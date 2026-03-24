#include "philo.h"

void	*monitor_life(void *vtable)
{
	int		i;
	int		full_philos;
	t_table	*table;

	table = (t_table *)vtable;
	while (dinner_ongoing(table))
	{
		i = 0;
		full_philos = 0;
		while (i < table->nr_philos && dinner_ongoing(table))
		{
			if (is_dead(&table->philos[i]))
				break ;
			if (is_full(&table->philos[i]))
				full_philos++;
			if (all_full(table, full_philos))
				break ;
			i++;
		}
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(&philo->table->state);
		if (*philo->fork1_free && *philo->fork2_free)
		{
			*philo->fork1_free = false;
			*philo->fork2_free = false;
			pthread_mutex_lock(philo->fork1);
			print_fork(philo);
			pthread_mutex_lock(philo->fork2);
			print_fork(philo);
			pthread_mutex_unlock(&philo->table->state);
			break ;
		}
		pthread_mutex_unlock(&philo->table->state);
		usleep(250);
	}
	pthread_mutex_lock(&philo->table->state);
	philo->last_meal = get_curr_time_ms();
	if (philo->meals_eaten >= 0)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->state);
	print_eating(philo);
	precise_usleep((unsigned long)philo->table->time_to_eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_lock(&philo->table->state);
	*philo->fork1_free = true;
	*philo->fork2_free = true;
	pthread_mutex_unlock(&philo->table->state);
}

void	sleepy(t_philo *philo)
{
	print_sleeping(philo);
	precise_usleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_thinking(philo);
}

void	*philo_life(void *vphilo)
{
	t_philo	*philo;

	philo = (t_philo *)vphilo;
	while (dinner_ongoing(philo->table))
	{
		eat(philo);
		if (!dinner_ongoing(philo->table))
			break ;
		sleepy(philo);
		if (!dinner_ongoing(philo->table))
			break ;
		think(philo);
		if (philo->id % 2)
			usleep(1000);
	}
	return (NULL);
}

int	run_simulation(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	table->start_time = get_curr_time_ms();
	while (i < table->nr_philos)
	{
		philo = &table->philos[i];
		if (pthread_create(&philo->tid, NULL, philo_life, philo) != 0)
			return (PTHREAD_FAIL);
		i++;
	}
	monitor_life(table);
	i = 0;
	while (i < table->nr_philos)
	{
		philo = &table->philos[i];
		if (pthread_join(philo->tid, NULL) != 0)
			return (PTHREAD_FAIL);
		i++;
	}
	return (0);
}
