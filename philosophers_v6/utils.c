/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 15:41:54 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/28 15:41:55 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_error(t_error error_code)
{
	if (error_code == 0)
		return (false);
	return (true);
}

int	print_msg(t_error err)
{
	if (err == NOARGS || err == XSARGS)
	{
		printf("Incorrect input.\n");
		printf("Usage: \"./philo nbr_of_philos time_to_die");
		printf(" time_to_eat time_to_sleep [meal_limit]\"\n");
	}
	else if (err == INV_VALUE)
		printf("Invalid input values passed\n");
	else if (err == MALLOC_FAIL)
		printf("Malloc failed\n");
	else if (err == PTHREAD_FAIL)
		printf("Pthread failed\n");
	else if (err == MUTEX_FAIL)
		printf("Mutex failed\n");
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}
