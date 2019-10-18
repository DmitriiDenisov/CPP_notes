/*
Автор программы: Денисов Дмитрий, ПМИ 172
Среда разработки: Microsoft Visual Studio 2010 Professional
Дата последнего изменения: 26.04.2014
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <cstdlib>
using namespace std;

class Ant//объявление полей объекта класса
{
private:
	int x;
	int y;
	//объявление методов объекта класса
public:

	//конструктор
	Ant::Ant(int a, int b)
	{
		Ant::x = a;
		Ant::y = b;	
	}

	int get_x_Ant()
	{
		return x;
	}

	int get_y_Ant()
	{
		return y;
	}

	void up()
	{
		if (x - 1 >= 0)
			x--;
	}

	void down (int N)//передаем количество клеток, чтобы не переполнить сетку
	{
		if (x + 1 < N)
			x++;
	}

	void left()
	{
		if (y - 1 >= 0)
			y--;
	}

	void right (int N)
	{
		if (y + 1 < N)
			y++;
	}

	~Ant(){}

};

class Stone//объявление полей объекта класса
{
private:
	int x;
	int y;
	//объявление методов объекта класса
public:

	//конструктор
	Stone::Stone(int x, int y)
	{
		Stone::x = x;
		Stone::y = y;	
	}

	int get_x_Stone()
	{
		return x;
	}

	int get_y_Stone()
	{
		return y;
	}

	~Stone(){}

};

class Food//объявление полей объекта класса
{
private:
	int x;
	int y;
	//объявление методов объекта класса
public:

	//конструктор
	Food::Food(int x, int y)
	{
		Food::x = x;
		Food::y = y;	
	}
	int get_x_Food()
	{
		return x;
	}

	int get_y_Food()
	{
		return y;
	}

	~Food(){}

};

class Field{
private:
	int N;
	vector<Ant> vecA;
	vector<Stone> vecS;
	vector<Food> vecF;
public:

	Field::Field(int N)//конструктор
	{
		Field::N = N;
		int count = 0;
		while (count != N)//генерируем N различных координат еды
		{
			bool flag = true;
			int x = rand () % N;
			int y = rand () % N;
			for (int i = 0 ; i < vecF.size() ; i++)//проверяем только вектор еды, так как остальные не заполнены
				if ((vecF[i].get_x_Food() == x ) && (vecF[i].get_y_Food() == y))
					flag = false;
			if (flag)
			{
				Food object(x, y);
				vecF.push_back(object);
				count++;
			}
		}

		count = 0;
		while (count != N)//генерируем N различных координат камней
		{
			bool flag = true;
			int x = rand () % N;
			int y = rand () % N;
			for (int i = 0 ; i < vecS.size() ; i++)//проверяем, есть ли уже такой камень
				if ((vecS[i].get_x_Stone() == x ) && (vecS[i].get_y_Stone() == y))
					flag = false;
			for (int i = 0 ; i < vecF.size() ; i++)//проверяем, есть ли уже еда с такими координатами
				if ((vecF[i].get_x_Food() == x ) && (vecF[i].get_y_Food() == y))
					flag = false;
			if (flag)
			{
				Stone object(x, y);
				vecS.push_back(object);
				count++;
			}
		}

		count = 0;
		while (count != 1)//добавляем ОДНОГО муравья
		{
			bool flag = true;
			int x = rand () % N;
			int y = rand () % N;
			for (int i = 0 ; i < vecS.size() ; i++)//проверяем, есть ли уже такой камень
				if ((vecS[i].get_x_Stone() == x ) && (vecS[i].get_y_Stone() == y))
					flag = false;
			for (int i = 0 ; i < vecF.size() ; i++)//проверяем, есть ли уже еда с такими координатами
				if ((vecF[i].get_x_Food() == x ) && (vecF[i].get_y_Food() == y))
					flag = false;
			if (flag)
			{
				Ant object(x, y);
				vecA.push_back(object);
				count++;
			}
		}
	}

	Ant* get_ant(int i)
	{
		return &vecA[i];
	}

	void print ()//вывод
	{
		int x = 0;
		int y = 0;
		bool flag;
		for (int i = 0 ; i < N * N ; i++)
		{
			flag = false;
			for (int j = 0 ; j < vecS.size() ; j++)
			{
				if ((vecS[j].get_x_Stone() == x) && (vecS[j].get_y_Stone() == y))
				{
					cout << "S";
					flag = true;
				}
			}
			if (flag)
			{
				if (y < N - 1)
					y++;
				else
				{
					cout << endl;
					y = 0;
					x++;
				}
				continue;
			}

			for (int j = 0 ; j < vecF.size() ; j++)
			{
				if ((vecF[j].get_x_Food() == x) && (vecF[j].get_y_Food() == y))
				{
					cout << "F";
					flag = true;
				}
			}
			if (flag)
			{
				if (y < N - 1)
					y++;
				else
				{
					cout << endl;
					y = 0;
					x++;
				}
				continue;
			}

			for (int j = 0 ; j < vecA.size() ; j++)
			{
				if ((vecA[j].get_x_Ant() == x) && (vecA[j].get_y_Ant() == y))
				{
					cout << "A";
					flag = true;
				}
			}
			if (flag)
			{
				if (y < N - 1)
					y++;
				else
				{
					cout << endl;
					y = 0;
					x++;
				}
				continue;
			}

			cout << ".";
			if (y < N - 1)
				y++;
			else
			{
				cout << endl;
				y = 0;
				x++;
			}
		}
	}

	void set_ant(char a)
	{
		switch (a)
		{
		case 'w':if (get_ant(0)->get_x_ant())
					 cout << "";
			get_ant(0)->up();
			system("cls");
			print();
			break;
		case 's':get_ant(0)->down(N);
			system("cls");
			print();
			break;
		case 'a':get_ant(0)->left();
			system("cls");
			print();
			break;
		case 'd':get_ant(0)->right(N);
			system("cls");
			print();
			break;
		case 'q':
			cout << "Thanks for using!";
		}
	}

	~Field (){}

};

int main ()
{
	setlocale (LC_ALL, "Russian");
	srand(time(NULL));
	cout << "Введите N:";
	int N;
	cin >> N;
	Field x(N);
	x.print();
	char a = ' ';
	cout << "Теперь управляйте муравьем (up - w, down - s, left - a, right - d)";
	while (a != 'q')
	{
		a = _getch();
		x.set_ant(a);
	}

	return 0;
}