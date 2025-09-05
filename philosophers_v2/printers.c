#include "philo.h"

void	print_msg(t_philo *p, t_prt_code code)
{
	mutex_fct(&p->t->print_mtx, LOCK, p->t);
	if (code == EAT)
		printf("[%ld] %d is eating\n", get_elapsed(p->t), p->id);
	if (code == SLEEP)
		printf("[%ld] %d is sleeping\n", get_elapsed(p->t), p->id);
	if (code == THINK)
		printf("[%ld] %d is thinking\n", get_elapsed(p->t), p->id);
	if (code == DIE)
		printf("[%ld] %d died\n", get_elapsed(p->t), p->id);
	if (code == FORK)
		printf("[%ld] %d has picked up a fork\n", get_elapsed(p->t), p->id);
	if (code == FORKD)
		printf("[%ld] %d has put down up a fork\n", get_elapsed(p->t), p->id);
	mutex_fct(&p->t->print_mtx, UNLOCK, p->t);

}
