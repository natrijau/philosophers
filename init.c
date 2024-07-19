/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:05:00 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/19 14:12:59 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*stock;

	i = 0;
	stock = (unsigned char *)s;
	while (i < n)
	{
		stock[i] = '\0';
		i++;
	}
}

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
		data->data_philo[i].nb_max_meal = -1;
		if (av[5])
			data->data_philo[i].nb_max_meal = ft_atoi(av[5]);
		data->data_philo[i].id_philosphers = i + 1;
		data->data_philo[i].my_fork = data->mutex[i];
		data->data_philo[i].data = data;
		data->data_philo[i].start_dead = 0;
		pthread_mutex_init(&data->data_philo[i].nb_eat, NULL);
		pthread_mutex_init(&data->data_philo[i].last_eat, NULL);
		pthread_mutex_init(&data->mutex[i], NULL);
		data->data_philo[i].next_fork = &data->data_philo[i + 1].my_fork;
		i++;
	}
	data->data_philo[i - 1].next_fork = &data->data_philo[0].my_fork;
}

int	init_thread(t_data *data, int number_philo)
{
	ft_bzero(data, sizeof(t_data));
	data->mutex = calloc(sizeof(pthread_mutex_t), number_philo);
	if (!data->mutex)
	{
		printf("Error malloc\n");
		return (1);
	}
	data->nb_eat = calloc(sizeof(pthread_mutex_t), number_philo);
	if (!data->nb_eat)
	{
		printf("Error malloc\n");
		return (1);
	}
	data->data_philo = calloc(sizeof(t_philosophers), number_philo);
	if (!data->data_philo)
	{
		printf("Error malloc\n");
		return (1);
	}
	data->dead_id = 0;
	data->start_time = my_time();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	return (0);
}
