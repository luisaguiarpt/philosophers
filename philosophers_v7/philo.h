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
	bool			*free_forks;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	state;
}				t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal;
	pthread_t		tid;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	bool			*fork1_free;
	bool			*fork2_free;
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
	NEG_TIME,
	INV_N_PHILO,
	INV_MEAL
}				t_error;

void	one_philo(t_table *t);

// parse.c - Input parsing
int		parse(t_table *table, int ac, char **av);

// init.c - Initializers
int		init(t_table *table);

// simulation.c - Main sim functions
int		run_simulation(t_table *table);
void	*monitor_life(void *_table);
void	*philo_life(void *_philo);
void	eat(t_philo *philo);
void	sleepy(t_philo *philo);
void	think(t_philo *philo);

// simulation_utils.c - Sim helpers
bool	dinner_ongoing(t_table *table);
bool	is_dead(t_philo *philo);
bool	is_full(t_philo *philo);
bool	all_full(t_table *table, int full_philos);

// printers.c - Printing with mutex
void	print_death(t_philo *philo);
void	print_fork(t_philo *philo);
void	print_eating(t_philo *philo);
void	print_sleeping(t_philo *philo);
void	print_thinking(t_philo *philo);
void	print_fork_down(t_philo *philo);

// time.c - Time related functions
void	precise_usleep(unsigned long ms);
unsigned long	get_curr_time_ms(void);
unsigned long	get_elapsed(t_table *t);

// utils.c - Utils
bool	is_error(t_error error_code);
int		print_msg(t_error err);

// exit.c - Exit functions
void	destroy_forks(t_table *table, int end);

#endif
