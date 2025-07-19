#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>	// pthread & pthread_mutex functions
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <unistd.h>	// write, usleep
# include <sys/time.h>	// gettimeofday
# include <stdbool.h>	// booleans
# include <limits.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int		nbr_philos;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		meal_limit;
	t_philo	**philo;
}				t_table;

typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	mtxid;
	int				last_meal_end;
	bool			dead;
	t_table			*table;
}				t_philo;

typedef enum e_exit_status
{
	SUCCESS,
	NOARGS,
	XSARGS,
	INV_VALUE,
	CALLOCFAIL
}				t_exit_status;

// Initializers - init.c
void	init_philos(t_table *table);

// Parsing - parse.c
void	parse(t_table *table, int ac, char **av);

// Exit - exit.c
void	exit_error(t_exit_status err);

// Utilities - utils.c
void	*ft_calloc(size_t nmemb, size_t size);
void	free_philos(t_philo **tab);

#endif
