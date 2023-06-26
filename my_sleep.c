/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:44:17 by sakarkal          #+#    #+#             */
/*   Updated: 2023/06/26 01:44:18 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_sleep(t_philo *philo, unsigned int t_todo)
{
	unsigned long	time;

	time = in_time(philo->current);
	while (1)
	{
		if (in_time(philo->current) - time >= t_todo)
			return (1);
		usleep(50);
	}
	return (0);
}
