#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define THREAD_NUM 10

pthread_mutex_t mutexFuel;
int fuel = 50;

pthread_mutex_t mutexWater;
int water = 0;

 void *routine(void *args)
{
	if (rand() % 2 == 0)
	{
		pthread_mutex_lock(&mutexFuel);
		sleep(1);
		pthread_mutex_lock(&mutexWater);
	}
	else {
		pthread_mutex_lock(&mutexWater);
		sleep(2);
		pthread_mutex_lock(&mutexFuel);
	}
	fuel += 50;
	water = fuel;
	printf("Incremented_fuel_to: { %d },\t", fuel);
	printf("and_set_water_to: { %d }\n", water);
	pthread_mutex_unlock(&mutexWater);
	pthread_mutex_unlock(&mutexFuel);
	return 0;
}


int main(int argc, char *argv[]) 
{
	pthread_t th[THREAD_NUM];
	pthread_mutex_init(&mutexFuel, NULL);
	int i;
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
		}
	}

	for (i = 0; i < THREAD_NUM; i++) 
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread");
		}
	}
	printf("Fuel >> %d\n", fuel);
	printf("Water >> %d\n", water);
	pthread_mutex_destroy(&mutexFuel);
	return 0;
}
