#include "philo.h"

int	main(int ac, char **av)
{
	t_table	t;

	parse(&t, ac, av);
	init_table(&t);
	init_forks(&t);
	init_philos(&t);
	prepare_philos(&t);
}

void	prepare_philos(t_table *t)
{
	int		i;

	i = -1;
	t->start_time = get_curr_time_ms();
	while (++i < t->n_philos)
	{
		t->philos[i].last_meal_start = t->start_time;
		init_philo_thread(&t->philos[i]);
	}
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	mutex_fct(&p->t->print_mtx, LOCK, p->t);
	printf("Philosopher %d is born\n", p->id);
	mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
	while (!get_dinner_status(p->t))
		usleep(50);
	while (get_dinner_status(p->t) && !meals_finished(p->t))
	{
		take_forks(p);
		eat(p);
	}
	return (NULL);
}
