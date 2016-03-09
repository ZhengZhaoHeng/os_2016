#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>

using namespace std;

int data[128][32];

void address_convert(short vaddress)
{
	cout<<"Virtual Address "<< hex << vaddress <<':'<<endl;
	short pde_i = vaddress >> 10;
	short pde_c = data[17][pde_i];
	short valid0 = pde_c >> 7;
	short pfn0 = pde_c & 0x7f;
	cout<<"--> pde index : "<< hex <<pde_i<<" pde contents:( valid "<< valid0 <<", pfn "<< hex <<pfn0<<" )"<<endl;
	if(valid0 == 0)
		cout<<"--> Fault (page directory entry not valid)"<<endl;
	else
	{
		short pte_i = (vaddress & 0x03ff) >> 5;
		short pte_c = data[pfn0][pte_i];
		short valid1 = pte_c >> 7;
		short pfn1 = pte_c & 0x7f;
		cout<<"--> pte index : "<< hex<<pte_i <<" pte contents: ( valid "<<valid1 <<", pfn "<< hex <<pfn1<<" )"<<endl;

		if(valid1 == 0)
			cout<<"--> Fault (page table entry not valid)"<<endl;
		else
		{
			short paddress = pfn1 << 5 + (vaddress & 0x001f);
			short value = data[pfn1][vaddress & 0x001f];
			cout<<"--> Translates to Physical Address "<< hex <<paddress<<" --> Value: "<<hex<<value<<endl;
		}
	}


	//cout<<valid0<<' '<<pfn0<<' '<<pte_i<<' '<<pte_c<<' '<<valid1<<' '<<pfn1<<endl;
}

void init()
{
	ifstream fin("data.txt");
	char s[10];
	char c;
	int pn;
	int num = 128;
	for(int i=0; i<num; i++)
	{
		fin >> s;
		fin >> hex >> pn;
		fin >> c;
		//cout<< s << pn << c;
		for(int j=0; j<32; j++)
			fin >> hex >> data[i][j];
	}
}
int main()
{
	init();
	//cout<<data[0][0]<<endl;
	address_convert(0x6b22);
	int stop =0;
	return 0;
}