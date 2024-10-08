/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:05:00 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/22 17:41:34 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(t_data *data, int flag)
{
	if (flag == 1 && !data->mutex)
	{
		printf("Error malloc\n");
		return (1);
	}
	if (flag == 3 && !data->data_philo)
	{
		printf("Error malloc\n");
		return (1);
	}
	return (0);
}

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
		pthread_mutex_init(&data->mutex[i], NULL);
		data->data_philo[i].next_fork = &data->data_philo[i + 1].my_fork;
		i++;
	}
	data->data_philo[i - 1].next_fork = &data->data_philo[0].my_fork;
	data->nb_philo_eat = 0;
}

int	init_thread(t_data *data, int number_philo)
{
	ft_bzero(data, sizeof(t_data));
	data->mutex = ft_calloc(sizeof(pthread_mutex_t), number_philo);
	if (print_error(data, 1) == 1)
		return (1);
	data->data_philo = ft_calloc(sizeof(t_philosophers), number_philo);
	if (print_error(data, 3) == 1)
		return (1);
	data->dead_id = 0;
	data->hour_of_death = 0;
	data->id_philo_death = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->dead, NULL);
	return (0);
}
