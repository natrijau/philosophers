/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:16:33 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/19 14:38:33 by natrijau         ###   ########.fr       */
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
	printf("0 1 take fork\n");
	printf("%d 1 dead\n", data->data_philo->time_to_die / 1000);
}

void	print_dead(t_philosophers *philo, long int start)
{
	LOCK(&philo->data->print);
	printf("%ld %d dead\n", my_time() - start, philo->id_philosphers);
	UNLOCK(&philo->data->print);
}

void	print_message(t_philosophers *philo, char *action)
{
	long int	actual_time;

	actual_time = my_time() - philo->data->start_time;
	LOCK(&philo->data->dead);
	if (philo->data->dead_id != 1 /*&& philo->nb_max_meal > 0*/)
	{
		UNLOCK(&philo->data->dead);
		LOCK(&philo->data->print);
		printf("%ld %d %s", actual_time, philo->id_philosphers, action);
		UNLOCK(&philo->data->print);
		return ;
	}
	UNLOCK(&philo->data->dead);
}

void	ft_usleep(t_philosophers *philo, long int mili_second)
{
	long int	start;

	start = my_time();
	while (my_time() - start < mili_second / 1000)
	{
		usleep(1000);
		LOCK(&philo->data->dead);
		if (philo->data->dead_id == 0)
		{
			if ((my_time() > philo->start_dead + philo->time_to_die / 1000))
			{
				philo->data->dead_id = 1;
				UNLOCK(&philo->data->dead);
				print_dead(philo, start);
				break ;
			}
		}
		if (philo->data->dead_id == 1)
		{
			UNLOCK(&philo->data->dead);
			break ;
		}
		UNLOCK(&philo->data->dead);
	}
}
