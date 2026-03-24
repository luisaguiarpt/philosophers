#include "philo.h"

void	print_death(t_philo *philo)
{
	unsigned long	elapsed;

	elapsed = get_elapsed(philo->table);
	pthread_mutex_lock(&philo->table->write);
	printf("[%ld] %d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write);
}

void	print_fork_down(t_philo *philo)
{
	unsigned long	elapsed;

	if (!dinner_ongoing(philo->table))
		return ;
	elapsed = get_elapsed(philo->table);
	pthread_mutex_lock(&philo->table->write);
	printf("[%ld] %d has returned a fork\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write);
}

void	print_fork(t_philo *philo)
{
	unsigned long	elapsed;

	if (!dinner_ongoing(philo->table))
		return ;
	elapsed = get_elapsed(philo->table);
	pthread_mutex_lock(&philo->table->write);
	printf("[%ld] %d has taken a fork\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write);
}

void	print_eating(t_philo *philo)
{
	unsigned long	elapsed;

	if (!dinner_ongoing(philo->table))
		return ;
	elapsed = get_elapsed(philo->table);
	pthread_mutex_lock(&philo->table->write);
	printf("[%ld] %d is eating\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write);
}

void	print_sleeping(t_philo *philo)
{
	unsigned long	elapsed;

	if (!dinner_ongoing(philo->table))
		return ;
	elapsed = get_elapsed(philo->table);
	pthread_mutex_lock(&philo->table->write);
	printf("[%ld] %d is sleeping\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write);
}

void	print_thinking(t_philo *philo)
{
	unsigned long	elapsed;

	if (!dinner_ongoing(philo->table))
		return ;
	elapsed = get_elapsed(philo->table);
	pthread_mutex_lock(&philo->table->write);
	printf("[%ld] %d is thinking\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write);
}
