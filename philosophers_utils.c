/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:16:33 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/21 17:46:54 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	my_time(void)
{
	struct timeval	my_time;
	long int		current_time;

	gettimeofday(&my_time, NULL);
	current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);
	return (current_time);
}

void	print_alone(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(data->data_philo->time_to_die / 1000);
	printf("%d 1 died\n", data->data_philo->time_to_die / 1000);
}

void	print_dead(t_philosophers *philo)
{
	long int	actual_time;

	LOCK(&philo->data->time);
	actual_time = my_time() - philo->data->start_time;
	UNLOCK(&philo->data->time);
	philo->data->hour_of_death = actual_time;
	philo->data->id_philo_death = philo->id_philosphers;
}

void	print_message(t_philosophers *philo, char *action)
{
	long int	actual_time;

	LOCK(&philo->data->time);
	actual_time = my_time() - philo->data->start_time;
	UNLOCK(&philo->data->time);
	LOCK(&philo->data->dead);
	if (philo->data->dead_id != 1)
	{
		UNLOCK(&philo->data->dead);
		printf("%ld %d %s", actual_time, philo->id_philosphers, action);
		return ;
	}
	UNLOCK(&philo->data->dead);
}

void	ft_usleep(t_philosophers *philo, long int mili_second)
{
	long int	start;

	LOCK(&philo->data->time);
	start = my_time();
	UNLOCK(&philo->data->time);
	while (my_time() - start < mili_second / 1000)
	{
		usleep(500);
		LOCK(&philo->data->dead);
		if (philo->data->dead_id == 1)
		{
			UNLOCK(&philo->data->dead);
			break ;
		}
		// UNLOCK(&philo->data->dead);
		// LOCK(&philo->data->dead);
		if (philo->data->dead_id == 0)
		{
			if ((my_time() > philo->time_last_eat + philo->time_to_die / 1000))
			{
				philo->data->dead_id = 1;
				UNLOCK(&philo->data->dead);
				print_dead(philo);
				break ;
			}
		}
		UNLOCK(&philo->data->dead);
	}
}
