#include "philo.h"

void	set_dinner_status_off(t_table *t)
{
	mutex_fct(&t->state_mtx, LOCK, t);
	t->dinner_on = false;
	mutex_fct(&t->state_mtx, UNLOCK, t);
}
