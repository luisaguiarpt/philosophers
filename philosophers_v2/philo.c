#include "philo.h"

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
		pthread_detach(t->philos[i].tid);
	pthread_join(t->monitor_tid, NULL);
	mutex_fct(&t->print_mtx, LOCK, t);
	printf("Dinner is over\n");
	mutex_fct(&t->print_mtx, UNLOCK, t);
	while (get_ready(t) != 0)
		usleep(100);
	free(t->forks);
	free(t->philos);
}

void	*monitor_life(void *table)
{
	t_table	*t;
	int		i;

	t = (t_table *)table;
	mutex_fct(&t->print_mtx, LOCK, t);
	printf("Monitor thread started\n");
	mutex_fct(&t->print_mtx, UNLOCK, t);
	while (get_ready(t) != t->n_philos)
		usleep(1000);
	while (get_dinner_status(t) && !meals_finished(t))
	{
		i = -1;
		while (++i < t->n_philos)
		{
			if (has_starved(&t->philos[i]))
				set_dinner_status_off(t);
			if (is_full(&t->philos[i]))
				set_dinner_status_off(t);
		}
	}
	while (get_ready(t) != 0)
		usleep(100);
	return (NULL);
}

bool	is_full(t_philo *p)
{
	if (p->t->meal_limit == -1)
		return (false);
	if (get_meals_eaten(p) >= p->t->meal_limit)
	{
		printf("meal limit [Philo %i]\n", p->id);
		return (true);
	}
	return (false);
}

bool	has_starved(t_philo *p)
{
	if (get_elapsed_last_meal(p) > (unsigned long)p->t->time_to_die)
	{
		mutex_fct(&p->t->print_mtx, LOCK, p->t);
		printf("Philo %i -> elapsed since last meal: %lu\n", p->id, get_elapsed_last_meal(p));
		printf("Philo %i has starved [elapsed: %lu]\n", p->id, get_elapsed_last_meal(p));
		mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
		return (true);
	}
	return (false);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	mutex_fct(&p->t->print_mtx, LOCK, p->t);
	printf("philosopher %d is born\n", p->id);
	mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
	ready_philo(p->t);
	while (get_ready(p->t) != p->t->n_philos)
		;
	mutex_fct(&p->t->print_mtx, LOCK, p->t);
	printf("philosopher %d is ready\n", p->id);
	mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
	while (get_dinner_status(p->t) == true)
	{
		pick_up_forks(p);
		eat(p);
		put_down_forks(p);
		sleepy(p);
		think(p);
	}
	printf("End of philo %i life\n", p->id);
	end_philo(p->t);
	return (NULL);
}

void	pick_up_forks(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	mutex_fct(&p->fork1->mtxid, LOCK, p->t);
	print_msg(p, FORK);
	mutex_fct(&p->fork2->mtxid, LOCK, p->t);
	print_msg(p, FORK);
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
		usleep(50);
	}
	mutex_fct(&p->meal_mtx, LOCK, p->t);
	p->meals_eaten++;
	if (p->meals_eaten == p->t->meal_limit)
		set_dinner_status_off(p->t);
	mutex_fct(&p->meal_mtx, UNLOCK, p->t);
}

void	put_down_forks(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	mutex_fct(&p->fork1->mtxid, UNLOCK, p->t);
	print_msg(p, FORKD);
	mutex_fct(&p->fork2->mtxid, UNLOCK, p->t);
	print_msg(p, FORKD);
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
		usleep(50);
	}
}

void	think(t_philo *p)
{
	if (get_dinner_status(p->t) == false)
		return ;
	print_msg(p, THINK);
}
