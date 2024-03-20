/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:05:09 by natrijau          #+#    #+#             */
/*   Updated: 2024/03/20 12:57:33 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
// float time_diff(struct timeval *start, struct timeval *end) {
//   return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
// }

bool	its_integer(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);	
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (false);
		i++;
	}
	return (true);
}

bool	init_arg(t_data *data, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!its_integer(av[i]))
			return (false);			
		i++;
	}
	data->data_args->number_of_philosophers = ft_atoi(av[1]);	
	data->data_args->time_to_die = ft_atoi(av[2]);	
	data->data_args->time_to_eat = ft_atoi(av[3]);	
	data->data_args->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->data_args->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);	
	return (true);
}

bool	check_arg(int ac, t_data *data)
{
	(void)data;
	data->data_args = malloc(sizeof(t_philosophers));
	if (ac == 5 || ac == 6)
	{
		// data->data_args = NULL;
		// data->data_args->number_of_philosophers = NULL;
		return (true);
	}
	return(false);
}	

int	main(int ac, char **av)
{
	t_data data;
	if (!check_arg(ac, &data))
	{
		printf("Invalid number of arguments !\n");
		return (1);
	}
	if (!init_arg(&data, av))
	{
		printf("One of the arguments is invalid !\n");
		return (1);
	}
	printf("nombre de philosophes -> %d\n", data.data_args->number_of_philosophers);
	printf("time_to_die -> en milisecondes %d\n", data.data_args->time_to_die);
	printf("time_to_eat -> en milisecondes %d\n", data.data_args->time_to_eat);
	printf("time_to_sleep -> en milisecondes %d\n", data.data_args->time_to_sleep);
	if (av[5])
		printf("number_of_times_each_philosopher_must_eat -> %d\n", data.data_args->number_of_times_each_philosopher_must_eat);
	
	// /* TEST usleep */
	// unsigned int mSeconds = 1000000;
    // int returnCode;
    // returnCode = usleep(mSeconds);
	// printf("temps ecoule en milisec -> %dmicrosecondes\nEn sec -> %dsec", mSeconds, mSeconds / 1000000 );
	// printf("\nusleep result -> %d\n", returnCode);	
	// /* TEST gettimeofday */
	// struct timeval start;
	// struct timeval end;

	// /*
	// start.tv_sec pour les secondes
	// start.tv_usec pour les micro secondes
	// idem pour end ...
	// */


	// gettimeofday(&start, NULL);
   	// usleep(mSeconds);
	// gettimeofday(&end, NULL);


	// printf("temps passe entre :%f sec\n", time_diff(&start, &end));

	/*TEST pthread_create*/
	
	
	return (0);
}