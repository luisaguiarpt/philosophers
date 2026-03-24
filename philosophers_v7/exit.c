#include "philo.h"

void	destroy_forks(t_table *table, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
	return ;
}
