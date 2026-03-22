#include "philo.h"

static int	init_table(t_table *table)
{
	int	exit_code;

	table->start_time = 0;
	table->dinner_finished = false;
	exit_code = pthread_mutex_init(&table->write, NULL);
	if (exit_code)
		return (exit_code);
	exit_code = pthread_mutex_init(&table->state, NULL);
	if (exit_code)
		return (exit_code);
	return (0);
}

static int	init_forks(t_table *table)
{
	int	exit_code;
	int	i;

	table->forks = malloc(table->nr_philos * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (MALLOC_FAIL);
	i = 0;
	while (i < table->nr_philos)
	{
		exit_code = pthread_mutex_init(&table->forks[i], NULL);
		if (exit_code)
		{
			destroy_forks(table, i);
			return (MUTEX_FAIL);
		}
		i++;
	}
	return (0);
}

static int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(table->nr_philos * sizeof(t_philo));
	if (!table->philos)
		return (PTHREAD_FAIL);
	i = 0;
	while (i < table->nr_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_end = 0;
		table->philos[i].fork1 = &table->forks[i];
		table->philos[i].fork1 = &table->forks[(i + 1) % table->nr_philos];
		table->philos[i].table = table;
		i++;
	}
	return (0);
}

int	init(t_table *table)
{
	int	exit_code;

	exit_code = init_table(table);
	if (exit_code)
		return (exit_code);
	exit_code = init_forks(table);
	if (exit_code)
		return (exit_code);
	exit_code = init_philos(table);
	if (exit_code)
		return (exit_code);
	return (0);
}
