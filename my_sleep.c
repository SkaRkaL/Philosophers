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
