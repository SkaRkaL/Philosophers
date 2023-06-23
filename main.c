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
	philo->last_meal = 0;
	// philo->check = 0;
	philo->max_tto_eat = 0;
	if (ac == 6)
		philo->max_tto_eat = ft_atoi(av[5]);
	philo->next = NULL;
	if (philo->n_philo < 1 || philo->time_to_die < 0 || philo->time_to_eat < 0 || philo->time_to_sleep < 0 || philo->max_tto_eat < 0)
		return (NULL);
	return (philo);
}

void print(char *doing, t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%zu	%d %s\n", in_time(philo->current), philo->id, doing);
	pthread_mutex_unlock(philo->print);
}

void *routin(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// philo->last_meal = get_time();
	// if(philo->id % 2)
	// 	usleep(philo->time_to_eat * 1000);
	while (1)
	{
		// STILL UPDATING ....
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
			break;
		print("is sleeping", philo);
		my_sleep(philo, philo->time_to_sleep);
		print("is thinking", philo);
	}
	return NULL;
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

void init_philo(t_philo *philo)
{
	t_philo *tmp;
	pthread_mutex_t print;
	pthread_mutex_init(&print, NULL);

	int i;

	i = 0;
	tmp = philo;
	
	while (i < philo->n_philo)
	{
		// usleep(1000);
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
		if (pthread_create(&(philo)->philos, NULL, &routin, philo) == -1)
			return ;
		usleep(50);
		philo = philo->next;
		i++;
	}
	// usleep(philo->time_to_eat * 1000);

	while (1)
	{
		if (philo->max_tto_eat && check_eating(philo))
		{
			ft_free(philo);
			break ;
		}
		pthread_mutex_lock(&(philo)->eat);
		if (philo->time_to_die <= get_time() - philo->last_meal)
		{
			pthread_mutex_lock(philo->print);
			printf("%zu	%d died\n", in_time(philo->current), philo->id);
			ft_free(philo);
			break ;
		}
		pthread_mutex_unlock(&(philo)->eat);
		usleep(500);
		philo = philo->next;
	}
}

int main(int ac, char **av)
{
	int i = 0;
	int n_philos;
	t_philo *philo;
	if (ac < 5 || ac > 6)
		return (write(2, "Error\n", 7), 1);
	philo = NULL;
	n_philos = ft_atoi(av[1]);
	while (i < n_philos)
	{
		ft_lstadd_back(&philo, ft_lstnew(ac, av));
		ft_lstlast(philo)->id = i + 1;
		i++;
	}
	ft_lstlast(philo)->next = philo;
	init_philo(philo);
	free(philo);
	return (0);
}
