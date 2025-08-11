#include "philo.h"

unsigned long 	get_curr_time_ms(void)
{
	struct timeval	tv_curr;
	unsigned long	current;

	gettimeofday(&tv_curr, NULL);
	current = tv_curr.tv_sec * 1000 + tv_curr.tv_usec / 1000;
	return (current);
}

unsigned long get_elapsed(t_table *t)
{
	long int	current;
	long int	elapsed;

	current = get_curr_time_ms();
	elapsed = current - t->start_time;
	return (elapsed);
}

unsigned long	get_elapsed_last_meal(t_philo *p)
{
	unsigned long 	current;
	unsigned long 	time_since_last_meal;

	current = get_curr_time_ms();
	pthread_mutex_lock(&p->meal_mtx);
	time_since_last_meal = current - p->last_meal_start;
	pthread_mutex_unlock(&p->meal_mtx);
	return (time_since_last_meal);
}

unsigned long	get_last_meal_start(t_philo *p)
{
	unsigned long	last_meal_start;

	pthread_mutex_lock(&p->meal_mtx);
	last_meal_start = p->last_meal_start;
	pthread_mutex_unlock(&p->meal_mtx);
	return (last_meal_start);
}
