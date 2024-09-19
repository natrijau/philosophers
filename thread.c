/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:18:27 by natrijau          #+#    #+#             */
/*   Updated: 2024/09/12 11:47:55 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	test_and_unlock(t_philosophers *philo, int flag)
{
	if (check_dead_and_meal(philo) && flag == 1)
	{
		unlock_one_fork(philo, 1);
		return (true);
	}
	else if (check_dead_and_meal(philo) && flag == 2)
	{
		unlock_two_fork(philo);
		return (true);
	}
	return (false);
}

void	ft_eating(t_philosophers *philo)
{
	lock_one_fork(philo, 1);
	if (test_and_unlock(philo, 1))
		return ;
	print_message(philo, "has taken a fork\n");
	lock_one_fork(philo, 2);
	if (test_and_unlock(philo, 2))
		return ;
	print_message(philo, "has taken a fork\n");
	if (test_and_unlock(philo, 2))
		return ;
	print_message(philo, "is eating\n");
	if (test_and_unlock(philo, 2))
		return ;
	LOCK(&philo->data->time);
	philo->start_dead = my_time();
	UNLOCK(&philo->data->time);
	if (!ft_usleep(philo, philo->time_to_eat, 2))
		return ;
	unlock_two_fork(philo);
	LOCK(&philo->data->meal);
	if ((int)philo->nb_max_meal > 0)
		philo->nb_max_meal--;
	UNLOCK(&philo->data->meal);
}

void	sleeping(t_philosophers *philo)
{
	if (check_dead_and_meal(philo))
		return ;
	print_message(philo, "is sleeping\n");
	ft_usleep(philo, philo->time_to_sleep, 0);
}

void	routine(t_philosophers *philo)
{
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
		if (philo->id_philosphers % 2 == 0
			&& (((philo->time_to_eat / 1000) * 2) >= philo->time_to_die / 1000))
		{
			ft_usleep(philo, philo->time_to_die - philo->time_to_eat, 0);
			LOCK(&philo->data->dead);
			philo->data->dead_id = 1;
			UNLOCK(&philo->data->dead);
			print_dead(philo);
			break ;
		}
	}
}

void	*round_table(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *) arg;
	LOCK(&philo->data->time);
	philo->start_dead = my_time();
	UNLOCK(&philo->data->time);
	if (philo->id_philosphers % 2 == 0)
	{
		print_message(philo, "is thinking\n");
		usleep(200);
		LOCK(&philo->data->time);
		philo->start_dead = my_time();
		UNLOCK(&philo->data->time);
	}
	routine(philo);
	pthread_exit(EXIT_SUCCESS);
}
