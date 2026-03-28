/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 15:41:01 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/28 15:41:02 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	cleanup(&table);
	return (0);
}
