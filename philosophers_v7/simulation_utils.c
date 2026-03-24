#include "philo.h"

bool	dinner_ongoing(t_table *table)
{
	bool	dinner_state;

	pthread_mutex_lock(&table->state);
	dinner_state = table->dinner_finished;
	pthread_mutex_unlock(&table->state);
	return (!dinner_state);
}

bool	is_dead(t_philo *philo)
{
	unsigned long	current;
	unsigned long	time_since_last_meal;

	current = get_curr_time_ms();
	pthread_mutex_lock(&philo->table->state);
	time_since_last_meal = current - philo->last_meal;
	pthread_mutex_unlock(&philo->table->state);
	if (time_since_last_meal >= (unsigned long)philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->state);
		philo->table->dinner_finished = true;
		pthread_mutex_unlock(&philo->table->state);
		print_death(philo);
		return (true);
	}
	return (false);
}

bool	is_full(t_philo *philo)
{
	int	meals_eaten;

	if (philo->table->meal_limit == -1)
		return (false);
	pthread_mutex_lock(&philo->table->state);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->table->state);
	return (meals_eaten >= philo->table->meal_limit);
}

bool	all_full(t_table *table, int full_philos)
{
	if (full_philos >= table->nr_philos)
	{
		pthread_mutex_lock(&table->state);
		table->dinner_finished = true;
		pthread_mutex_unlock(&table->state);
		return (true);
	}
	return (false);
}
