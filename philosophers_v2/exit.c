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
	free_forks(t);
	free_philos(t);
	exit(err);
}

void	unlock_forks(t_table *t)
{
	int	i;
	

	i = -1;
	while (++i < t->n_philos)
	{

		if (
	}
}
