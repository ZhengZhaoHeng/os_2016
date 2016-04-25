#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

#define PROC_SUM  1000
#define IDLE 0
#define WAIT 1
#define ACTIVE 2

int current[PROC_SUM];
int flag[PROC_SUM];
int turn;
int runCritical = -1;

bool runProcess(int pid)
{
	switch (current[pid])
	{
	case 0:
		flag[pid] = ACTIVE;
		current[pid] = 1;
		break;
	case 1:
		current[pid] = 6;
		for(int i = 0; i < PROC_SUM; i++)
			if(i != pid && flag[i] == ACTIVE)
			{
				current[pid] = 2;
				break;
			}
		break;
	case 2:
		if(turn != pid)
			current[pid] = 3;
		else
			current[pid] = 1;
		break;
	case 3:
		flag[pid] = WAIT;
		current[pid] = 4;
		break;
	case 4:
		if(turn != pid)
			current[pid] = 4;
		else
			current[pid] = 5;
		break;
	case 5:
		flag[pid] = ACTIVE;
		current[pid] = 1;
		break;
	case 6:
		if(runCritical != -1)
			return false;
		runCritical = pid;
		cout<<"Process "<<pid<<" enter the critical section!"<<endl;
		current[pid] = 7;
		break;
	case 7:
		if(runCritical != pid)
			return false;
		cout<<"Process "<<pid<<" run in the critical section!"<<endl;
		current[pid] = 8;
		break;
	case 8:
		if(runCritical != pid)
			return false;
		runCritical = -1;
		cout<<"Process "<<pid<<" exit the critical section!"<<endl;
		current[pid] = 9;
		break;
	case 9:
		for(int i = 0; i < PROC_SUM; i++)
			if(i != pid && flag[i] == WAIT)
			{
				turn = i;
				break;
			}
		current[pid] = 10;
		break;
	case 10:
		flag[pid] = IDLE;
		current[pid] = 0;
		break;
	default:
		break;
	}

	return true;
}

int main()
{
	for(int i = 0; i < PROC_SUM; i++)
	{
		flag[i] = IDLE;
		current[i] = 0;
	}

	srand(time(0));
	for(int i = 0; i < 100000; i++)
	{
		int pid = rand()%PROC_SUM;
		//cout<<pid<<' '<<current[pid]<<endl;
		if(!runProcess(pid))
		{
			cout<<"Wrong!"<<endl;
			return 0;
		}
	}
	cout<<"Correct!"<<endl;
	return 0;
}