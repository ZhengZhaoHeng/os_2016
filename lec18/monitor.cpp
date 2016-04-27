#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

#define MAX_SEATS 100
#define MAX_ACTION 100

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

void* enter(void *arg)
{
	ReadingRoom *room = (ReadingRoom*)arg; 
	pthread_mutex_lock(&room->lock);
	while(room->seats == 0)
		pthread_cond_wait(&room->notFull, &room->lock);
	room->seats --;
	pthread_cond_signal(&room->notEmpty);
	pthread_mutex_unlock(&room->lock);
	cout<<"One reader enters the reading room!"<<endl;
}

void* leave(void *arg)
{
	ReadingRoom *room = (ReadingRoom*)arg; 
	pthread_mutex_lock(&room->lock);
	while(room->seats == MAX_SEATS)
		pthread_cond_wait(&room->notEmpty, &room->lock);
	room->seats ++;
	pthread_cond_signal(&room->notFull);
	pthread_mutex_unlock(&room->lock);
	cout<<"One reader leaves the reading room!"<<endl;	
}

int main()
{
	ReadingRoom room;

	pthread_t action[MAX_ACTION];

	srand(time(0));
	for(int i = 0; i < MAX_ACTION; i++)
	{
		int type = rand()%2;
		if(type == 0)
			pthread_create(&action[i], NULL, &enter, &room);
		else
			pthread_create(&action[i], NULL, &leave, &room);
		sleep(1);
	}

	for(int i = 0; i <MAX_ACTION; i++)
		pthread_join(action[i], NULL);
}
