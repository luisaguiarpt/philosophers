#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	init_table(&table, ac, av);
	free_forks(&table);
	free_philos(&table);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
	{

	}
}
