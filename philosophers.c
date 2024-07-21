/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:05:09 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/21 17:37:42 by natrijau         ###   ########.fr       */
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
		data->data_philo[i].time_last_eat = data->start_time;
		pthread_create(&threads[i], NULL, round_table, &data->data_philo[i]);
		i++;
	}
	i = 0;	
	while (i < nb_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	if (data->dead_id == 1)
		printf("%ld %d died\n", data->hour_of_death, data->id_philo_death);
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
	free_all(&data);
	return (0);
}
