#include "philo.h"

suseconds_t	get_start_time(t_table *t)
{
	suseconds_t	ret;

	pthread_mutex_lock(&t->mtxid);
	ret = t->start_time.tv_usec;
	pthread_mutex_unlock(&t->mtxid);
	return (ret);
}

bool	get_dinner_status(t_table *t)
{
	bool	ret;
	pthread_mutex_lock(&t->mtxid);
	if (t->dinner_on)
		ret = true;
	else
		ret = false;
	pthread_mutex_unlock(&t->mtxid);
	return (ret);
}
