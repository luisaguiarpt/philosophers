#include "philo.h"

void	one_philo(t_table *t)
{
	printf("[%i] 1 has picked up a fork\n", 0);
	printf("[%i] 1 has died\n", t->time_to_die + 1);
	exit(0);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		exit_code;

	exit_code = parse(&table, ac, av);
	if (is_error(exit_code))
		return (print_msg(exit_code));
	exit_code = init(&table);
	if (is_error(exit_code))
		return (print_msg(exit_code));
	exit_code = run_simulation(&table);
	if (is_error(exit_code))
		return (print_msg(exit_code));
}
