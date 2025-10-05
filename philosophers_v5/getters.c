#include "philo.h"

bool	get_dinner_status(t_table *t)
{
	bool	status;

	mutex_fct(&t->state_mtx, LOCK, t);
	status = t->dinner_on;
	mutex_fct(&t->state_mtx, UNLOCK, t);
	return (status);
}

bool	check_dead(t_philo *p)
{
	bool	dead;

	mutex_fct(&t->dead_mtx, LOCK, t);
	dead = p->dead;
	mutex_fct(&t->dead_mtx, UNLOCK, t);
	return (dead);

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
