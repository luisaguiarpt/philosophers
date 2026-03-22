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
	int				nr_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				meal_limit;
	unsigned long	start_time;
	bool			dinner_finished;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	state;
}				t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal_end;
	pthread_t		tid;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	t_table			*table;
}				t_philo;

typedef enum e_error
{
	SUCCESS,
	NOARGS,
	XSARGS,
	INV_VALUE,
	MALLOC_FAIL,
	PTHREAD_FAIL,
	MUTEX_FAIL,
	TIME_FAIL,
	NEG_TIME,
	INV_N_PHILO,
	INV_MEAL,
	PTHREAD_PHILO,
	PTHREAD_MONITOR
}				t_error;

void	one_philo(t_table *t);

// parse.c - Input parsing
int		parse(t_table *table, int ac, char **av);

// init.c - Initializers
int		init(t_table *table);

// utils.c - Utils
bool	is_error(t_error error_code);
int		print_msg(t_error err);

// exit.c - Exit functions
void	destroy_forks(t_table *table, int end);

#endif
