#include "philo.h"

void	init_table(t_table *t, int ac, char **av)
{
	t->forks = NULL;
	t->philos = NULL;
	t->dinner_on = 0;
	mutex_f(t, &t->mtxid, INIT);
	set_start_time(t);
	parse(t, ac, av);
	init_forks(t);
	init_philos(t);
}

void	init_forks(t_table *t)
{
	int	i;

	t->forks = ft_calloc(t->nbr_philos + 1, sizeof(t_fork *));
	if (!t->forks)
		exit_error(t, CALLOCFAIL);
	i = -1;
	while (++i < t->nbr_philos)
	{
		t->forks[i] = ft_calloc(1, sizeof(t_fork));
		if (!t->forks[i])
		{
			free_forks(t);
			exit_error(t, CALLOCFAIL);
		}
		t->forks[i]->fork_id = i;
		mutex_f(t, &t->forks[i]->mtxid, INIT);
	}
}

void	init_philos(t_table *t)
{
	int		i;

	t->philos = ft_calloc(t->nbr_philos + 1, sizeof(t_philo *));
	if (!t->philos)
		exit_error(t, CALLOCFAIL);
	i = -1;
	while (++i < t->nbr_philos)
	{
		t->philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!t->philos[i])
		{
			free_philos(t);
			exit_error(t, CALLOCFAIL);
		}
		t->philos[i]->id = i + 1;
		t->philos[i]->dead = false;
		t->philos[i]->t = t;
		t->philos[i]->meals_eaten = 0;
		assign_forks(t->philos[i]);
		mutex_f(t, &t->philos[i]->mtxid, INIT);
		set_last_meal_time(t->philos[i]);
		init_philo_thread(t, &t->philos[i]->tid, t->philos[i]);
		printf("Created philo %d\n", i + 1);
		printf("Philo %d has fork %d and %d\n", t->philos[i]->id, t->philos[i]->fork1->fork_id, 
				t->philos[i]->fork2->fork_id);
	}
}

void	assign_forks(t_philo *p)
{
	t_fork	**forks;

	forks = p->t->forks;
	if (p->id % 2 == 0)
	{
		p->fork1 = forks[p->id - 1];
		p->fork2 = forks[p->id % p->t->nbr_philos];
	}
	else
	{
		p->fork1 = forks[p->id % p->t->nbr_philos];
		p->fork2 = forks[p->id - 1];
	}
}

void	init_philo_thread(t_table *t, pthread_t *tid, t_philo *p)
{
	int	ret;

	ret = pthread_create(tid, NULL, eat_sleep_think_repeat, p);
	if (ret)
		exit_error(t, PTHREAD_FAIL);
}
