/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:05:09 by natrijau          #+#    #+#             */
/*   Updated: 2024/04/09 16:41:08 by natrijau         ###   ########.fr       */
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
		return(false);
	}
	//! rajouter le test max philo
	return(true);
}	

void	check_dead(t_philosophers *philo, int flag)
{
	if (flag == 0)
	{
		philo->start_dead = 0;
		if (philo->time_to_eat >= philo->time_to_die)
		{
			// printf("\teating\tLe philosophe %d alive ? %d\n",philo->id_philosphers, philo->alive);
			// philo->alive = false;
			philo->end_time = philo->time_to_die / 1000;
		}
	}
	if (flag == 1)
	{
		philo->start_dead += philo->time_to_sleep + philo->time_to_eat;
		if (philo->start_dead >= philo->time_to_die
			|| philo->time_to_sleep >= philo->time_to_die)
		{
			// philo->alive = false;
			// printf("\tsleeping\tLe philosophe %d alive ? %d\n",philo->id_philosphers, philo->alive);
			philo->end_time = philo->time_to_die / 1000;
		}
	}
}

// void	ft_usleep(t_philosophers *philo, long int mili_second)
// {
// 	(void) philo;
// 	(void) mili_second;
// 	struct timeval my_time;
//   	long int current_time;
//   	long int i;

// 	gettimeofday(&my_time, NULL);
// 	current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);
// 	printf("current time %lu\n", current_time);
// 	i = 0;
// 	// printf("i %ld\n", i);
	
// 	while (i < mili_second / 1000)
// 	{
// 		usleep(170);
// 		gettimeofday(&my_time, NULL);
// 		i = ((my_time.tv_sec * 1000) + (my_time.tv_usec / 1000)) - philo->start_time;
// 		// printf("i %ld\n", i);
// 	}
// }

long int	my_time()
{
	struct timeval my_time;
  	long int current_time;
	gettimeofday(&my_time, NULL);

	current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);
	return (current_time);	
}

void	ft_eating(t_philosophers *philo)
{
  	long int current_time;

	pthread_mutex_lock(&philo->my_fork);
	pthread_mutex_lock(&philo->print);
	current_time = my_time();
	if (philo->data->dead_id != 1)
		printf("%ld %d take fork\n",current_time - philo->start_time,  philo->id_philosphers);
	pthread_mutex_unlock(&philo->my_fork);
	pthread_mutex_lock(philo->next_fork);
	if (philo->data->dead_id != 1)
		printf("%ld %d take fork\n",current_time - philo->start_time,  philo->id_philosphers);
	pthread_mutex_unlock(philo->next_fork);
	pthread_mutex_unlock(&philo->print);
	if (philo->data->dead_id > 0)
	{
		//!unlock les mutex
		pthread_mutex_unlock(&philo->my_fork);
		pthread_mutex_unlock(philo->next_fork);
		return;
	}

	philo->number_of_times_each_philosopher_must_eat--;
	while ((my_time() - philo->start_dead) < philo->time_to_die / 1000)
	{
		// if ((my_time() - philo-> start_time) > )
		// 	philo->data->dead_id = 1;
		
		usleep(500);
	}
	pthread_mutex_lock(&philo->print);
	if (philo->data->dead_id != 1)
		printf("%ld %d eat\n",my_time() - philo->start_time,  philo->id_philosphers);
	pthread_mutex_unlock(&philo->print);	
	philo->start_dead = my_time();
	// if (philo->time_to_die <= philo->time_to_eat)
	// {
	// 	printf("%ld\tLe philosophe %d start eat \n",current_time - philo->start_time,  philo->id_philosphers);
	// 	usleep(philo->time_to_die);
	// 	philo->end_time += philo->time_to_die / 1000;
	// 	pthread_mutex_lock(&philo->print);
	// 	philo->data->dead_id += 1;
	// 	if (philo->data->dead_id == 1)
	// 		printf("%ld Le philosophe %d est MORTTTTTTTTTTTT !\n", philo->end_time, philo->id_philosphers);
	// 	pthread_mutex_unlock(&philo->print);
		
	// 	pthread_mutex_unlock(&philo->my_fork);
	// 	pthread_mutex_unlock(philo->next_fork);
	// 	return ;
	// }	
	// pthread_mutex_lock(&philo->print);
	// if (philo->data->dead_id == 0)
	// {
	// 	printf("%ld\tLe philosophe %d take fork ! \n",current_time - philo->start_time,  philo->id_philosphers);
	// 	printf("%ld\tLe philosophe %d take second fork ! \n",current_time - philo->start_time,  philo->id_philosphers);
	// 	printf("%ld\tLe philosophe %d start eat \n",current_time - philo->start_time,  philo->id_philosphers);
	// 	usleep(philo->time_to_eat);
	// }
	// philo->start_dead = philo->time_to_eat;
	// pthread_mutex_unlock(&philo->print);
	// pthread_mutex_unlock(&philo->my_fork);
	// pthread_mutex_unlock(philo->next_fork);
}

void	sleeping(t_philosophers *philo)
{
  	long int current_time;

	pthread_mutex_lock(&philo->print);
	current_time = my_time();
	if (philo->data->dead_id != 1)
		printf("%ld %d start sleeping\n",current_time - philo->start_time,  philo->id_philosphers);
	pthread_mutex_unlock(&philo->print);

	while ((my_time() - philo->start_dead) < philo->time_to_die / 1000)
	{
		usleep(500);
	}
	// pthread_mutex_lock(&philo->print);
	// gettimeofday(&my_time, NULL);
	// current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);
	// // check_dead(philo, 1);
	
	// if (philo->start_dead + philo->time_to_sleep >= philo->time_to_die)
	// {
	// 	// printf("fonction sleeping\n\tphilo->start_dead + philo->time_to_sleep %ld =? %d philo->time_to_die\nphilo->data->dead_id %d\n", philo->start_dead + philo->time_to_sleep, philo->time_to_die, philo->data->dead_id);
	// 	philo->data->dead_id += 1;
	// 	// philo->end_time += philo->time_to_die / 1000;
	// 	// pthread_mutex_lock(&philo->print);
	// 	// printf("%ld\tLe philosophe %d start sleep !\n",current_time - philo->start_time, philo->id_philosphers);
	// 	// pthread_mutex_unlock(&philo->print);
	// 	// pthread_mutex_lock(&philo->print);
	// 	// if (philo->data->dead_id == 1)
	// 		// printf("%ld Le philosophe %d est MORTTTTTTTTTTTT !\n", philo->end_time, philo->id_philosphers);
	// 	// pthread_mutex_unlock(&philo->print);
	// 	return ;
	// }
	// if (philo->data->dead_id == 0)
	// {
	// 	printf("%ld\tLe philosophe %d start sleep !\n",current_time - philo->start_time, philo->id_philosphers);
	//     usleep(philo->time_to_sleep);
	// }
	// philo->start_dead = current_time - philo->start_time;
	// // ft_usleep(philo, philo->time_to_sleep);
	// pthread_mutex_unlock(&philo->print);
}

void	thinking(t_philosophers *philo)
{
  	long int current_time;

	pthread_mutex_lock(&philo->print);
	current_time = my_time();
	if (philo->data->dead_id != 1)
		printf("%ld %d thinking\n",current_time - philo->start_time,  philo->id_philosphers);
	pthread_mutex_unlock(&philo->print);

	// struct timeval my_time;
  	// long int current_time;
	// pthread_mutex_lock(&philo->print);
	// gettimeofday(&my_time, NULL);
	// current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);
	// // philo->end_time = current_time - philo->start_time;
	// if (philo->start_dead >= philo->time_to_die / 1000)
	// {
	// 	philo->end_time = philo->time_to_die / 1000;
	// 	philo->data->dead_id += 1;
	// }
	// if (philo->data->dead_id == 0)
	// 	printf("%ld\tLe philosophe %d think !\n",(current_time - philo->start_time),  philo->id_philosphers);
	// pthread_mutex_unlock(&philo->print);
}

void	*round_table(void *arg)
{
	t_philosophers	*philo = (t_philosophers *) arg;
	philo->start_time = my_time();
	if (philo->id_philosphers % 2 == 0)
		thinking(philo);
	while (1)
	{
		ft_eating(philo);					
		sleeping(philo);
		thinking(philo);
		// if(philo->number_of_times_each_philosopher_must_eat == 0)
		// 	break;
		
		pthread_mutex_lock(&philo->print);
		printf("philo->data->dead_id %d\n", philo->data->dead_id);
		if (philo->data->dead_id > 0)
		{
			pthread_mutex_unlock(&philo->print);
			break;
		}
		pthread_mutex_unlock(&philo->print);
	}
	
	pthread_exit(EXIT_SUCCESS);	
}

int get_thread(t_data *data)
{
    unsigned int num_fork;
    pthread_t *threads = malloc(data->data_philo->number_of_philosophers * sizeof(pthread_t));

    // Créer tous les threads
    for (num_fork = 0; num_fork < data->data_philo->number_of_philosophers; num_fork++)
    {
        pthread_create(&threads[num_fork], NULL, round_table, &data->data_philo[num_fork]);
    }

    // Attendre que tous les threads se terminent
    for (num_fork = 0; num_fork < data->data_philo->number_of_philosophers; num_fork++)
    {
        pthread_join(threads[num_fork], NULL);
    }

    free(threads);
    return 0;
}

void	alone(t_data *data)
{
	printf("0\t 1 take fork\n");
	printf("%d\t 1 take fork\n", data->data_philo->time_to_die / 1000);
}

int	main(int ac, char **av)
{
	t_data data;
	if (!check_arg(ac, av))
		return (1);
	init_thread(&data, ft_atoi(av[1]));
	init_philo(&data, av);
	if (data.data_philo->number_of_philosophers == 1)
	{
		//! en boolean
		alone(&data);
		free_all(&data);
		return (0);
	}
	
	// print_test_init(&data);
	get_thread(&data);
	// free_all(&data);
	return (0);
}