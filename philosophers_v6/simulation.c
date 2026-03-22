#include "philo.h"

bool	is_dead(t_philo *philo)
{
	bool	dead;


	pthread_mutex_lock(table->state);
	if (get_elapsd)
}

void	*monitor_life(void *table)
{
	int		i;
	int		full_philos;

	while (dinner_ongoing(table))
	{
		i = 0;
		full_philos = 0;
		while (i < table->nr_philos && dinner_ongoing(table))
		{
			if (is_dead(table->philos[i]))
				return ;
			if (is_full(table->philos[i]))
				full_philos++;
			if (all_full(table))
				return ;
		}
	}
}

int	run_simulation(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nr_philos)
	{
		philo = table->philos[i];
		if (pthread_create(&philo->tid, NULL, philo_life, philo) != 0)
			return (PTHREAD_FAIL);
		i++;
	}
	monitor_life(table);]
	i = 0;
	while (i < table->nr_philos)
	{
		philo = table->philos[i];
		if (pthread_join(philo->tid, null) != 0)
			return (PTHREAD_FAIL);
		i++;
	}
	return (0);
}
