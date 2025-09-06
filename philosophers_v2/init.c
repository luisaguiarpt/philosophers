#include "philo.h"

void	init_table(t_table *t)
{
	t->dinner_on = true;
	t->meals_finished = 0;
	t->start_time = 0;
	t->ready = 0;
	mutex_fct(&t->state_mtx, INIT, t);
	mutex_fct(&t->print_mtx, INIT, t);
	mutex_fct(&t->time_mtx, INIT, t);
}

void	init_philos(t_table *t)
{
	int	i;

	t->philos = safe_calloc(t->n_philos, sizeof(t_philo), t);
	i = -1;
	while (++i < t->n_philos)
	{
		t->philos[i].id = i + 1;
		t->philos[i].t = t;
		t->philos[i].meals_eaten = 0;
		t->philos[i].held_forks = 0;
		assign_forks(t, i);
		mutex_fct(&t->philos[i].meal_mtx, INIT, t);
	}
	i = -1;
	while (++i < t->n_philos)
		init_philo_thread(&t->philos[i]);
}

void	init_forks(t_table *t)
{
	int	i;

	t->forks = safe_calloc(t->n_philos, sizeof(t_fork), t);
	i = -1;
	while (++i < t->n_philos)
	{
		mutex_fct(&t->forks[i].mtxid, INIT, t);
	}
}

void	assign_forks(t_table *t, int i)
{
	if (i % 2 == 0)
	{
		sleep(1);
		t->philos[i].fork1 = &t->forks[i];
		t->philos[i].fork2 = &t->forks[(i + 1) % t->n_philos];
		printf("Philo %i has fork %i and %i\n", t->philos[i].id, i, (i + 1) % t->n_philos);
	}
	else
	{
		t->philos[i].fork1 = &t->forks[(i + 1) % t->n_philos];
		t->philos[i].fork2 = &t->forks[i];
		printf("Philo %i has fork %i and %i\n", t->philos[i].id, i, (i + 1) % t->n_philos);
	}
}
