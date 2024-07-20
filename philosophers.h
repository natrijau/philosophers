/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:29:29 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/19 14:32:12 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define LOCK	pthread_mutex_lock
# define UNLOCK	pthread_mutex_unlock

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

typedef struct s_philosophers	t_philosophers;
typedef struct s_data			t_data;

typedef struct s_philosophers
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nb_max_meal;
	unsigned int	id_philosphers;
	long int		start_dead;
	pthread_mutex_t	my_fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	nb_eat;
	t_data			*data;
}	t_philosophers;

typedef struct s_data
{
	int				dead_id;
	long int		start_time;
	long int		time_die;
	unsigned int	id_philo_die;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*nb_eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	t_philosophers	*data_philo;
}	t_data;

/*philosopher.c*/
bool			check_arg(int ac, char **av);
int				get_thread(t_data *data);
int				main(int ac, char **av);

/*philosophers_utils.c*/
long int		my_time(void);
void			print_alone(t_data *data);
void			print_dead(t_philosophers *philo);
void			print_message(t_philosophers *philo, char *action);
void			ft_usleep(t_philosophers *philo, long int mili_second);

/*free.c*/
void			free_all(t_data *data);

/*init.c*/
void			ft_bzero(void *s, size_t n);
void			init_philo(t_data *data, char **av);
int				init_thread(t_data *data, int number_philo);

/*lib.c*/
void			*ft_calloc(size_t nmemb, size_t size);
long int		ft_atoi(const char *nptr);
bool			its_integer(char *str);
bool			all_positiv_num(char **av);

/*thread.c*/
bool			check_dead_and_meal(t_philosophers *philo);
void			ft_eating(t_philosophers *philo);
void			sleeping(t_philosophers *philo);
void			thinking(t_philosophers *philo);
void			*round_table(void *arg);

/*DEL AFTER -- test.c*/
void			print_test_init(t_data *data);
#endif 
