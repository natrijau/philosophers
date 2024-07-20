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
	LOCK(&philo->data->dead);
	philo->start_dead = my_time();
	UNLOCK(&philo->data->dead);
	LOCK(&philo->my_fork);
	print_message(philo, "take fork\n");
	LOCK(philo->next_fork);
	print_message(philo, "take fork\n");
	print_message(philo, "eat\n");
	ft_usleep(philo, philo->time_to_eat);
	// if (philo->id_philosphers % 2 == 0)
	// {
	// 	UNLOCK(&philo->my_fork);
	// 	UNLOCK(philo->next_fork);
	// }
	UNLOCK(philo->next_fork);
	UNLOCK(&philo->my_fork);
	LOCK(&philo->nb_eat);
	if (philo->nb_max_meal > 0)
		philo->nb_max_meal--;
	UNLOCK(&philo->nb_eat);
}

void	sleeping(t_philosophers *philo)
{
	
	print_message(philo, "start sleeping\n");
	ft_usleep(philo, philo->time_to_sleep);
	// LOCK(&philo->data->print);
	// printf("\ndead id %d\n", philo->data->dead_id);
	// UNLOCK(&philo->data->print);	
	// print_message(philo, "thinking\n");
	// usleep(100);
}

void	thinking(t_philosophers *philo)
{
	if (check_dead_and_meal(philo))
		return ;
	print_message(philo, "thinking\n");
}

void	*round_table(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *) arg;
	LOCK(&philo->data->dead);
	philo->start_dead = my_time();
	UNLOCK(&philo->data->dead);
	if (philo->id_philosphers % 2 == 0)
		usleep(100);	
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
		thinking(philo);
	}
	pthread_exit(EXIT_SUCCESS);
}
