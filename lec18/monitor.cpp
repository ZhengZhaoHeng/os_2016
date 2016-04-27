#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <ctime>

using namespace std;

#define MAX_SEATS 100

struct ReadingRoom
{
	pthread_mutex_t lock;
	pthread_cond_t notFull, notEmpty;
	int seats;
	ReadingRoom();
};

ReadingRoom::ReadingRoom()
{
	lock = PTHREAD_MUTEX_INITIALIZER;
	notEmpty = PTHREAD_COND_INITIALIZER;
	notFull = PTHREAD_COND_INITIALIZER;
	seats = MAX_SEATS;
}

void enter(ReadingRoom *room)
{
	pthread_mutex_lock(room->lock);
	while(seats == 0)
		pthread_cond_wait(room->notFull, room->lock);
	seats --;
	pthread_cond_signal(room->notEmpty);
	pthread_mutex_unlock(room->lock);
}

void leave(ReadingRoom *room)
{
	pthread_mutex_lock(room->lock);
	while(seats == MAX_SEATS)
		pthread_cond_wait(room->notEmpty, room->lock);
	seats ++;
	pthread_cond_signal(room->notFull);
	pthread_mutex_unlock(room->lock);
}

int main()
{
	pthread_t action[MAX_ACTION];

	srand(time(0));
	for(int i = 0; i < MAX_ACTION; i++)
	{
		int type = rand()%2;
		if(type == 0)
			pthread_create(&action[i], NULL, &enter, NULL);
		else
			pthread_create(%action[i], NULL, &leave, NULL);
		int interval = rand()%5;
		sleep(interval);
	}

	for(int i = 0; i <MAX_ACTION; i++)
		pthread_join(action[i], NULL);
}
