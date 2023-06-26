/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:44:20 by sakarkal          #+#    #+#             */
/*   Updated: 2023/06/26 01:46:56 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	int					done;
	int					n_philo;
	unsigned long long	last_meal;
	unsigned long long	current;
	pthread_mutex_t		fork;
	pthread_mutex_t		*print;
	pthread_mutex_t		eat;
	unsigned long long	n_meals;
	int					check;
	unsigned long long	max_tto_eat;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	pthread_t			philos;
	struct s_philo		*next;
}						t_philo;

// ---------------- LIST -----------------

t_philo			*ft_lstlast(t_philo *lst);
t_philo			*ft_lstnew(int ac, char **av);
void			ft_lstadd_front(t_philo **lst, t_philo *new);
void			ft_lstadd_back(t_philo **lst, t_philo *new);

// ---------------------------------------

unsigned long	in_time(unsigned long var);
unsigned long	get_time(void);
int				my_sleep(t_philo *philo, unsigned int t_todo);
int				check_eating(t_philo *philo);

// ---------------------------------------

long			ft_atoi(char *str);

#endif
