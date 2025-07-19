#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	parse(&table, ac, av);
	init_philos(&table);
	start_dinner(&table);
	free_philos(table.philo);
}

void	start_dinner(t_table *table)
{
	
}
