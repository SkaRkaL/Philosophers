/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:44:04 by sakarkal          #+#    #+#             */
/*   Updated: 2023/06/26 01:49:11 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned long	in_time(unsigned long var)
{
	struct timeval		time;
	unsigned long long	l;
	unsigned long long	s;
	unsigned long long	u;

	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	return (l - var);
}

void	ft_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_philo)
	{
		free(philo);
		philo = philo->next;
		i++;
	}
}
