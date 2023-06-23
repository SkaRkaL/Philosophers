#include "philo.h"

int	my_sleep(unsigned int t_todo)
{
	unsigned long	time;

	time = in_time();
	while (1)
	{
		if (in_time() - time >= t_todo)
			return (1);
		usleep(100);
	}
	return (0);
}
