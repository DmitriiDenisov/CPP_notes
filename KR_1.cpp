//Денисов Дмитрий,ПМИ,172
//

#include "stdafx.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

int* generateRandomMatrix(int* rank)
{
	int* ykaz = new int[*rank**rank];
	bool flag;

	for (int i = 0;i <*rank**rank;i++)
	{
		do
		{
			flag = 0;
			ykaz[i] = rand() % (*rank**rank) + 1;
			for (int j = i - 1;j >= 0 ; j--)
			{
				if (ykaz[i] == ykaz[j])
					flag = 1;
			}
		}while (flag);
	}
	return ykaz;
}

void printMatrix(int* matrix, int* rank)
{
	int* per;
	cout<<endl;
for (int i = 0; i <= *rank**rank ; i++)
{
	per = generateRandomMatrix(rank);
	cout<<setprecision(4)<<*per<<'\t';
	if ((i+1)%7 == 0)
	{
		cout<<endl;
	}
}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N;
	srand(time(NULL));
	
	do{
		cout<<"Enter num from [7;17]:";
		cin>>N;
	}while((N < 7)||(N > 17)||(N % 2 == 1));

	int* c = generateRandomMatrix(&N);
	printMatrix(generateRandomMatrix(&N),&N);
	
	return 0;
}

