#include "philo.h"

void	test_structs(t_table *t)
{
	int	i = 0;

	while (i < t->n_philos)
	{
		printf("Philosopher %d:\n", t->philos[i].id);
		printf("Meals eaten: %u\n", t->philos[i].meals_eaten);
		printf("Last meal start: %lu\n", t->philos[i].last_meal_start);
		printf("Mutex: %p\n", &t->philos[i].meal_mtx);
		printf("Fork 1: %p\n", t->philos[i].fork1);
		printf("Fork 2: %p\n", t->philos[i].fork2);
		i++;
	}
	i = 0;
	while (i < t->n_philos)
	{
		printf("Fork %d:\n", i);
		printf("Mutex: %p\n", &t->forks[i].mtxid);
		i++;
	}
}

void	test_parse(t_table *t)
{
	printf("Number of philos: %d\n", t->n_philos);
	printf("Time to die: %d\n", t->time_to_die);
	printf("Time to eat: %d\n", t->time_to_eat);
	printf("Time to sleep: %d\n", t->time_to_sleep);
	printf("Meal limit: %d\n", t->meal_limit);
}

void	test_times(t_table *t)
{
	t_philo	philo;

	philo.t = t;
	t->start_time = get_curr_time_ms();
	pthread_mutex_init(&t->print_mtx, NULL);
	pthread_mutex_init(&philo.meal_mtx, NULL);
	printf("Start time: %ld\n", t->start_time);
	philo.last_meal_start = get_curr_time_ms();
	printf("Start time: %ld\n", philo.last_meal_start);
	usleep(1000000);
	printf("Time since last meal: %ld\n", get_time_since_last_meal(&philo));
	printf("Time elapsed: %ld\n", get_elapsed(t));
	usleep(1000000);
	philo.last_meal_start = get_curr_time_ms();
	printf("Time since last meal: %ld\n", get_time_since_last_meal(&philo));
	printf("Time elapsed: %ld\n", get_elapsed(t));
}
