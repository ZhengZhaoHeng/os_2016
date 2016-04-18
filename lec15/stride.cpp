#include <iostream>
#include <vector>

using namespace std;

const int BIG_STRIDE = 2147483647;

struct Proc
{
	int pid;
	int time_remain;
	int priority;
	int stride;
	int pass;
	Proc(int _pid, int _time, int _priority): pid(_pid), time_remain(_time), priority(_priority), stride(0), pass(BIG_STRIDE/priority){};
};

class Scheduler
{
private:
	vector<Proc*> proc_list;
	int time_slice;
public:
	Scheduler(int time): time_slice(time) {};
	~Scheduler() {};
	void add_proc(Proc *p);
	bool schedule();
};

void Scheduler::add_proc(Proc *p)
{
	proc_list.push_back(p);
}

bool Scheduler::schedule()
{
	if(proc_list.empty())
	{
		cout<<"All the process have exited"<<endl;
		return false;
	}

	int min_stride = BIG_STRIDE;
	Proc *proc = proc_list[0];
	vector<Proc*>::iterator p = proc_list.begin();
	for(vector<Proc*>::iterator it = proc_list.begin(); it != proc_list.end(); ++it)
		if((*it)->stride < min_stride)
		{
			proc = *it;
			p = it;
			min_stride = proc->stride;
		}
	if(proc->time_remain <= time_slice)
	{
		cout<<"Process "<<proc->pid<<" run "<<proc->time_remain<<" and exited"<<endl;
		proc_list.erase(p);
	}
	else
	{
		cout<<"Process "<<proc->pid<<" run "<<time_slice<<endl;
		proc->time_remain -= time_slice;
		proc->stride += proc->pass;
	}
	return true;
}

int main()
{
	int time_slice = 10;
	Scheduler scheduler(time_slice);
	scheduler.add_proc(new Proc(0, 100, 100));
	scheduler.add_proc(new Proc(1, 100, 200));
	scheduler.add_proc(new Proc(2, 100, 300));
	scheduler.add_proc(new Proc(3, 100, 400));

	int ticks = 0;
	while(scheduler.schedule())
		ticks += time_slice;

	return 0;
}