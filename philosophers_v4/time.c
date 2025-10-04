#include "philo.h"

void	precise_usleep(unsigned long ms)
{
	long	start;
	
	start = get_curr_time_ms();
	while (get_curr_time_ms() - start < ms)
		usleep(500);
}

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

	pthread_mutex_lock(&p->meal_mtx);
	current = get_curr_time_ms();
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

unsigned long	get_start_time(t_table *t)
{
	unsigned long	start_time;

	mutex_fct(&t->time_mtx, LOCK, t);
	start_time = t->start_time;
	mutex_fct(&t->time_mtx, UNLOCK, t);
	return (start_time);
}
