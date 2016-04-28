#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

#define MAX_SEATS 4
#define MAX_ACTION 100

struct ReadingRoom
{
	sem_t mutex, full, empty;
	int seats;
	int waits;
	ReadingRoom();
};

class Semaphore
{
	int sem;

};

ReadingRoom::ReadingRoom()
{
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, MAX_SEATS);
	sem_init(&empty, 0, 0);
	seats = MAX_SEATS;
	waits = 0;
}

void* enter(void *arg)
{
	ReadingRoom *room = (ReadingRoom*)arg; 
	sem_wait(&room->full);
	sem_wait(&room->mutex);
	room->seats --;
	cout<<"One reader enters the reading room!"<<endl;
	cout<<"Current Status:"<<endl;
	cout<<"seats: "<<room->seats<<endl;
	cout<<"readers in the room: "<<MAX_SEATS-room->seats<<endl;
	sem_post(&room->mutex);
	sem_post(&room->empty);
}

void* leave(void *arg)
{
	ReadingRoom *room = (ReadingRoom*)arg;
	sem_wait(&room->empty);
	sem_wait(&room->mutex);
	room->seats++;
	cout<<"One reader leaves the reading room!"<<endl;
	cout<<"Current Status:"<<endl;
	cout<<"seats: "<<room->seats<<endl;
	cout<<"readers in the room: "<<MAX_SEATS-room->seats<<endl;
	sem_post(&room->mutex);
	sem_post(&room->full);
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
