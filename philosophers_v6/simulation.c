/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 15:41:30 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/28 15:41:32 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_life(void *vtable)
{
	int		i;
	int		full_philos;
	t_table	*table;

	table = (t_table *)vtable;
	while (dinner_ongoing(table))
	{
		i = 0;
		full_philos = 0;
		while (i < table->nr_philos && dinner_ongoing(table))
		{
			if (is_dead(&table->philos[i]))
				break ;
			if (is_full(&table->philos[i]))
				full_philos++;
			if (all_full(table, full_philos))
				break ;
			i++;
		}
	}
	return (NULL);
}

void	*philo_life(void *vphilo)
{
	t_philo	*philo;

	philo = (t_philo *)vphilo;
	if (philo->id % 2)
		usleep(1000);
	while (dinner_ongoing(philo->table))
	{
		eat(philo);
		if (!dinner_ongoing(philo->table))
			break ;
		sleepy(philo);
		if (!dinner_ongoing(philo->table))
			break ;
		think(philo);
		if (!(philo->id % 2))
			usleep(1000);
	}
	return (NULL);
}

int	run_simulation(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	table->start_time = get_curr_time_ms();
	while (i < table->nr_philos)
	{
		philo = &table->philos[i];
		if (pthread_create(&philo->tid, NULL, philo_life, philo) != 0)
			return (PTHREAD_FAIL);
		i++;
	}
	monitor_life(table);
	i = 0;
	while (i < table->nr_philos)
	{
		philo = &table->philos[i];
		if (pthread_join(philo->tid, NULL) != 0)
			return (PTHREAD_FAIL);
		i++;
	}
	return (0);
}
