#include "philo.h"

t_philo *ft_lstnew(int ac, char **av)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->n_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->n_meals = 0;
	philo->check = 0;
	philo->max_tto_eat = 0;
	if (ac == 6)
		philo->max_tto_eat = ft_atoi(av[5]);
	philo->next = NULL;
	if (philo->n_philo < 1 || philo->time_to_die < 0 || philo->time_to_eat < 0 || philo->time_to_sleep < 0 || philo->max_tto_eat < 0)
		return (NULL);
	return (philo);
}

void	print(size_t time, char *doing, t_philo *philo)
{
		pthread_mutex_lock(philo->print);
		printf("%zu	%d %s\n", time, philo->id, doing);
		pthread_mutex_unlock(philo->print);
}

void *routin(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		// STILL UPDATING ....
		philo->last_meal = in_time();
		pthread_mutex_lock(&(philo->fork));
		print(in_time(), "Has Locking a Fork", philo);

		pthread_mutex_lock(&(philo->next->fork));
		print(in_time(), "Has Locking a Fork", philo);

		philo->last_meal = in_time();
		print(in_time(), "is eating", philo);
		usleep(philo->time_to_eat * 1000);

		pthread_mutex_unlock(&(philo->next->fork));
		pthread_mutex_unlock(&(philo->fork));
		if (philo->max_tto_eat)
			philo->n_meals++;
		if (philo->max_tto_eat && philo->max_tto_eat <= philo->n_meals)
			break ;
		print(in_time(), "Sleeping", philo);
		usleep(philo->time_to_sleep * 1000);

		print(in_time(), "Thinking", philo);
	}
	return NULL;
}

void init_philo(t_philo *philo, int n_philo)
{
	t_philo *tmp;
	pthread_mutex_t print;
	pthread_mutex_init(&print, NULL);
	
	int i;

	i = 0;
	tmp = philo;

	while (i < n_philo)
	{
		usleep(1000);
		tmp->print = &print;
		pthread_mutex_init(&(tmp->fork), NULL);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		if (pthread_create(&(tmp)->philos, NULL, &routin, tmp) == -1)
			return ;
		usleep(50);
		tmp = tmp->next;
		i++;
	}
	usleep(philo->time_to_eat);
	while (1)
	{
		if (philo->time_to_die <= in_time() - philo->last_meal)
		{
			pthread_mutex_lock(philo->print);
			printf("philo %d died.\n", philo->id);
			return;
		}
		philo = philo->next;
	}
}

int main(int ac, char **av)
{
	int i = 0;
	int n_philos;
	t_philo *philo;
	if (ac < 5 || ac > 6)
		return(write(2, "Error\n", 7), 1);
	philo = NULL;
	n_philos = ft_atoi(av[1]);
	while (i < n_philos)
	{
		ft_lstadd_back(&philo, ft_lstnew(ac, av));
		ft_lstlast(philo)->id = i + 1;
		i++;
	}
	ft_lstlast(philo)->next = philo;
	init_philo(philo, n_philos);
	return (0);
}
