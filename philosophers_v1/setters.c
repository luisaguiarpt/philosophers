#include "philo.h"

void	set_start_time(t_table *t)
{
	int				ret;
	struct timeval	temp;

	pthread_mutex_lock(&t->mtxid);
	ret = gettimeofday(&temp, NULL);
	if (ret)
		exit_error(t, TIME_FAIL);
	t->start_time = get_milliseconds(temp);
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
	pthread_mutex_lock(&p->mtxid);
	p->last_meal_end = get_elapsed(p->t);
	pthread_mutex_unlock(&p->mtxid);
}
