#include "philo.h"

void	*start_routine(void *data);

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	int			a;
	int			b;

	a = 1;
	b = 2;
	pthread_create(&tid1, NULL, &start_routine, (void *)&a);
	pthread_create(&tid2, NULL, &start_routine, (void *)&b);
	pthread_detach(tid1);
	pthread_detach(tid2);
}

void	*start_routine(void *data)
{
	int *idata = (int *)data;

	printf("This thread received argument %d\n", *idata);
	return ((void *)data);
}
