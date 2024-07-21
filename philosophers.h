/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:29:29 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/21 16:18:04 by natrijau         ###   ########.fr       */
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
	long int		time_last_eat;
	pthread_mutex_t	my_fork;
	pthread_mutex_t	*next_fork;
	t_data			*data;
}	t_philosophers;

typedef struct s_data
{
	int				dead_id;
	long int		start_time;
	long int		hour_of_death;
	unsigned int	id_philo_death;
	unsigned int	all_philo_eat;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	time;
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

/*init.c*/
int				print_error(t_data *data, int flag);
void			ft_bzero(void *s, size_t n);
void			init_philo(t_data *data, char **av);
int				init_thread(t_data *data, int number_philo);

/*lib.c*/
void			*ft_calloc(size_t nmemb, size_t size);
long int		ft_atoi(const char *nptr);
bool			its_integer(char *str);
bool			all_positiv_num(char **av);

/*thread.c*/
bool			life_time_limit_test(t_philosophers *philo, int flag);
bool			check_dead_and_meal(t_philosophers *philo);
void			ft_eating(t_philosophers *philo);
void			sleeping(t_philosophers *philo);
void			*round_table(void *arg);

/*free.c*/
void			free_all(t_data *data);

#endif 
