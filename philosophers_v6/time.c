#include "philo.h"

void	precise_usleep(unsigned long ms)
{
	long	start;
	
	start = get_curr_time_ms();
	while (get_curr_time_ms() - start < ms)
	{
		usleep(500);
	}
}

unsigned long 	get_curr_time_ms(void)
{
	struct timeval	tv_curr;
	unsigned long	current;

	gettimeofday(&tv_curr, NULL);
	current = tv_curr.tv_sec * 1000 + tv_curr.tv_usec / 1000;
	return (current);
}

unsigned long get_elapsed(t_table *t)
{
	long int	current;
	long int	elapsed;

	current = get_curr_time_ms();
	elapsed = current - t->start_time;
	return (elapsed);
}
