/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:15:24 by natrijau          #+#    #+#             */
/*   Updated: 2024/07/19 14:16:02 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tab;

	if (nmemb > 65535 && size > 65535)
		return (NULL);
	if (nmemb * size > 2147483647)
		return (NULL);
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_bzero((void *)tab, nmemb * size);
	return ((void *)tab);
}

long int	ft_atoi(const char *nptr)
{
	long int	i;
	long int	nb;
	long int	max_long;

	i = 0;
	nb = 0;
	max_long = 2147483647;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = (nb * 10) + (nptr[i] - 48);
		if (nb > max_long)
			return (-1);
		i++;
	}
	return (nb);
}

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

bool	all_positiv_num(char **av)
{
	int			i;
	long int	args;

	i = 1;
	while (i <= 4)
	{
		args = ft_atoi(av[i]);
		if (args < 0)
			return (false);
		i++;
	}
	if (av[5])
	{
		args = ft_atoi(av[5]);
		if (args < 0)
			return (false);
	}
	return (true);
}
