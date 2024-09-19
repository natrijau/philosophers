/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:35:27 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/25 11:50:43 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_dead_and_meal(t_philosophers *philo)
{
	LOCK(&philo->data->meal);
	if ((int)philo->nb_max_meal == 0)
	{
		UNLOCK(&philo->data->meal);
		if (philo->data->nb_philo_eat == (int)philo->number_of_philosophers)
			return (true);
		philo->data->nb_philo_eat++;
	}
	UNLOCK(&philo->data->meal);
	LOCK(&philo->data->dead);
	if (philo->data->dead_id == 1)
	{
		UNLOCK(&philo->data->dead);
		return (true);
	}
	UNLOCK(&philo->data->dead);
	return (false);
}

void	unlock_two_fork(t_philosophers *philo)
{
	UNLOCK(philo->next_fork);
	UNLOCK(&philo->my_fork);
}

void	lock_one_fork(t_philosophers *philo, int flag)
{
	if (flag == 1)
		LOCK(&philo->my_fork);
	else
		LOCK(philo->next_fork);
}

void	unlock_one_fork(t_philosophers *philo, int flag)
{
	if (flag == 1)
		UNLOCK(&philo->my_fork);
	else
		UNLOCK(philo->next_fork);
}
