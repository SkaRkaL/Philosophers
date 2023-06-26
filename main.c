/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:44:14 by sakarkal          #+#    #+#             */
/*   Updated: 2023/06/26 01:48:25 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *doing, t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%zu	%d %s\n", in_time(philo->current), philo->id, doing);
	pthread_mutex_unlock(philo->print);
}

void	*routin(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->fork));
		print("has taken a fork", philo);
		pthread_mutex_lock(&(philo->next->fork));
		print("has taken a fork", philo);
		pthread_mutex_lock(&(philo)->eat);
		philo->last_meal = get_time();
		philo->n_meals++;
		pthread_mutex_unlock(&(philo)->eat);
		print("is eating", philo);
		my_sleep(philo, philo->time_to_eat);
		pthread_mutex_unlock(&(philo->next->fork));
		pthread_mutex_unlock(&(philo->fork));
		if (philo->max_tto_eat && philo->max_tto_eat < philo->n_meals)
			break ;
		print("is sleeping", philo);
		my_sleep(philo, philo->time_to_sleep);
		print("is thinking", philo);
	}
	return (NULL);
}

void	killer(t_philo *philo)
{
	while (1)
	{
		if (philo->max_tto_eat && check_eating(philo))
			break ;
		pthread_mutex_lock(&(philo)->eat);
		if (philo->time_to_die <= get_time() - philo->last_meal)
		{
			pthread_mutex_lock(philo->print);
			printf("%zu	%d died\n", in_time(philo->current), philo->id);
			return ;
		}
		pthread_mutex_unlock(&(philo)->eat);
		usleep(500);
		philo = philo->next;
	}
}

void	init_philo(t_philo *philo)
{
	pthread_mutex_t	print;
	int				i;

	i = 0;
	pthread_mutex_init(&print, NULL);
	while (i < philo->n_philo)
	{
		philo->print = &print;
		philo->current = get_time();
		philo->last_meal = get_time();
		pthread_mutex_init(&(philo->fork), NULL);
		pthread_mutex_init(&(philo->eat), NULL);
		philo = philo->next;
		i++;
	}
	i = 0;
	while (i < philo->n_philo)
	{
		pthread_create(&(philo)->philos, NULL, &routin, philo);
		usleep(50);
		pthread_detach(philo->philos);
		philo = philo->next;
		i++;
	}
	killer(philo);
}

int	main(int ac, char **av)
{
	int		i;
	int		n_philos;
	t_philo	*philo;

	i = 0;
	if (ac < 5 || ac > 6)
		return (write(2, "Error\n", 7), 1);
	philo = NULL;
	n_philos = ft_atoi(av[1]);
	if (n_philos == 0)
		return (-1);
	while (i < n_philos)
	{
		ft_lstadd_back(&philo, ft_lstnew(ac, av));
		ft_lstlast(philo)->id = i + 1;
		i++;
	}
	ft_lstlast(philo)->next = philo;
	init_philo(philo);
	return (0);
}
