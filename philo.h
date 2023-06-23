#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int id;
	int done;
	int n_philo;
	unsigned long long last_meal;
	pthread_mutex_t fork;
	pthread_mutex_t *print;
	unsigned long long n_meals;
	int check;
	unsigned long long max_tto_eat;
	unsigned long long time_to_die;
	unsigned long long time_to_eat;
	unsigned long long time_to_sleep;
	pthread_t philos;
	struct s_philo *next;
} t_philo;

// ---------------- LIST -----------------

t_philo *ft_lstlast(t_philo *lst);
t_philo *ft_lstnew(int ac, char **av);
void ft_lstadd_front(t_philo **lst, t_philo *new);
void ft_lstadd_back(t_philo **lst, t_philo *new);

// ---------------------------------------

unsigned long in_time(void);
int my_sleep(unsigned int t_todo);
int check_eating(t_philo *philo);

// ---------------------------------------

long ft_atoi(char *str);

#endif
