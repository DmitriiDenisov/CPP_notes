// Игра пятнашки. Цель игры - составить все числа по порядку.
// Среда разработки: Microsoft Visual C++ 2013 Express			//
// Версия программы: 1.1  |  Автор: Денисов Д.М., ПМИ, 172			//
// Дата последнего изменения: 27.01.2013 	

#include "stdafx.h"
#include <iostream>
#include <conio.h>//для _getch()
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

bool proverka(int **mass, int N)//проверка выигрыша
{
	bool flag = true;
	int num = 1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if ((mass[i][j]!= num) && ((i!= N - 1) || (j!= N - 1)))
				flag = false;
			num++;
		}
		return flag;
}

void vivod (int **mass, int N, int steps)//функция вывода
{
	system("cls");//стираем предыдущую матрицу
	for (int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cout<<setw(4);
			if (mass[i][j]!= 0)
				cout<<mass[i][j];
			else
				cout<<" ";
		}
		cout<<endl;
	}
	if (proverka(mass,N) == true)//проверка, выиграл ли пользователь
	{
		cout<<"Congratulation!You are winner!!!"<<endl;
		cout<<"Your time:"<<clock()/1000.0<<endl;
		cout<<"Number of steps:"<<steps<<endl;
		exit(1);
	}
}

int** generation(int N)//функция генерирует создаёт нужную нам матрицу
{
	int num = 0;
	int **ykaz = new int *[N];
	for(int i = 0; i < N; i++)
		ykaz[i] = new int [N];
	for (int i = 0; i < N; i++)//сначала заполним матрицу числами по порядку
	{
		for(int j = 0; j < N; j++)
		{
			num++;
			ykaz[i][j] = num;
		}
	}

	for (int i = 0; i < N; i++)//потом случайным образом будем менять местами числа
	{
		for(int j = 0; j < N; j++)
		{
			int x = rand() % N;
			int y = rand() % N;
			if (((x!= N - 1) || (y!= N - 1)) && ((i!= N - 1) || (j!= N - 1)))//за исключением последней клетки-там будет начальное положение курсора
			{
				int k = ykaz[i][j];
				ykaz[i][j] = ykaz[x][y];
				ykaz[x][y] = k;
			}
		}
	}
	ykaz[N-1][N-1] = 0;//начальное положение зануляем

	cout<<'\n';
	vivod(ykaz, N, 0);
	return ykaz;

}

int main(int argc, const char * argv[])
{
	int N;//переменная рамерности матрицы
	int count = 0;//счетчик количества ходов
	char input = 'x';//переменная действия
	srand(time(NULL));
	
	do
	{
		cout<<"Enter N from segment [1;+oo):";
		cin>>N;
	}while (N < 1);

	cout<<"To control position use: w-up, s-down, a-left, d-right."<<endl;
	cout<<"Warning! This message will disapear!";
	system("pause");
	int** mass = generation(N);
	int x_koor = N - 1;//координаты "пустого" места, курсора
	int y_koor = N - 1;

	while (input!='q')
	{
		count++;
		cout<<"Enter action:";
		char input = _getch();
		switch (input)
		{
		case 'q':
			cout<<"Thanks for using. Having nice day!:)"<<endl;
			exit(1);
		case 'w': if (x_koor - 1 >= 0)
				  {
					  mass[x_koor][y_koor] = mass[x_koor - 1][y_koor];
					  mass[x_koor - 1][y_koor] = 0;
					  x_koor--;
				  }
				  vivod(mass, N, count);
				  break;

		case 'a':   if (y_koor - 1 >= 0)
					{
						mass[x_koor][y_koor] = mass[x_koor][y_koor - 1];
						mass[x_koor][y_koor - 1] = 0;
						y_koor--;
					}
					vivod(mass, N, count);
					break;


		case 's':   if (x_koor + 1 <= N - 1)
					{
						mass[x_koor][y_koor] = mass[x_koor + 1][y_koor];
						mass[x_koor + 1][y_koor] = 0;
						x_koor++;
					}
					vivod(mass, N, count);
					break;

		case 'd':   if (y_koor + 1 <= N - 1)
					{
						mass[x_koor][y_koor] = mass[x_koor][y_koor + 1];
						mass[x_koor][y_koor + 1] = 0;
						y_koor++;
					}
					vivod(mass, N, count);
					break;
		default: vivod(mass, N, count);
			break;
		}
	}
	delete mass;
	mass = NULL; 

	return 0;
}