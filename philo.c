#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	init_table(&table, ac, av);
	start_dinner(&table);
	free_forks(&table);
	free_philos(&table);

}

void	start_dinner(t_table *t)
{
	pthread_t	check_id;

	if (pthread_create(&check_id, NULL, check_life, t))
		exit_error(t, PTHREAD_FAIL);
	set_dinner_on(t);
	while (get_dinner_status(t))
		;
}

void	*check_life(void *table)
{
	int				i;
	suseconds_t		elapsed;
	t_table			*t;

	t = (t_table *)table;
	while (get_dinner_status(t))
	{
		i = -1;
		while (get_dinner_status(t) && ++i < t->nbr_philos)
		{
			elapsed = get_elapsed(t);
			if (elapsed - t->philos[i]->last_meal_end > t->time_to_die)
			{
				printf("%lu %d has died\n", elapsed, i + 1);
				set_dinner_off(t);
			}
		}
	}
	return (NULL);
}

void	*eat_sleep_think_repeat(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	while (!get_dinner_status(p->t))
		;
	while (get_dinner_status(p->t))
	{
		pickup_fork(p, 1);
		pickup_fork(p, 2);
		eat(p);
		putdown_fork(p, 1);
		putdown_fork(p, 2);
		sleepy(p);
	}
	return (NULL);
}

void	sleepy(t_philo *p)
{
	long int		elapsed;

	elapsed = get_elapsed(p->t);
	printf("%lu %d is sleeping\n", elapsed, p->id);
	usleep(p->t->time_to_sleep * 1000);
	elapsed = get_elapsed(p->t);
	printf("%lu %d is thinking\n", elapsed, p->id);
}

void	eat(t_philo *p)
{
	long int		elapsed;

	elapsed = get_elapsed(p->t);
	printf("%lu %d is eating\n", elapsed, p->id);
	usleep(p->t->time_to_eat * 1000);
	set_last_meal_time(p);
	p->meals_eaten++;
}

void	pickup_fork(t_philo *p, int f)
{
	long int	elapsed;
	int			fork_nr;

	if (f == 1)
		pthread_mutex_lock(&p->fork1->mtxid);
	else
		pthread_mutex_lock(&p->fork2->mtxid);
	elapsed = get_elapsed(p->t);
	if (f == 1)
		fork_nr = p->fork1->fork_id;
	else
		fork_nr = p->fork2->fork_id;
	printf("%lu %d has taken a fork [%d]\n", elapsed, p->id, fork_nr);
}

void	putdown_fork(t_philo *p, int f)
{
	long int	elapsed;

	if (f == 1)
		pthread_mutex_unlock(&p->fork1->mtxid);
	else
		pthread_mutex_unlock(&p->fork2->mtxid);
	elapsed = get_elapsed(p->t);
	printf("%lu %d has put down a fork\n", elapsed, p->id);
}
