#include "philo.h"

void	init_philos(t_table *table)
{
	int		i;

	table->philo = ft_calloc(table->nbr_philos + 1, sizeof(t_philo *));
	if (!table->philo)
		exit_error(CALLOCFAIL);
	i = -1;
	while (++i < table->nbr_philos)
	{
		table->philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!table->philo[i])
		{
			free_philos(table->philo);
			exit_error(CALLOCFAIL);
		}
		table->philo[i]->dead = false;
		table->philo[i]->table = table;
		pthread_mutex_init(table->philo[i]->mtxid, NULL);
		printf("Created philo %d\n", i);
	}
}
