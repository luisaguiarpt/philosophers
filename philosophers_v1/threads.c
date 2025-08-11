#include "philo.h"

void	mutex_f(t_table *t, pthread_mutex_t *id, t_thread_code code)
{
	int	err;

	err = 0;
	if (code == INIT)
		err = pthread_mutex_init(id, NULL);
	else if (code == DESTROY)
		err = pthread_mutex_destroy(id);
	else if (code == LOCK)
		err = pthread_mutex_lock(id);
	else if (code == UNLOCK)
		err = pthread_mutex_unlock(id);
	else
		exit_error(t, err);
}
