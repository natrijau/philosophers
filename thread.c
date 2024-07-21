/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:18:27 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/21 17:48:18 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	life_time_limit_test(t_philosophers *philo, int flag)
{
	if (flag == 3)
		UNLOCK(&philo->data->dead);
	if (my_time() > philo->start_dead + philo->time_to_die / 1000)
	{
		LOCK(&philo->data->dead);
		if (philo->data->dead_id == 0)
		{
			philo->data->dead_id = 1;
			UNLOCK(&philo->data->dead);
			if (flag == 1)
			{
				if ((philo->id_philosphers % 2 == 0) && (philo->number_of_philosophers % 2 == 0)
					&& (philo->number_of_philosophers == philo->id_philosphers))
					UNLOCK(philo->next_fork);
				else
					UNLOCK(&philo->my_fork);
			}
			if (flag == 2)
			{
				if ((philo->id_philosphers % 2 == 0) && (philo->number_of_philosophers % 2 == 0)
					&& (philo->number_of_philosophers == philo->id_philosphers))
				{
					UNLOCK(&philo->my_fork);
					UNLOCK(philo->next_fork);				
				}
				else
				{
					UNLOCK(philo->next_fork);
					UNLOCK(&philo->my_fork);
				}
			}
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
	// LOCK(&philo->nb_eat);
	LOCK(&philo->data->dead);
	if (philo->data->all_philo_eat == 0)
	{
		UNLOCK(&philo->data->dead);
		// UNLOCK(&philo->nb_eat);
		return (true);
	}
	UNLOCK(&philo->data->dead);
	// UNLOCK(&philo->nb_eat);
	return (false);
}

void	ft_eating(t_philosophers *philo)
{
	if ((philo->id_philosphers % 2 == 0) && (philo->number_of_philosophers % 2 == 0)
		&& (philo->number_of_philosophers == philo->id_philosphers))
		LOCK(philo->next_fork);
	else
		LOCK(&philo->my_fork);
	if (!life_time_limit_test(philo, 1))
		return ;
	print_message(philo, "has taken a fork\n");
	if ((philo->id_philosphers % 2 == 0) && (philo->number_of_philosophers % 2 == 0)
		&& (philo->number_of_philosophers == philo->id_philosphers))
		LOCK(&philo->my_fork);
	else
		LOCK(philo->next_fork);
	if (!life_time_limit_test(philo, 2))
		return ;
	print_message(philo, "has taken a fork\n");
	if (!life_time_limit_test(philo, 2))
		return ;
	print_message(philo, "is eating\n");
	LOCK(&philo->data->dead);
	philo->start_dead = my_time();
	UNLOCK(&philo->data->dead);
	ft_usleep(philo, philo->time_to_eat);

	if ((philo->id_philosphers % 2 == 0) && (philo->number_of_philosophers % 2 == 0)
		&& (philo->number_of_philosophers == philo->id_philosphers))
	{
		UNLOCK(&philo->my_fork);
		UNLOCK(philo->next_fork);
	}	
	else
	{
		UNLOCK(philo->next_fork);
		UNLOCK(&philo->my_fork);
	}

	// LOCK(&philo->nb_eat);
	LOCK(&philo->data->dead);
	if (philo->data->all_philo_eat > 0)
		philo->data->all_philo_eat--;
	// UNLOCK(&philo->nb_eat);
	UNLOCK(&philo->data->dead);
}

void	sleeping(t_philosophers *philo)
{
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
	if (philo->id_philosphers % 2 == 1)
	{
		print_message(philo, "is thinking\n");
		usleep(500);
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
		if (philo->id_philosphers % 2 == 0 
			&& (((philo->time_to_eat / 1000 + philo->time_to_sleep / 1000) + philo->time_to_eat / 1000) >= philo->time_to_die / 1000))
		{
			print_message(philo, "is thinking\n");
			ft_usleep(philo, (philo->time_to_eat / 1000 + philo->time_to_sleep / 1000) + philo->time_to_eat /1000);
			LOCK(&philo->data->dead);
			philo->data->dead_id = 1;
			UNLOCK(&philo->data->dead);
			print_dead(philo);
			break;
		}
		else
			print_message(philo, "is thinking\n");			
		// LOCK(&philo->data->dead);
		// if (life_time_limit_test(philo, 3))
		// 	break ;		
		// UNLOCK(&philo->data->dead);
	}
	pthread_exit(EXIT_SUCCESS);
}
