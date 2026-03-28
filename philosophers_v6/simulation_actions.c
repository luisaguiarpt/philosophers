/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 15:41:36 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/28 15:41:37 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	print_fork(philo);
	pthread_mutex_lock(philo->fork2);
	print_fork(philo);
	pthread_mutex_lock(&philo->table->state);
	philo->last_meal = get_curr_time_ms();
	if (philo->meals_eaten >= 0)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->state);
	print_eating(philo);
	precise_usleep((unsigned long)philo->table->time_to_eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	sleepy(t_philo *philo)
{
	print_sleeping(philo);
	precise_usleep((unsigned long)philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_thinking(philo);
}
