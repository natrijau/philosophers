/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:03:18 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/21 16:17:56 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (&data->print)
		pthread_mutex_destroy(&data->print);
	if (&data->dead)
		pthread_mutex_destroy(&data->dead);
	if (data->mutex)
		free(data->mutex);
	if (data->data_philo)
		free(data->data_philo);
}
