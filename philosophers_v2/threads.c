#include "philo.h"

void	mutex_fct(pthread_mutex_t *mtxid, t_mtx_code code, t_table *t)
{
	int	err;

	err = 0;
	if (code == INIT)
		err = pthread_mutex_init(mtxid, NULL);
	else if (code == DESTROY)
		err = pthread_mutex_destroy(mtxid);
	else if (code == LOCK)
		err = pthread_mutex_lock(mtxid);
	else if (code == UNLOCK)
		err = pthread_mutex_unlock(mtxid);
	if (err)
		exit_error(t, MUTEX_FAIL);
}

void	init_philo_thread(t_philo *p)
{
	int	ret;

	ret = pthread_create(&p->tid, NULL, philo_life, p);
	if (ret)
		exit_error(p->t, PTHREAD_PHILO);
}

void	init_monitor_thread(t_table *t)
{
	int	ret;
	ret = pthread_create(&t->monitor_tid, NULL, monitor_life, t);
	if (!ret)
		exit_error(t, PTHREAD_MONITOR);
}
