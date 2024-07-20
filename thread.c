/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:18:27 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/19 14:25:23 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	life_time_limit_test(t_philosophers *philo, int flag)
{
	if (my_time() > philo->start_dead + philo->time_to_die / 1000)
	{
		LOCK(&philo->data->dead);
		if (philo->data->dead_id == 0)
		{
			philo->data->dead_id = 1;
			UNLOCK(&philo->data->dead);
			if (flag == 1)
				UNLOCK(&philo->my_fork);
			if (flag == 2)
			{
				UNLOCK(&philo->my_fork);
				UNLOCK(philo->next_fork);
			}
			LOCK(&philo->data->dead);
			print_dead(philo);
			return (false);
		}
		UNLOCK(&philo->data->dead);
	}
	return (true);
}

bool	check_dead_and_meal(t_philosophers *philo)
{
	LOCK(&philo->data->dead);
	if (philo->data->dead_id == 1)
	{
		UNLOCK(&philo->data->dead);
		return (true);
	}
	UNLOCK(&philo->data->dead);
	LOCK(&philo->nb_eat);
	if (philo->nb_max_meal == 0)
	{
		UNLOCK(&philo->nb_eat);
		return (true);
	}
	UNLOCK(&philo->nb_eat);
	return (false);
}

void	ft_eating(t_philosophers *philo)
{
	LOCK(&philo->my_fork);
	print_message(philo, "has taken a fork\n");
	if (!life_time_limit_test(philo, 1))
		return ;
	LOCK(philo->next_fork);
	print_message(philo, "has taken a fork\n");
	if (!life_time_limit_test(philo, 2))
		return ;
	print_message(philo, "is eating\n");
	if (!life_time_limit_test(philo, 2))
		return ;
	LOCK(&philo->data->dead);
	philo->start_dead = my_time();
	UNLOCK(&philo->data->dead);
	ft_usleep(philo, philo->time_to_eat);
	UNLOCK(philo->next_fork);
	UNLOCK(&philo->my_fork);
	LOCK(&philo->nb_eat);
	if (philo->nb_max_meal > 0)
		philo->nb_max_meal--;
	UNLOCK(&philo->nb_eat);
}

void	sleeping(t_philosophers *philo)
{
	if (!life_time_limit_test(philo, 0))
		return ;
	print_message(philo, "is sleeping\n");
	ft_usleep(philo, philo->time_to_sleep);
}

void	*round_table(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *) arg;
	LOCK(&philo->data->dead);
	philo->start_dead = my_time();
	UNLOCK(&philo->data->dead);
	if (philo->id_philosphers % 2 == 0)
	{
		usleep(100);
		print_message(philo, "is thinking\n");
	}
	while (1)
	{
		if (check_dead_and_meal(philo))
			break ;
		ft_eating(philo);
		if (check_dead_and_meal(philo))
			break ;
		sleeping(philo);
		if (check_dead_and_meal(philo))
			break ;
		print_message(philo, "is thinking\n");
	}
	pthread_exit(EXIT_SUCCESS);
}
