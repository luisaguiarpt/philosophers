#include "philo.h"

void	safe_use(pthread_mutex_t *mtxid, (void *)f(void *), t_table *table)
{
	pthread_mutex_lock(mtxid);
	f(table);
	pthread_mutex_unlock(mtxid);
}
