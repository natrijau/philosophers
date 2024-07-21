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
	long int time_max;
	if (flag == 3)
		UNLOCK(&philo->data->dead);

	//temps a ne pas depasser
	LOCK(&philo->data->time);
	time_max = philo->time_last_eat + philo->time_to_die / 1000;
	UNLOCK(&philo->data->time);

	// compare present time and spent time since last meal
	LOCK(&philo->data->dead);
	if ((my_time() > time_max)
		&& philo->data->dead_id == 0)
	{
		philo->data->dead_id = 1;
		UNLOCK(&philo->data->dead);
		if (flag == 1)
			UNLOCK(&philo->my_fork);
		if (flag == 2)
		{
			UNLOCK(philo->next_fork);
			UNLOCK(&philo->my_fork);
		}
		print_dead(philo);
		return (false);
	}
	UNLOCK(&philo->data->dead);
	return (true);
}

bool	check_dead_and_meal(t_philosophers *philo)
{
	//check if value dead true
	LOCK(&philo->data->dead);
	if (philo->data->dead_id == 1)
	{
		UNLOCK(&philo->data->dead);
		return (true);
	}
	UNLOCK(&philo->data->dead);

	//check and of all eating
	LOCK(&philo->data->dead);
	if (philo->data->all_philo_eat == 0)
	{
		UNLOCK(&philo->data->dead);
		return (true);
	}
	UNLOCK(&philo->data->dead);
	return (false);
}

void	ft_eating(t_philosophers *philo)
{
	LOCK(&philo->my_fork);

	//check firt time if dead and unlock first fork
	if (!life_time_limit_test(philo, 1))
		return ;

	print_message(philo, "has taken a fork\n");
	LOCK(philo->next_fork);
	
	//check second time if dead and unlock second adn first fork
	if (!life_time_limit_test(philo, 2))
		return ;

	print_message(philo, "has taken a fork\n");
	
	//check another time if dead and unlock second adn first fork
	if (!life_time_limit_test(philo, 2))
		return ;

	print_message(philo, "is eating\n");
	
	//reinitialize last eat
	LOCK(&philo->data->time);
	philo->time_last_eat = my_time();
	UNLOCK(&philo->data->time);

	ft_usleep(philo, philo->time_to_eat);

	// unlock forks after eat
	UNLOCK(philo->next_fork);
	UNLOCK(&philo->my_fork);

	// minus all eat philo
	LOCK(&philo->data->dead);
	if (philo->data->all_philo_eat > 0)
		philo->data->all_philo_eat--;
	UNLOCK(&philo->data->dead);
}

void	sleeping(t_philosophers *philo)
{
	print_message(philo, "is sleeping\n");
	ft_usleep(philo, philo->time_to_sleep);
}

void	thinking(t_philosophers *philo)
{
	long int test;
	if (philo->number_of_philosophers % 2 == 1)
	{
		print_message(philo, "is thinking\n");
		test = philo->time_to_sleep - philo->time_to_eat;
		if (test <= 0)
			test *= -1;
		ft_usleep(philo, test);
	}
	else
		print_message(philo, "is thinking\n");
}

void	*round_table(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *) arg;

	// initialize first time 
	LOCK(&philo->data->time);
	philo->time_last_eat = my_time();
	UNLOCK(&philo->data->time);

	// odd philo (impair) start after once
	if (philo->id_philosphers % 2 == 0)
	{
		// thinking(philo);
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

		// thisnking(philo);
		print_message(philo, "is thinking\n");

		LOCK(&philo->data->dead);
		if (life_time_limit_test(philo, 3))
			break ;		
		UNLOCK(&philo->data->dead);
	}
	pthread_exit(EXIT_SUCCESS);
}
