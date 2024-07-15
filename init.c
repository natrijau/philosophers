/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:05:00 by natrijau          #+#    #+#             */
/*   Updated: 2024/04/09 15:57:15 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
 
void	init_philo(t_data *data, char **av)
{
	int	i;
	int	number_philo;

	number_philo = ft_atoi(av[1]);
	i = 0;
	while (i < number_philo)
	{
		data->data_philo[i].number_of_philosophers = ft_atoi(av[1]);
		data->data_philo[i].time_to_die = ft_atoi(av[2]) * 1000;	
		data->data_philo[i].time_to_eat = ft_atoi(av[3]) * 1000;	
		data->data_philo[i].time_to_sleep = ft_atoi(av[4]) * 1000;
		if (av[5])
			data->data_philo[i].number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		data->data_philo[i].id_philosphers = i + 1;
		data->data_philo[i].my_fork = data->mutex[i];
		data->data_philo[i].data = data;
		data->data_philo[i].start_dead = 0;
		data->data_philo[i].end_time = 0;
		pthread_mutex_init(&data->mutex[i], NULL);
		data->data_philo[i].next_fork = &data->data_philo[i + 1].my_fork;
		i++;
	}
	data->data_philo[i - 1].next_fork = &data->data_philo[0].my_fork;
}

void	init_thread(t_data *data, int number_philo)
{
	data->dead_id = 0;
	data->mutex = malloc(sizeof(pthread_mutex_t) * number_philo);
	data->data_philo = malloc(sizeof(t_philosophers) * number_philo);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->print, NULL);
}

// void	init_mutex(t_data *data, char **av)
// {
// 	int	num_fork;
// 	int	i;

// 	i = 0;
// 	num_fork = ft_atoi(av[1]);
// 	while (i < num_fork)
// 	{
// 		// pthread_mutex_init(data->data_philo->sleep, NULL);
// 		// pthread_mutex_init(data->data_philo->thinking, NULL);
// 		pthread_mutex_init(&data->data_philo->my_fork, NULL);
// 		pthread_mutex_init(data->data_philo->next_fork, NULL);
// 		pthread_mutex_init(&data->data_philo->print, NULL);
// 		i++;
// 	}
// }