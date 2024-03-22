/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:05:09 by natrijau          #+#    #+#             */
/*   Updated: 2024/03/22 14:04:26 by natrijau         ###   ########.fr       */
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
		return (true);
	return(false);
}	

void	*round_table(void *arg)
{
	t_data	*data = (t_data *) arg;
	pthread_mutex_t mutex;
	unsigned int	eating_time;
	unsigned int	time_sleep;
	unsigned int	time_die;
	
	eating_time = data->data_args->time_to_eat;
	time_sleep = data->data_args->time_to_sleep;
	time_die = data->data_args->time_to_die;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	while (eating_time > 0)
	{
		printf("id_fork %d eating_time %d\n", *data->id_fork, eating_time);
		eating_time--;
	}
	pthread_mutex_unlock(&mutex);
	
	/*boucle pour le temps de sommeil*/
	while (time_sleep > 0)
	{
		pthread_mutex_lock(&mutex);
		printf("id_fork %d time_sleep %d\n", *data->id_fork, time_sleep);
		pthread_mutex_unlock(&mutex);
		time_sleep--;
	}

	/*boucle pour le temps avant la mort*/
	while (time_die > 0)
	{
		pthread_mutex_lock(&mutex);
		printf("id_fork %d time_die %d\n", *data->id_fork, time_die);
		pthread_mutex_unlock(&mutex);
		time_die--;
	}
	printf("Nous sommes dans le thread\n");
	// int	*i;
	// i = (int *) arg;
	// (*i) = (*i) * 5;
	// Arrêt propre du thread
	pthread_exit(EXIT_SUCCESS);	
}

void	get_thread(t_data *data)
{
	int	num_fork;
	num_fork = data->data_args->number_of_philosophers;
	data->id_fork = malloc(sizeof(int) * num_fork);
	// data->id_fork[num_fork];
	while (num_fork > 0)
	{
		// printf("numb of fork %d\n", num_fork);
		pthread_create(&data->thread, NULL, round_table, data);
		data->id_fork[num_fork - 1] = num_fork;
		num_fork--;
		pthread_join(data->thread, NULL);
	}
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
	get_thread(&data);
	// int	thread;
	// int	i = 1;
	// pthread_t thread1;
	// printf("Avant la création du thread. i vaut : %i\n", i);

	// /*Créer un thread*/
	// thread = pthread_create(&thread1, NULL, thread_1, &i);
	
	// // /*Récupérer un thread ou le détacher*/
	// pthread_join(thread1, NULL);
	
	// printf("La creation du thread renvoi : %d\n", thread);
	// printf("Après la création du thread. i vaut : %i\n", i);
	// for (unsigned int i = 0; i < data.data_args->number_of_philosophers; i++)
	// {
	// 	// printf("i -> %d\n", i);
	// 	printf("id de la fourchette %d\n", data.id_fork[i]);
	// 	/* code */
	// }
	
	/*//////////////////////////////////////////////////*/
	free_all(&data);
	return (0);
}