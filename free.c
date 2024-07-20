/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:03:18 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/19 13:43:04 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex_philo(t_data *data)
{
	unsigned int	i;

	i = 1;
	if (!data->data_philo->number_of_philosophers)
		return ;
	while (i < data->data_philo->number_of_philosophers)
	{
		if (&data->data_philo[i].nb_eat)
			pthread_mutex_destroy(&data->data_philo[i].nb_eat);
		i++;
	}
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	// if (&data->print)
	// 	pthread_mutex_destroy(&data->print);
	// if (&data->dead)
	// 	pthread_mutex_destroy(&data->dead);
	// destroy_mutex_philo(data);
	if (data->mutex)
		free(data->mutex);
	if (data->data_philo)
		free(data->data_philo);
	if (data->nb_eat)
		free(data->nb_eat);
}
