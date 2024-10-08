/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:05:09 by natrijau          #+#    #+#             */
/*   Updated: 2024/09/10 14:31:36 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Invalid number of arguments !\n");
		return (false);
	}
	while (av[i])
	{
		if (!its_integer(av[i]))
		{
			printf("One of the arguments is invalid !\n");
			return (false);
		}
		i++;
	}
	if (!all_positiv_num(av))
	{
		printf("One of the arguments is invalid !\n");
		return (false);
	}
	return (true);
}

void	check_dead_philo(t_data *data, unsigned int nb_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (data->nb_philo_eat == (int)nb_philo)
			break ;
		LOCK(&data->time);
		if (my_time() - data->data_philo[i].start_dead
			>= data->data_philo[i].time_to_die / 1000)
		{
			UNLOCK(&data->time);
			LOCK(&data->dead);
			data->dead_id = 1;
			UNLOCK(&data->dead);
			print_dead(&data->data_philo[i]);
			break ;
		}
		UNLOCK(&data->time);
		i++;
		if (i == nb_philo)
			i = 0;
	}
}

int	get_thread(t_data *data)
{
	unsigned int	i;
	unsigned int	nb_philo;
	pthread_t		*threads;

	nb_philo = data->data_philo->number_of_philosophers;
	threads = malloc(nb_philo * sizeof(pthread_t));
	data->start_time = my_time();
	i = 0;
	while (i < nb_philo)
	{
		LOCK(&data->time);
		data->data_philo[i].start_dead = data->start_time;
		UNLOCK(&data->time);
		pthread_create(&threads[i], NULL, round_table, &data->data_philo[i]);
		i++;
	}
	check_dead_philo(data, nb_philo);
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_arg(ac, av))
		return (1);
	if (init_thread(&data, ft_atoi(av[1])))
	{
		free_all(&data);
		return (1);
	}
	init_philo(&data, av);
	if (data.data_philo->number_of_philosophers == 1)
	{
		print_alone(&data);
		free_all(&data);
		return (0);
	}
	get_thread(&data);
	LOCK(&data.dead);
	if (data.dead_id == 1)
		printf("%ld %d died\n", data.hour_of_death, data.id_philo_death);
	UNLOCK(&data.dead);
	free_all(&data);
	return (0);
}
