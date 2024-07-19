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

void	free_split(int	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->mutex)
		free(data->mutex);
	if (data->data_philo)
		free(data->data_philo);
	if (data->nb_eat)
		free(data->nb_eat);
}
