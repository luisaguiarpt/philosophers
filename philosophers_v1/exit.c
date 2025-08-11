#include "philo.h"

void	exit_error(t_table *t, t_exit_status err)
{
	if (err == NOARGS || err == XSARGS)
	{
		printf("Incorrect input.\n");
		printf("Usage: \"./philo nbr_of_philos time_to_die"); 
		printf(" time_to_eat time_to_sleep [meal_limit]\"\n");
	}
	else if (err == INV_VALUE)
		printf("Invalid value passed in input.\n");
	else if (err == CALLOCFAIL)
		printf("Calloc failed.\n");
	else if (err == PTHREAD_FAIL)
		printf("Wrong mutex code passed\n");
	free_forks(t);
	free_philos(t);
	exit(err);
}
