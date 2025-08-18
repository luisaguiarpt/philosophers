#include "philo.h"

int	main(int ac, char **av)
{
	t_table	t;

	parse(&t, ac, av);
	init_table(&t);
	init_forks(&t);
	init_philos(&t);
	init_monitor_thread(&t);
	start_dinner(&t);
}

void	start_dinner(t_table *t)
{
	sleep(1);
	t->start_time = get_curr_time_ms();
	if (t->dinner_on == true)
		printf("Dinner_status: ON\n");
	else
		printf("Dinner_status: OFF\n");
	sleep(1);
}

void	wait_for_end(t_table *t)
{
	while (get_dinner_status(t))
	{
		usleep(50);
	}
}

void	*monitor_life(void *table)
{
	t_table	*t;
	int		i;

	t = (t_table *)table;
	mutex_fct(&t->print_mtx, LOCK, t);
	printf("Monitor thread started\n");
	mutex_fct(&t->print_mtx, UNLOCK, t);
	while (t->start_time == 0)
		usleep(50);
	while (get_dinner_status(t) && !meals_finished(t))
	{
		i = -1;
		while (++i < t->n_philos)
		{
			if (has_starved(&t->philos[i]))
				set_dinner_status_off(t);
			if (get_meals_eaten(&t->philos[i]) >= t->meal_limit)
				set_dinner_status_off(t);
		}
	}
	return (NULL);
}

bool	has_starved(t_philo *p)
{
	if (get_elapsed_last_meal(p) > get_last_meal_start(p))
		return (true);
	return (false);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	mutex_fct(&p->t->print_mtx, LOCK, p->t);
	printf("philosopher %d is born\n", p->id);
	mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
	while (p->t->start_time == 0)
		usleep(50);
	p->last_meal_start = p->t->start_time;
	while (get_dinner_status(p->t) && !meals_finished(p->t))
	{
		pick_up_forks(p);
		eat(p);
		put_down_forks(p);
		sleepy(p);
		think(p);
	}
	return (NULL);
}

void	sleepy(t_philo *p)
{
	print_msg(p, SLEEP);
	usleep(p->t->time_to_sleep * 1000);
}

void	think(t_philo *p)
{
	print_msg(p, THINK);
}

void	eat(t_philo *p)
{
	print_msg(p, EAT);
	mutex_fct(&p->meal_mtx, LOCK, p->t);
	p->last_meal_start = get_curr_time_ms();
	mutex_fct(&p->meal_mtx, UNLOCK, p->t);
	usleep(p->t->time_to_eat * 1000	);
	mutex_fct(&p->meal_mtx, LOCK, p->t);
	p->meals_eaten++;
	mutex_fct(&p->meal_mtx, UNLOCK, p->t);
}

void	pick_up_forks(t_philo *p)
{
	mutex_fct(&p->fork1->mtxid, LOCK, p->t);
	print_msg(p, FORK);
	mutex_fct(&p->fork2->mtxid, LOCK, p->t);
	print_msg(p, FORK);
}

void	put_down_forks(t_philo *p)
{
	mutex_fct(&p->fork1->mtxid, UNLOCK, p->t);
	mutex_fct(&p->fork2->mtxid, UNLOCK, p->t);
}
