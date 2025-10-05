#include "philo.h"

void	set_dinner_status_off(t_table *t, t_philo *p, int cause)
{
	mutex_fct(&t->state_mtx, LOCK, t);
	t->dinner_on = false;
	mutex_fct(&t->state_mtx, UNLOCK, t);
	if (cause == 0)
		print_msg(p, DIE);
}

void	ready_philo(t_table *t)
{
	mutex_fct(&t->state_mtx, LOCK, t);
	t->ready++;
	mutex_fct(&t->state_mtx, UNLOCK, t);
}

void	end_philo(t_table *t)
{
	mutex_fct(&t->state_mtx, LOCK, t);
	t->ready--;
	mutex_fct(&t->state_mtx, UNLOCK, t);
}
