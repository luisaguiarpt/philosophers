/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 15:41:12 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/28 15:41:13 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_philo *philo)
{
	unsigned long	elapsed;

	elapsed = get_elapsed(philo->table);
	ft_putnbr_fd(elapsed, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" died\n", 1);
	pthread_mutex_unlock(&philo->table->write);
}

void	print_fork(t_philo *philo)
{
	unsigned long	elapsed;

	elapsed = get_elapsed(philo->table);
	if (!dinner_ongoing(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->write);
	ft_putnbr_fd(elapsed, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
	pthread_mutex_unlock(&philo->table->write);
}

void	print_eating(t_philo *philo)
{
	unsigned long	elapsed;

	elapsed = get_elapsed(philo->table);
	if (!dinner_ongoing(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->write);
	ft_putnbr_fd(elapsed, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is eating\n", 1);
	pthread_mutex_unlock(&philo->table->write);
}

void	print_sleeping(t_philo *philo)
{
	unsigned long	elapsed;

	elapsed = get_elapsed(philo->table);
	if (!dinner_ongoing(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->write);
	ft_putnbr_fd(elapsed, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is sleeping\n", 1);
	pthread_mutex_unlock(&philo->table->write);
}

void	print_thinking(t_philo *philo)
{
	unsigned long	elapsed;

	elapsed = get_elapsed(philo->table);
	if (!dinner_ongoing(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->write);
	ft_putnbr_fd(elapsed, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is thinking\n", 1);
	pthread_mutex_unlock(&philo->table->write);
}
