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

typedef struct	s_philo	t_philo;
typedef struct	s_fork	t_fork;

typedef struct	s_table
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_limit;
	unsigned long	start_time;
	bool			dinner_on;
	int				meals_finished;
	pthread_mutex_t	state_mtx;
	pthread_mutex_t	print_mtx;
	t_philo			*philos;
	t_fork			*forks;
	pthread_t		monitor;
}				t_table;

typedef struct	s_philo
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal_start;
	pthread_t		tid;
	pthread_mutex_t	meal_mtx;
	t_table			*t;
	t_fork			*fork1;
	t_fork			*fork2;
}				t_philo;

typedef struct	s_fork
{
	pthread_mutex_t	mtxid;
}				t_fork;

typedef enum e_exit_status
{
	SUCCESS,
	NOARGS,
	XSARGS,
	INV_VALUE,
	CALLOCFAIL,
	PTHREAD_FAIL,
	TIME_FAIL,
	NEG_TIME,
	INV_N_PHILO,
	INV_MEAL,
	PTHREAD_PHILO,
	MUTEX_FAIL
}				t_exit_status;

typedef enum	e_mtx_code
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK
}				t_mtx_code;

typedef enum	e_thr_code
{
	CREATE,
	JOIN,
	DETACH
}				t_thr_code;

// Testing/Debug functions - debug.c
void		test_parse(t_table *t);
void		test_times(t_table *t);
void		test_structs(t_table *t);

// Dinner related functions - philo.c
void		prepare_philos(t_table *t);
void		*philo_life(void *philo);

// Time related functions - time.c
unsigned long 	get_curr_time_ms(void);
unsigned long 	get_elapsed(t_table *t);
unsigned long 	get_time_since_last_meal(t_philo *p);

// Initializer functions - init.c
void			init_table(t_table *t);
void			init_philos(t_table *t);
void			init_forks(t_table *t);
void			assign_forks(t_table *t, int i);

// Utilities - utils.c
void			*safe_calloc(size_t nmemb, size_t size, t_table *t);

// Parsing - parse.c
void			parse(t_table *t, int ac, char **av);

// Thread functions utils - threads.c
void			mutex_fct(pthread_mutex_t *mtxid, t_mtx_code code, t_table *t);
void			init_philo_thread(t_philo *p);

// Exiting - exit.c
void			exit_error(t_table *t, t_exit_status err);

#endif
