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
typedef struct s_fork	t_fork;

typedef struct s_table
{
	int				nbr_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				meal_limit;
	bool			dinner_on;
	long int		start_time;
	pthread_mutex_t	mtxid;
	t_fork			**forks;
	t_philo			**philos;
}				t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	pthread_mutex_t	mtxid;
	long int		start_time;
	long int		last_meal_end;
	bool			dead;
	t_fork			*fork1;
	t_fork			*fork2;
	t_table			*t;
}				t_philo;

typedef struct s_fork
{
	int				fork_id;
	pthread_t		tid;
	pthread_mutex_t	mtxid;
}				t_fork;

typedef enum e_thread_code
{
	CREATE,
	JOIN,
	DETACH,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK
}				t_thread_code;

typedef enum e_exit_status
{
	SUCCESS,
	NOARGS,
	XSARGS,
	INV_VALUE,
	CALLOCFAIL,
	PTHREAD_FAIL,
	TIME_FAIL
}				t_exit_status;

// Main - philo.c
void	start_dinner(t_table *t);
void	*check_life(void *table);
void	*eat_sleep_think_repeat(void *philo);
void	sleepy(t_philo *p);
void	eat(t_philo *p);
void	pickup_fork(t_philo *p, int f);
void	putdown_fork(t_philo *p, int f);

// Initializers - init.c
void	init_table(t_table *t, int ac, char **av);
void	init_forks(t_table *t);
void	init_philos(t_table *table);
void	init_philo_thread(t_table *t, pthread_t *tid, t_philo *p);

// Setters - setters.c
void	set_start_time(t_table *t);
void	set_dinner_on(t_table *t);
void	set_dinner_off(t_table *t);
void	set_last_meal_time(t_philo *p);

// Getters - getters.c
suseconds_t	get_start_time(t_table *t);
bool		get_dinner_status(t_table *t);
long int	get_milliseconds(struct timeval tv);
long int	get_elapsed(t_table *t);

// Parsing - parse.c
void	parse(t_table *table, int ac, char **av);

// Thread functions - threads.c
void	mutex_f(t_table *t, pthread_mutex_t *id, t_thread_code code);

// Exit - exit.c
void	exit_error(t_table *t, t_exit_status err);

// Utilities - utils.c
void	*ft_calloc(size_t nmemb, size_t size);
void	free_forks(t_table *t);
void	free_philos(t_table *t);

#endif
