#include "philo.h"

void	exit_error(t_table *t, t_exit_status err)
{
	(void)t;
	if (err == NOARGS || err == XSARGS)
	{
		printf("Incorrect input.\n");
		printf("Usage: \"./philo nbr_of_philos time_to_die"); 
		printf(" time_to_eat time_to_sleep [meal_limit]\"\n");
	}
	else if (err == INV_VALUE)
		printf("Invalid input values passed\n");
	else if (err == CALLOCFAIL)
		printf("Calloc failed\n");
	else if (err == PTHREAD_FAIL)
		printf("Wrong mutex code passed\n");
	else if (err == PTHREAD_PHILO)
		printf("Failed to create a philo thread\n");
	else if (err == NEG_TIME)
		printf("Please don't input negative times\n");
	else if (err == INV_N_PHILO)
		printf("Please input positive amount of philosophers\n");
	else if (err == INV_MEAL)
		printf("If you're setting a meal limit, please make it positive\n");
	if (err == INV_N_PHILO)
		exit(err);
	free(t->forks);
	free(t->philos);
	exit(err);
}

void	unlock_forks(t_philo *p)
{
	mutex_fct(&p->fork1->lock_mtx, LOCK, p->t);
	if (p->fork1->locked == p->id)
	{
		p->fork1->locked = 0;
		mutex_fct(&p->fork1->mtxid, UNLOCK, p->t);
	}
	mutex_fct(&p->fork1->lock_mtx, UNLOCK, p->t);
	mutex_fct(&p->fork2->lock_mtx, LOCK, p->t);
	if (p->fork2->locked == p->id)
	{
		p->fork2->locked = 0;
		mutex_fct(&p->fork2->mtxid, UNLOCK, p->t);
	}
	mutex_fct(&p->fork2->lock_mtx, UNLOCK, p->t);
}

void	destroy_mtx(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_philos)
	{
		mutex_fct(&t->philos[i].meal_mtx, DESTROY, t);
		mutex_fct(&t->forks[i].mtxid, DESTROY, t);
		mutex_fct(&t->forks[i].lock_mtx, DESTROY, t);
		mutex_fct(&t->state_mtx, DESTROY, t);
		mutex_fct(&t->time_mtx, DESTROY, t);
		mutex_fct(&t->print_mtx, DESTROY, t);
	}
}
