#include "philo.h"

void	print_msg(t_philo *p, t_prt_code code)
{
	if (!p->t->print)
		return ;
	mutex_fct(&p->t->print_mtx, LOCK, p->t);
	if (code == EAT)
		printf("[%ld] %d is eating\n", get_elapsed(p->t), p->id);
	if (code == SLEEP)
		printf("[%ld] %d is sleeping\n", get_elapsed(p->t), p->id);
	if (code == THINK)
		printf("[%ld] %d is thinking\n", get_elapsed(p->t), p->id);
	if (code == DIE)
	{
		printf("[%ld] %d died\n", get_elapsed(p->t), p->id);
		p->t->print = 0;
	}
	if (code == FORK && DEBUG == 0)
		printf("[%ld] %d has picked up a fork\n", get_elapsed(p->t), p->id);
	if (code == FORKD && DEBUG == 0)
		printf("[%ld] %d has put down up a fork\n", get_elapsed(p->t), p->id);
	mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
}

void	print_fork(t_philo *p, t_fork *f, t_prt_code code)
{
	if (!DEBUG)
		return ;
	mutex_fct(&p->t->print_mtx, LOCK, p->t);
	if (code == FORK)
		printf("[%lu] %i has picked up fork %i\n", get_elapsed(p->t), p->id, f->id);
	if (code == FORKD)
		printf("[%lu] %i has put down fork %i\n", get_elapsed(p->t), p->id, f->id);
	if (code == WAIT)
		printf("[%lu] %i is waiting for fork %i\n", get_elapsed(p->t), p->id, f->id);
	mutex_fct(&p->t->print_mtx, UNLOCK, p->t);
}
