#include "philo.h"

t_philo	*ft_lstnew(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->n_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->n_meals = 0;
	philo->check = 0;
	philo->next = NULL;
	if (ac == 6)
		philo->max_tto_eat = ft_atoi(av[5]);
	if (philo->n_philo < 1 || philo->time_to_die < 0 || philo->time_to_eat < 0
		|| philo->time_to_sleep < 0 || philo->max_tto_eat < 0)
		return (NULL);
	return (philo);
}

int main(int ac, char **av)
{
	int i = 0;
	int n_philos;
	t_philo	*philo;
	if (ac < 5 || ac > 6)
		exit(write(2, "Error\n", 7));

	n_philos = ft_atoi(av[1]);
	while (i < n_philos)
	{
		ft_lstadd_back(&philo, ft_lstnew(ac, av));
		ft_lstlast(philo)->index = i + 1;
		i++;
	}
	for (int j = 1; av[j]; j++)
	{
		printf("%s ", av[j]);
	}
	printf("\n");

	return (0);
}
