#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <utility>

struct item
{
	bool accessed, modified;
	int page_num;
};

const int PHYSICAL_SIZE = 10;
const int OP_NUM = 20;
const int VIRTUAL_SIZE = 20;

using namespace std;

int main()
{
	srand((int)time(NULL));
	item* clock = new item[PHYSICAL_SIZE];
	memset(clock, 0, PHYSICAL_SIZE * sizeof(item));
	int head = 0;
	for (int i = 0; i < PHYSICAL_SIZE; i++)
	{
		clock[i].page_num = -1;
	}

	for (int i = 0; i < OP_NUM; i++)
	{
		int vp = rand() % VIRTUAL_SIZE;
		int op = rand() % 2;       // 0 - read only, 1 - write
		printf("accessing virtual page num: %d operation: %d \n", vp, op);
		bool hit = false;

		for (int j = 0; j < PHYSICAL_SIZE; j++)
		{
			if (clock[j].page_num == vp)
			{
				clock[j].accessed = true;
				clock[j].modified |= op;
				hit = true;
				printf("virtual page %d hit!\n", vp);
			}
		}

		if (!hit)
		{
			printf("accessing virtual page: %d, page fault! \n");
			while (clock[head].accessed | clock[head].modified)
			{
				clock[head].modified &= clock[head].accessed;
				clock[head].accessed &= 0;
				if (!(clock[head].accessed | clock[head].modified)) break;
				head++;
				if (head >= PHYSICAL_SIZE) head = head % PHYSICAL_SIZE;
			}

			if (!(clock[head].accessed | clock[head].modified))
			{
				clock[head].accessed = true;
				clock[head].modified |= op;
				clock[head].page_num = vp;
				head++;
				if (head >= PHYSICAL_SIZE) head = head % PHYSICAL_SIZE;
			}
		}

	}
	delete[] clock;
	return 0;
}