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

void *routin(void *arg)
{
	t_philo *tmp;
	int f = 0;
	tmp = (t_philo *)arg;
	pthread_mutex_lock(tmp->mutex);
	for (int i = 1; i < 4; i++)
	{
		f++;
		printf("------| F 9abla >> %d |-------\n", f);
	}
	printf("\nThread Finished  < 1 >\n-");
	printf("\n||||||||||||||||||||||||||||||||||||\n\n");
	pthread_mutex_unlock(tmp->mutex);
	return NULL;
}

void init_philo(t_philo *philo, int n_philo)
{
	t_philo *tmp;
	pthread_mutex_t mutex;
	int i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	tmp = philo;
	while (i < n_philo)
	{
		tmp->mutex = &mutex;
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		if (pthread_create(&(tmp)->philos, NULL, &routin, tmp))
			return;
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		if (pthread_join(tmp->philos, NULL) != 0)
			return;
		i++;
	}
	pthread_mutex_destroy(&mutex);
}

int main(int ac, char **av)
{
	int i = 0;
	int n_philos;
	t_philo *philo;
	if (ac < 5 || ac > 6)
		exit(write(2, "Error\n", 7));
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
	for (int j = 1; av[j]; j++)
	{
		printf("%s ", av[j]);
	}
	printf("\n");

	return (0);
}
