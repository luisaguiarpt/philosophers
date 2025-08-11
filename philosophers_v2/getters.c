#include "philo.h"

bool	get_dinner_status(t_table *t)
{
	bool	status;

	mutex_fct(&state_mtx, LOCK, t);
	status = t->dinner_on;
	mutex_fct(&state_mtx, UNLOCK, t);
	return (status);
}

int	meals_finished(t_table *t)
{
	int	status;

	mutex_fct(&state_mtx, LOCK, t);
	status = t->meals_finished;
	mutex_fct(&state_mtx, UNLOCK, t);
	return (status);
}
