#include "philo.h"

void	exit_error(t_exit_status err)
{
	if (err == NOARGS || err == XSARGS)
	{
		printf("Incorrect input.\n");
		printf("Usage: \"./philo nbr_of_philos time_to_die \
				time_to_eat time_to_sleep [meal_limit]\"");
		exit(NOARGS);
	}
	if (err == INV_VALUE)
	{
		printf("Invalid value passed in input.\n");
		exit(INV_VALUE);
	}
	if (err == CALLOCFAIL)
	{
		printf("Calloc failed.\n");
		exit(CALLOCFAIL);
	}
}
