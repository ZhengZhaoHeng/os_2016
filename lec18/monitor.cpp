#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

#define MAX_SEATS 4
#define MAX_ACTION 100

struct ReadingRoom
{
	pthread_mutex_t lock;
	pthread_cond_t notFull, notEmpty;
	int seats;
	int waits;
	ReadingRoom();
};

ReadingRoom::ReadingRoom()
{
	lock = PTHREAD_MUTEX_INITIALIZER;
	notEmpty = PTHREAD_COND_INITIALIZER;
	notFull = PTHREAD_COND_INITIALIZER;
	seats = MAX_SEATS;
	waits = 0;
}

void* enter(void *arg)
{
	ReadingRoom *room = (ReadingRoom*)arg; 
	pthread_mutex_lock(&room->lock);
	while(room->seats == 0)
	{
		room->waits ++;
		cout<<"One reader waits in the reading room!"<<endl;
		cout<<"Current Status:"<<endl;
		cout<<"seats: "<<room->seats<<endl;
		cout<<"readers in the room: "<<MAX_SEATS-room->seats<<endl;
		cout<<"readers waiting "<<room->waits<<endl<<endl;
		pthread_cond_wait(&room->notFull, &room->lock);
		room->waits --;
	}
	room->seats --;
	pthread_cond_signal(&room->notEmpty);
	cout<<"One reader enters the reading room!"<<endl;
	cout<<"Current Status:"<<endl;
	cout<<"seats: "<<room->seats<<endl;
	cout<<"readers in the room: "<<MAX_SEATS-room->seats<<endl;
	cout<<"readers waiting "<<room->waits<<endl<<endl;
	pthread_mutex_unlock(&room->lock);
}

void* leave(void *arg)
{
	ReadingRoom *room = (ReadingRoom*)arg; 
	pthread_mutex_lock(&room->lock);
	if(room->seats == MAX_SEATS)
	{
		pthread_mutex_unlock(&room->lock);
		return 0;
	}
	room->seats ++;
	pthread_cond_signal(&room->notFull);
	cout<<"One reader leaves the reading room!"<<endl;
	cout<<"Current Status:"<<endl;
	cout<<"seats: "<<room->seats<<endl;
	cout<<"readers in the room: "<<MAX_SEATS-room->seats<<endl;
	cout<<"readers waiting "<<room->waits<<endl<<endl;
	pthread_mutex_unlock(&room->lock);	
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
