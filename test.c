/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:35:59 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/19 14:32:55 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//test init philo
void	print_test_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < (int)data->data_philo->number_of_philosophers)
	{
		printf("idphilo -> %d\n", data->data_philo[i].id_philosphers);
		printf("\ttime_to_die -> %d\n", data->data_philo[i].time_to_die);
		printf("\ttime_to_eat -> %d\n", data->data_philo[i].time_to_eat);
		printf("\ttime_to_sleep -> %d\n", data->data_philo[i].time_to_sleep);
		i++;
	}
}
