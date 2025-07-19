#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>	// pthread & pthread_mutex functions
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <unistd.h>	// write, usleep
# include <sys/time.h>	// gettimeofday
# include <stdbool.h>	// booleans

typedef struct s_table
{
	int		nbr_philos;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		meal_limit;
	s_philo	**philos;
}				t_table;

typedef struct s_philo
{
	int		last_meal;
	int		time_to_die;
	int		time_to_sleep;
	bool	dead;
}				t_philo;

typedef enum e_exit_status
{
	SUCCESS,
	NOARGS,
	XSARGS
}				t_exit_status;
#endif
