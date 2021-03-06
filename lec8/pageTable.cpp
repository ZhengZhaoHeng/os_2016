#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>

using namespace std;

int memory[128][32];
int disk[128][32];

void lookup_disk(short vaddress)
{
	cout<<"Virtual Address 0x"<< hex << vaddress <<':'<<endl;
	short pde_i = (vaddress >> 10) & 0x7;
	short pde_c = memory[0x6c][pde_i];

	short valid0 = pde_c >> 7;
	short pfn0 = pde_c & 0x7f;
	cout<<"--> pde index : 0x"<< hex <<pde_i<<" pde contents:(0x"<<pde_c<<", valid "<< valid0 <<", pfn 0x"<< hex <<pfn0<<" )"<<endl;
	
	cout<<"page 6c: ";
	for(int i=0; i<16; i++)
		cout<<memory[0x6c][i]<<' ';
	cout<<endl<<"         ";
	for(int i=16; i<32; i++)
		cout<<memory[0x6c][i]<<' ';
	cout<<endl;
	
	if(valid0 == 0)
		cout<<"    --> Fault (page directory entry not valid)"<<endl;
	else
	{
		cout<<"page "<<hex<<pfn0<<": ";
		for(int i=0; i<16; i++)
			cout<<memory[pfn0][i]<<' ';
		cout<<endl<<"         ";
		for(int i=16; i<32; i++)
			cout<<memory[pfn0][i]<<' ';
		cout<<endl;

		short pte_i = (vaddress >> 5) & 0x1f;
		short pte_c = memory[pfn0][pte_i];
		short valid1 = pte_c >> 7;
		short pfn1 = pte_c & 0x7f;
		cout<<"    --> pte index : 0x"<< hex<<pte_i <<" pte contents:(0x"<<pte_c<<", valid "<<valid1 <<", pfn 0x"<< hex <<pfn1<<" )"<<endl;

		if(valid1 == 0)
		{
			if(pfn1 == 0x7f)
			{
				cout<<"        --> neither in memory, nor in disk"<<endl;
			}
			else
			{
				cout<<"page "<<hex<<pfn1<<": ";
				for(int i=0; i<16; i++)
					cout<<disk[pfn1][i]<<' ';
				cout<<endl<<"         ";
				for(int i=16; i<32; i++)
					cout<<disk[pfn1][i]<<' ';
				cout<<endl;

				short diskaddress = (pfn1 << 5) + (vaddress & 0x001f);
				short value = disk[pfn1][vaddress & 0x001f];
				cout<<"        --> To Disk Sector Address 0x"<< hex << diskaddress <<" --> Value: "<< hex <<value<<endl;
			}
		}
		else
		{
			cout<<"page "<<hex<<pfn1<<": ";
			for(int i=0; i<16; i++)
				cout<<memory[pfn1][i]<<' ';
			cout<<endl<<"         ";
			for(int i=16; i<32; i++)
				cout<<memory[pfn1][i]<<' ';
			cout<<endl;

			short paddress = (pfn1 << 5) + (vaddress & 0x001f);
			short value = memory[pfn1][vaddress & 0x001f];
			cout<<"        --> To Physical Address 0x"<< hex <<paddress<<" --> Value: "<<hex<<value<<endl;
		}
	}
}

void init()
{
	ifstream fin("memory.txt");
	char s[10];
	char c;
	int pn;
	int num = 128;
	for(int i=0; i<num; i++)
	{
		fin >> s;
		fin >> hex >> pn;
		fin >> c;
		for(int j=0; j<32; j++)
			fin >> hex >> memory[i][j];
	}
	fin.close();

	fin.open("disk.txt");
	for(int i=0; i<num; i++)
	{
		fin >> s;
		fin >> hex >> pn;
		fin >> c;
		for(int j=0; j<32; j++)
			fin >> hex >> disk[i][j];
	}
	fin.close();
}
int main()
{
	init();
	lookup_disk(0x0330);
	return 0;
}