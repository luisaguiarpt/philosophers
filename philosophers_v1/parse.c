#include "philo.h"

static char	*get_sign(char *str, int *sign);
static int	safe_atoi(char *str, int *result);

void	parse(t_table *t, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		exit_error(t, NOARGS);
	if (!safe_atoi(av[1], &t->nbr_philos))
		exit_error(t, INV_VALUE);
	if (!safe_atoi(av[2], &t->time_to_die))
		exit_error(t, INV_VALUE);
	if (!safe_atoi(av[3], &t->time_to_eat))
		exit_error(t, INV_VALUE);
	if (!safe_atoi(av[4], &t->time_to_sleep))
		exit_error(t, INV_VALUE);
	if (ac == 6)
	{
		if (!safe_atoi(av[5], &t->meal_limit))
			exit_error(t, INV_VALUE);
	}
	else
		t->meal_limit = -1;
}

/* 
 * Returns 1 if it's a valid INT, 0 if not
 * Saves value to result
 */

static int	safe_atoi(char *str, int *result)
{
	long	nbr;
	int		sign;
	int		i;

	i = 0;
	nbr = 0;
	str = get_sign(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nbr > (LONG_MAX - (str[i] - '0')) / 10)
			return (0);
		nbr = nbr * 10 + str[i++] - '0';
	}
	if (!sign)
		return (0);
	if ((sign < 0 && nbr <= -(long)INT_MIN) || ((sign > 0) && nbr <= INT_MAX))
	{
		*result = (int)nbr * sign;
		return (1);
	}
	else
		return (0);
}

static char	*get_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		*sign = 0;
	return (&str[i]);
}
