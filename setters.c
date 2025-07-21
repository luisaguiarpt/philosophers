#include "philo.h"

void	set_start_time(t_table *t)
{
	int	ret;

	pthread_mutex_lock(&t->mtxid);
	ret = gettimeofday(&t->start_time, NULL);
	if (ret)
		exit_error(t, TIME_FAIL);
	pthread_mutex_unlock(&t->mtxid);
}

void	set_dinner_on(t_table *t)
{
	pthread_mutex_lock(&t->mtxid);
	t->dinner_on = true;
	pthread_mutex_unlock(&t->mtxid);
}

void	set_dinner_off(t_table *t)
{
	pthread_mutex_lock(&t->mtxid);
	t->dinner_on = false;
	pthread_mutex_unlock(&t->mtxid);
}

void	set_last_meal_time(t_philo *p)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	pthread_mutex_lock(&p->mtxid);
	p->last_meal_end = curr.tv_usec;
	pthread_mutex_unlock(&p->mtxid);
}
