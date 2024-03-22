/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:16:33 by natrijau          #+#    #+#             */
/*   Updated: 2024/03/22 11:36:16 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	unsigned int	nb;

	i = 0;
	nb = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = (nb * 10) + (nptr[i] - 48);
		i++;
	}
	return (nb);
}

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
		return;
	// if (data->data_args->number_of_philosophers)
	// 	free(data->data_args->number_of_philosophers);
	// if (data->data_args->time_to_die)
	// 	free(data->data_args->time_to_die);
	// if (data->data_args->time_to_eat)
	// 	free(data->data_args->time_to_eat);
	// if (data->data_args->time_to_sleep)
	// 	free(data->data_args->time_to_sleep);
	// if (data->data_args->number_of_times_each_philosopher_must_eat)
	// 	free(data->data_args->number_of_times_each_philosopher_must_eat);
	if (data->id_fork)
		free(data->id_fork);
	if (data->data_args)
		free(data->data_args);		
	// if (data)
	// 	free(data);
}