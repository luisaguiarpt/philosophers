#include "philo.h"

bool	is_error(t_error error_code)
{
	if (error_code == 0)
		return (false);
	return (true);
}

int	print_msg(t_error err)
{
	if (err == NOARGS || err == XSARGS)
	{
		printf("Incorrect input.\n");
		printf("Usage: \"./philo nbr_of_philos time_to_die"); 
		printf(" time_to_eat time_to_sleep [meal_limit]\"\n");
	}
	else if (err == INV_VALUE)
		printf("Invalid input values passed\n");
	else if (err == MALLOC_FAIL)
		printf("Malloc failed\n");
	else if (err == PTHREAD_FAIL)
		printf("Pthread failed\n");
	else if (err == MUTEX_FAIL)
		printf("Mutex failed\n");
	return (0);
}
