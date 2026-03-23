#include "philo.h"

void	precise_usleep(unsigned long ms)
{
	long	start;
	
	start = get_curr_time_ms();
	while (get_curr_time_ms() - start < ms)
		usleep(200);
}

unsigned long 	get_curr_time_ms(void)
{
	struct timeval	tv_curr;

	gettimeofday(&tv_curr, NULL);
	return (tv_curr.tv_sec * 1000 + tv_curr.tv_usec / 1000);
}

unsigned long get_elapsed(t_table *t)
{
	long int	current;

	current = get_curr_time_ms();
	return (current - t->start_time);
}
