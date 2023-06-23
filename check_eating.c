#include "philo.h"

int check_eating(t_philo *philo)
{
	int i;
	int ate;

	i = 0;
	ate = 0;
	while (i < philo->n_philo)
	{
		pthread_mutex_lock(&philo->eat);
		if (philo->n_meals >= philo->max_tto_eat)
			ate++;
		pthread_mutex_unlock(&philo->eat);
		philo = philo->next;
		i++;
	}
	if (ate == philo->n_philo)
		return (1);
	return (0);
}
