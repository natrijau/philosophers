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

typedef struct s_philosophers
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
} t_philosophers;

typedef struct s_data
{
	t_philosophers *data_args;
} t_data;

/*philosophers_utils.c*/
unsigned int	ft_atoi(const char *nptr);


#endif 
