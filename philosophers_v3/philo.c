#include "philo.h"

// temp debug
#include <errno.h>
void	*track_end_stats(void *t);

int	main(int ac, char **av)
{
	t_table	t;
	pthread_t	testid;

	printf("DEBUG=%i\n", DEBUG);
	parse(&t, ac, av);
	init_table(&t);
	init_forks(&t);
	init_monitor_thread(&t);
	init_philos(&t);
	start_dinner(&t);
	// temp debug
	if (DEBUG)
		pthread_create(&testid, NULL, track_end_stats, &t);
	wait_for_end(&t);
	if (DEBUG)
		usleep(10);
}

void	one_philo(t_table *t)
{
	printf("[%i] 1 has picked up a fork\n", 0);
	printf("[%i] 1 has died\n", t->time_to_die + 1);
	exit(0);
}

void	start_dinner(t_table *t)
{
	int				i;
	unsigned long	start_time;

	start_time = get_curr_time_ms();
	i = -1;
	while (++i < t->n_philos)
		t->philos[i].last_meal_start = start_time;
	t->start_time = start_time;
}

//temp debug
void	*track_end_stats(void *table)
{
	if (!DEBUG)
		return (NULL);
	t_table *t = (t_table *)table;
	while (get_ready(t) != t->n_philos)
		usleep(10);
	while (get_dinner_status(t) == true)
		usleep(100);
	int	i;
	int	error;
	while (true)
	{
		i = -1;
		mutex_fct(&t->print_mtx, LOCK, t);
		while (++i < t->n_philos)
		{
			error = pthread_mutex_trylock(&t->forks[i].mtxid);
			if (error == 0)
				pthread_mutex_unlock(&t->forks[i].mtxid);
			printf("Fork %i [Locked by %i] -> %s\n", i, t->forks[i].locked, strerror(error));
			usleep(10);
		}
		mutex_fct(&t->print_mtx, UNLOCK, t);
		sleep(3);
	}
	return (NULL);
}

void	wait_for_end(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_philos)
		pthread_join(t->philos[i].tid, NULL);
	pthread_join(t->monitor_tid, NULL);
	if (DEBUG)
	{
		mutex_fct(&t->print_mtx, LOCK, t);
		printf("Dinner is over\n");
		mutex_fct(&t->print_mtx, UNLOCK, t);
	}
	while (get_ready(t) != 0)
		usleep(100);
	if (DEBUG)
		return ;
	free(t->forks);
	free(t->philos);
}

void	*monitor_life(void *table)
{
	t_table	*t;
	int		i;

	t = (t_table *)table;
	if (DEBUG)
	{
		mutex_fct(&t->print_mtx, LOCK, t);
		printf("Monitor thread started\n");
		mutex_fct(&t->print_mtx, UNLOCK, t);
	}
	while (get_ready(t) != t->n_philos)
		usleep(100);
	while (get_dinner_status(t) && !meals_finished(t))
	{
		i = -1;
		while (++i < t->n_philos)
		{
			if (has_starved(&t->philos[i]))
				set_dinner_status_off(t, &t->philos[i], 0);
			if (is_full(&t->philos[i]))
				set_dinner_status_off(t, &t->philos[i], 1);
		}
	}
	while (get_ready(t) != 0)
		usleep(10);
	return (NULL);
}

bool	is_full(t_philo *p)
{
	if (p->t->meal_limit == -1)
		return (false);
	if (get_meals_eaten(p) >= p->t->meal_limit)
	{
		if (DEBUG)
		{
			mutex_fct(&p->t->print_mtx, LOCK, p->t);
			printf("meal limit [Philo %i]\n", p->id);
			mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
		}
		return (true);
	}
	return (false);
}

bool	has_starved(t_philo *p)
{
	if (get_elapsed_last_meal(p) > (unsigned long)p->t->time_to_die)
	{
		if (DEBUG)
		{
			mutex_fct(&p->t->print_mtx, LOCK, p->t);
			printf("Philo %i has starved [elapsed: %lu]\n", p->id, get_elapsed_last_meal(p));
			mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
		}
		return (true);
	}
	return (false);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (DEBUG)
	{
		mutex_fct(&p->t->print_mtx, LOCK, p->t);
		printf("philosopher %d is born\n", p->id);
		mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
	}
	ready_philo(p->t);
	while (get_ready(p->t) != p->t->n_philos)
		usleep(10);
	if (DEBUG)
	{
		mutex_fct(&p->t->print_mtx, LOCK, p->t);
		printf("philosopher %d is ready\n", p->id);
		mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
	}
	while (get_dinner_status(p->t) == true)
	{
		pick_up_forks(p);
		eat(p);
		put_down_forks(p);
		sleepy(p);
		think(p);
	}
	if (DEBUG)
	{
		mutex_fct(&p->t->print_mtx, LOCK, p->t);
		printf("End of philo %i life\n", p->id);
		mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
	}
	unlock_forks(p);
	end_philo(p->t);
	return (NULL);
}

void	pick_up_forks(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	print_fork(p, p->fork1, WAIT);
	mutex_fct(&p->fork1->mtxid, LOCK, p->t);
	p->fork1->locked = p->id;
	print_msg(p, FORK);
	if (DEBUG)
		print_fork(p, p->fork1, FORK);
	if (get_dinner_status(p->t) == false)
		return ;
	print_fork(p, p->fork2, WAIT);
	mutex_fct(&p->fork2->mtxid, LOCK, p->t);
	p->fork2->locked = p->id;
	print_msg(p, FORK);
	if (DEBUG)
		print_fork(p, p->fork2, FORK);
}

void	eat(t_philo *p)
{
	unsigned long	start;

	if (get_dinner_status(p->t) == false)
		return ;
	print_msg(p, EAT);
	mutex_fct(&p->meal_mtx, LOCK, p->t);
	start = get_curr_time_ms();
	p->last_meal_start = start;
	mutex_fct(&p->meal_mtx, UNLOCK, p->t);
	while (get_curr_time_ms() - start < (unsigned long)p->t->time_to_eat)
	{
		if (get_dinner_status(p->t) == false)
			return ;
		usleep(10);
	}
	mutex_fct(&p->meal_mtx, LOCK, p->t);
	p->meals_eaten++;
//	if (p->meals_eaten == p->t->meal_limit)
		//set_dinner_status_off(p->t, p, 1);
	mutex_fct(&p->meal_mtx, UNLOCK, p->t);
}

void	put_down_forks(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	mutex_fct(&p->fork1->mtxid, UNLOCK, p->t);
	p->fork1->locked = 0;
	if (DEBUG)
	{
		print_msg(p, FORKD);
		print_fork(p, p->fork1, FORKD);
	}
	if (get_dinner_status(p->t) == false)
		return ;
	mutex_fct(&p->fork2->mtxid, UNLOCK, p->t);
	p->fork2->locked = 0;
	if (DEBUG)
	{
		print_msg(p, FORKD);
		print_fork(p, p->fork2, FORKD);
	}
}

void	sleepy(t_philo *p)
{
	unsigned long	start;

	if (get_dinner_status(p->t) == false)
		return ;
	print_msg(p, SLEEP);
	start = get_curr_time_ms();
	while (get_curr_time_ms() - start < (unsigned long)p->t->time_to_sleep)
	{
		if (get_dinner_status(p->t) == false)
			return ;
		usleep(10);
	}
}

void	think(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	print_msg(p, THINK);
}
