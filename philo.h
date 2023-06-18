#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				n_philo;
	unsigned long	last_meal;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	size_t			n_meals;
	size_t			check;
	size_t			max_tto_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_t		philos;
	struct s_philo	*next;
} 		t_philo;

// ---------------- LIST -----------------

t_philo *ft_lstlast(t_philo *lst);
t_philo *ft_lstnew(int ac, char **av);
void ft_lstadd_front(t_philo **lst, t_philo *new);
void ft_lstadd_back(t_philo **lst, t_philo *new);

// ---------------------------------------

unsigned long	in_time(void);

// ---------------------------------------

long ft_atoi(char *str);

#endif
