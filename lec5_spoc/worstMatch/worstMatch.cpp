#include <stdio.h>
#define MAX_SIZE  1000
#define POOL_SIZE  10000

struct ListNode
{
	int head;
	int size;
	ListNode *last, *next;		//pointers for rank 
	ListNode *prev, *back;		//pointers for address
	bool used;
	ListNode(): used(false), last(NULL), next(NULL), prev(NULL), back(NULL) {} 
}node_pool[POOL_SIZE];

ListNode* pool_head;

ListNode* free_head;
ListNode* address_head;

int malloc(int size)
{
	ListNode* current = free_head;
	int head = -1;
	if(current != NULL)
	{
		if(current->size >= size)
			if(current->size > size)
			{
				ListNode* newNode = pool_head;
				pool_head = pool_head->next;

				newNode->head = current->head + size;
				newNode->size = current->size - size;
				newNode->used = false;
				newNode->last = NULL;
				newNode->next = NULL;
				
				head = current->head;
				current->size = size;
				current->used = true;

				// revise address pointer
				if(current->back != NULL)
					current->back->prev = newNode;
				newNode->back = current->back;
				newNode->prev = current;
				current->back = newNode;

				// revise rank pointer
				free_head = current->next;
				// find new rank for newNode
				ListNode* last = NULL;
				current = current->next;
				while(current != NULL)
				{
					if(current->size <= newNode->size)
					{
						if(last != NULL)
							last->next = newNode;
						else
							free_head = newNode;
						newNode->last = last;
						newNode->next = current;
						current->last = newNode;
						break;
					}
					else
					{
						last = current;
						current = current->next;
					}
				}
				if(current == NULL)
				{
					if(last != NULL)
						last->next = newNode;
					else
						free_head = newNode;
					newNode->last = last;
				}
			}
			else // size=
			{
				free_head = current->next;
				current->used = true;
				head = current->head;
			}
	}
	return head;
}

bool free(int head)
{
	ListNode* current = address_head;

	while(current != NULL)
	{
		if(current->head == head)
		{
			if(current->used == false)
				return false;
			current->used = false;
			// merge prev segment
			if(current->prev && current->prev->used == false)
			{
				ListNode* prev = current->prev;
				//revise free list of prev
				if(prev->last != NULL)
					prev->last->next = prev->next;
				else
					free_head = prev->next;
				if(prev->next != NULL)
					prev->next->last = prev->last;

				current->size = current->size + prev->size;
				current->head = prev->head;
				if(prev->prev != NULL)
					prev->prev->back = current;
				else
					address_head = current;
				current->prev = prev->prev;
				// free node to pool
				prev->used = false;
				prev->next = pool_head;
				pool_head = prev;
			}
			// merge back segment
			if(current->back && current->back->used == false)
			{
				ListNode* back = current->back;
				//revise free list of back
				if(back->last != NULL)
					back->last->next = back->next;
				else
					free_head = back->next;
				if(back->next != NULL)
					back->next->last = back->last;

				current->size = current->size + back->size;
				if(back->back != NULL)
					back->back->prev = current;
				current->back = back->back;
				// free node to pool
				back->used = false;
				back->next = pool_head;
				pool_head = back;
			}
			// insert into free list
			ListNode* newNode = current;
			current = free_head;
			ListNode* last = NULL;
			while(current != NULL)
			{
				if(current->size <= newNode->size)
				{
					if(last != NULL)
						last->next = newNode;
					else
						free_head = newNode;
					newNode->next = current;
					break;
				}
				else
				{
					last = current;
					current = current->next;	
				}
			}
			if(current == NULL)
			{
				if(last != NULL)
					last->next = newNode;
				else
					free_head = newNode;
			}
			break;
		}
		else
		{
			current = current->back;
		}
	}
	return true;
}


void init()
{
	for(int i=0; i <POOL_SIZE-1; i++)
	{
		node_pool[i].next = &node_pool[i+1];
	}
	node_pool[POOL_SIZE-1].next = NULL;

	address_head = node_pool;
	pool_head = &node_pool[1];

	address_head->head = 0;
	address_head->size = MAX_SIZE;
	address_head->next = NULL;
	free_head = address_head;
}

int main()
{
	init();
	printf("malloc: %d\n", malloc(100));	//return head of the memory, if return -1 means failure 
	printf("malloc: %d\n", malloc(200));
	printf("malloc: %d\n", malloc(300));
	printf("malloc: %d\n", malloc(400));
	printf("malloc: %d\n", malloc(300));
	printf("free: %d\n", free(100));		//return 1 means success, 0 means failure
	printf("free: %d\n", free(600));
	printf("malloc: %d\n", malloc(50));
	printf("malloc: %d\n", malloc(100));
	printf("malloc: %d\n", malloc(250));
	printf("malloc: %d\n", malloc(100));
	return 0;
}

