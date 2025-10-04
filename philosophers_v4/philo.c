#include "philo.h"

// temp debug
#include <errno.h>
void	*track_end_stats(void *t);

int	main(int ac, char **av)
{
	t_table	t;

	parse(&t, ac, av);
	init_table(&t);
	init_forks(&t);
	init_monitor_thread(&t);
	init_philos(&t);
	start_dinner(&t);
	wait_for_end(&t);
}

// NAO POSSO USAR EXIT
//
// E PRECISO TIRAR OS EXITS QUE TENHO
//
// NAO ESQUECER

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

void	wait_for_end(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_philos)
		pthread_join(t->philos[i].tid, NULL);
	pthread_join(t->monitor_tid, NULL);
	while (get_ready(t) != 0)
		usleep(500);
	free(t->forks);
	free(t->philos);
}

void	*monitor_life(void *table)
{
	t_table	*t;
	int		i;
	int		all_full;

	t = (t_table *)table;
	while (get_ready(t) != t->n_philos)
		usleep(1000);
	while (get_dinner_status(t) && !meals_finished(t))
	{
		all_full = 0;
		i = -1;
		while (++i < t->n_philos)
		{
			if (has_starved(&t->philos[i]))
				set_dinner_status_off(t, &t->philos[i], 0);
			if (is_full(&t->philos[i]))
				all_full++;
		}
		if (all_full == t->n_philos)
			set_dinner_status_off(t, &t->philos[i], 1);
		usleep(t->time_to_die / 4 * 1000);
	}
	while (get_ready(t) != 0)
		usleep(1000);
	return (NULL);
}

bool	is_full(t_philo *p)
{
	if (p->t->meal_limit == -1)
		return (false);
	if (get_meals_eaten(p) >= p->t->meal_limit)
		return (true);
	return (false);
}

bool	has_starved(t_philo *p)
{
	if (get_elapsed_last_meal(p) > (unsigned long)p->t->time_to_die)
		return (true);
	return (false);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	ready_philo(p->t);
	while (get_ready(p->t) != p->t->n_philos)
		usleep(1000);
	while (get_dinner_status(p->t) == true)
	{
		pick_up_forks(p);
		eat(p);
		put_down_forks(p);
		sleepy(p);
		think(p);
	}
	unlock_forks(p);
	end_philo(p->t);
	return (NULL);
}

void	pick_up_forks(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	mutex_fct(&p->fork1->mtxid, LOCK, p->t);
	p->fork1->locked = p->id;
	p->forks[0] = 1;
	print_msg(p, FORK);
	if (get_dinner_status(p->t) == false)
		return ;
	mutex_fct(&p->fork2->mtxid, LOCK, p->t);
	p->fork2->locked = p->id;
	p->forks[1] = 1;
	print_msg(p, FORK);
}

void	eat(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	print_msg(p, EAT);
	mutex_fct(&p->meal_mtx, LOCK, p->t);
	p->last_meal_start = get_curr_time_ms();
	mutex_fct(&p->meal_mtx, UNLOCK, p->t);
	precise_usleep((unsigned long)p->t->time_to_eat);
	mutex_fct(&p->meal_mtx, LOCK, p->t);
	p->meals_eaten++;
	mutex_fct(&p->meal_mtx, UNLOCK, p->t);
}

void	put_down_forks(t_philo *p)
{
	if (get_dinner_status(p->t) == false && p->forks[0] == 0 && p->forks[1] == 0)
		return ;
	mutex_fct(&p->fork1->mtxid, UNLOCK, p->t);
	p->fork1->locked = 0;
	p->forks[0] = 0;
	if (get_dinner_status(p->t) == false && p->forks[0] == 0 && p->forks[1] == 0)
		return ;
	mutex_fct(&p->fork2->mtxid, UNLOCK, p->t);
	p->fork2->locked = 0;
	p->forks[1] = 0;
}

void	sleepy(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	print_msg(p, SLEEP);
	precise_usleep((unsigned long)p->t->time_to_sleep);
}

void	think(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	print_msg(p, THINK);
}
