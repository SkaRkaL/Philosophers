#include "philo.h"

unsigned long	in_time(void)
{
	struct timeval	time;
	static size_t init_time;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	if(init_time == 0)
		init_time = l;
	return (l - init_time);
}
