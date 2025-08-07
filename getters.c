#include "philo.h"

suseconds_t	get_start_time(t_table *t)
{
	long int	ret;

	pthread_mutex_lock(&t->mtxid);
	ret = t->start_time;
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

long int	get_milliseconds(struct timeval tv)
{
	long int	ret;

	ret = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ret);
}

long int	get_elapsed(t_table *t)
{
	struct timeval	curr;
	long int		elapsed;
	int				ret;

	ret = gettimeofday(&curr, NULL);
	if (ret)
		exit_error(t, TIME_FAIL);
	elapsed = get_milliseconds(curr) - t->start_time;
	return (elapsed);
}
