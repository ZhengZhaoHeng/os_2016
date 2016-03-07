#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MIN_SIZE = 32;
const int MEM_SIZE = 1024;

char memory[1024];
int tree_num = 0;

struct Node
{
	int size, left, right, addr;
	bool empty, full;
};

Node tree[70];

void buildTree(int node, int size, int addr)
{
	tree[node].size = size;
	tree[node].empty = true;
	tree[node].full = false;
	tree[node].addr = addr;
	size = size / 2;
	if (size < MIN_SIZE) 
	{
		tree[node].left = -1;
		tree[node].right = -1;
		return;
	}
	tree_num++;
	tree[node].left = tree_num;
	buildTree(tree[node].left, size, addr);
	tree_num++;
	tree[node].right = tree_num;
	buildTree(tree[node].right, size, addr + size);
}

void test(int node)
{
	if (node < 0) return;
	printf("node: %d, size: %d, addr: %d, empty: %d, full: %d\n", node, tree[node].size, tree[node].addr, tree[node].empty, tree[node].full);
	test(tree[node].left);
	test(tree[node].right);
}

int alloc(int node, int size)
{
	int node_size = tree[node].size;
	if (size > node_size || tree[node].full) return -1;
	int son_size = node_size / 2;
	if (size > son_size)
	{
		if (tree[node].empty)
		{
			tree[node].empty = false;
			tree[node].full = true;
			return tree[node].addr;
		}
		else return -1;
	}
	int return_addr = alloc(tree[node].left, size);
	if (return_addr >= 0) 
	{
		tree[node].empty = false;
		return return_addr;
	}
	return_addr = alloc(tree[node].right, size);
	if (return_addr >= 0)
	{
		tree[node].empty = false;
	}
	return return_addr;
}

void release(int node, int ptr)
{
	if (tree[node].empty) return;
	if (tree[node].full && tree[node].addr == ptr) 
	{
		tree[node].empty = true;
		tree[node].full = false;
		return;
	}
	if (tree[tree[node].right].addr > ptr) release(tree[node].left, ptr);
	else release(tree[node].right, ptr);
	tree[node].empty = tree[tree[node].left].empty & tree[tree[node].right].empty;
}

int malloc(int size)
{
	return alloc(0, size);
}

void free(int ptr)
{
	release(0, ptr);
}

int main()
{
	buildTree(0, MEM_SIZE, 0);
	printf("%d\n", malloc(512));
	printf("%d\n", malloc(128));
	printf("%d\n", malloc(256));
	printf("%d\n", malloc(128));
	free(640);
	free(512);
	printf("%d\n", malloc(200));
	test(0);
	return 0;
}