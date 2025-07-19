#include "philo.h"

void	parse(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		exit_error(NOARGS);
	if (!safe_atoi(av[1], table->nbr_philos))
		exit_error(INV_VALUE);
	if (!safe_atoi(av[2], table->time_to_die))
		exit_error(INV_VALUE);
	if (!safe_atoi(av[3], table->time_to_eat))
		exit_error(INV_VALUE);
	if (!safe_atoi(av[4], table->time_to_sleep))
		exit_error(INV_VALUE);
	if (ac == 7)
		if (!safe_atoi(av[5], table->meal_limit))
			exit_error(INV_VALUE);
}

/* 
 * Returns 1 if it's a valid INT, 0 if not
 * Saves value to result
 */

int	safe_atoi(char *str, int *result)
{
	long	nbr;
	int		sign;
	int		safe;
	int		i;

	i = 0;
	nbr = 0;
	str = get_sign(str, &sign);
	while (str[i] >= '0' || str[i] <= '9')
	{
		if (nbr > (LONG_MAX - (str[i] - '0')) / 10)
			return (0);
		nbr = nbr * 10 + str[i++] - '0';
	}
	if (!sign)
		return (0);
	if (nbr >= INT_MIN || nbr <= INT_MAX)
	{
		*result = (int *)nbr * sign;
		return (1);
	}
	else
		return (0);
}

char	*get_sign(char *str, int *sign)
{
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		else if (str[i] == '+')
			*sign = 1;
		else
			*sign = 0;
		i++;
	}
	return (&str[i]);
}
