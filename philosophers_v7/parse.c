#include "philo.h"

static char	*get_sign(char *str, int *sign);
static int	safe_atoi(char *str, int *result);
static int	check_values(t_table *t, int ac);

int	parse(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return(NOARGS);
	if (ac == 5)
		table->meal_limit = -1;
	if (!safe_atoi(av[1], &table->nr_philos))
		return(INV_VALUE);
	if (!safe_atoi(av[2], &table->time_to_die))
		return(INV_VALUE);
	if (!safe_atoi(av[3], &table->time_to_eat))
		return(INV_VALUE);
	if (!safe_atoi(av[4], &table->time_to_sleep))
		return(INV_VALUE);
	if (ac == 6)
	{
		if (!safe_atoi(av[5], &table->meal_limit))
			return(INV_VALUE);
	}
	return (check_values(table, ac));
}

static int	check_values(t_table *t, int ac)
{
	if (t->time_to_die < 0 || t->time_to_eat < 0 || t->time_to_sleep < 0)
		return(NEG_TIME);
	if (t->nr_philos <= 0)
		return(INV_N_PHILO);
	if (t->nr_philos == 1)
		one_philo(t);
	if (ac == 6 && t->meal_limit < 0)
		return(INV_MEAL);
	return (0);
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

