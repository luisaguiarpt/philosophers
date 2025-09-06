#include "philo.h"

bool	get_dinner_status(t_table *t)
{
	bool	status;

	mutex_fct(&t->state_mtx, LOCK, t);
	status = t->dinner_on;
	mutex_fct(&t->state_mtx, UNLOCK, t);
	return (status);
}

int	get_ready(t_table *t)
{
	int	ready;

	mutex_fct(&t->state_mtx, LOCK, t);
	ready = t->ready;
	mutex_fct(&t->state_mtx, UNLOCK, t);
	return (ready);
}

int	meals_finished(t_table *t)
{
	int	status;

	mutex_fct(&t->state_mtx, LOCK, t);
	status = t->meals_finished;
	mutex_fct(&t->state_mtx, UNLOCK, t);
	return (status);
}

int	get_meals_eaten(t_philo *p)
{
	int	meals_eaten;

	mutex_fct(&p->meal_mtx, LOCK, p->t);
	meals_eaten = p->meals_eaten;
	mutex_fct(&p->meal_mtx, UNLOCK, p->t);
	return (meals_eaten);
}
