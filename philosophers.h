#ifndef		PHILOSOPHERS_H
# define	PHILOSOPHERS_H

/*printf*/
# include <stdio.h>

/*usleep*/
# include <unistd.h>

/*gettimeofday*/
# include <sys/time.h>

/*bool*/
# include <stdbool.h>

/*malloc*/
# include <stdlib.h>

/*thread*/
# include <pthread.h>

typedef struct s_philosophers
{
	unsigned int	id_philosphers;
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
} t_philosophers;

typedef struct s_data
{
	pthread_t		thread;
	int				*id_fork;
	t_philosophers	*data_args;
} t_data;

/*philosophers_utils.c*/
unsigned int	ft_atoi(const char *nptr);
void			free_all(t_data *data);


#endif 
