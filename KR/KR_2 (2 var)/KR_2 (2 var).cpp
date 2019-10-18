// Программа считывает информацию из внешнего файла, сохраняет, обрабатывает и выводит 
// считанную информацию о вагонах согласно требованиям задачи.
//	Среда разработки: Microsoft Visual C++ 2012 Express                                                |
// Версия программы: 1.2  |  Автор: Денисов Д.М.,ПМИ,172										      |
// Дата последнего изменения: 22.03.2014
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


const int len = 200;//константа длины считываемой строки
struct Train{
	char name[200];
	int size;
	int * wagwts;
	int * waglen;
	int weight;
	int length;
};

void readfile(ifstream& fin, vector<Train>& vec)//функция считывания информации
{
	char prom[200];
	Train object;//объект структуры, сначала заносим данные в него, после кидаем его в конец вектора
	ifstream data;
	if (!fin)
		cout<<"Файл не найден, какая жалость..."<<endl;
	else
	{
		int number = 0;
		while (fin.getline (prom, 200, '\n'))
		{
			int i = 0;
			while (prom[i] != '-')
				i++;
			int j = 0;
			for (j = 0 ; j < i - 1 ; j++)
				object.name[j] = prom[j];
			object.name[j] = '\0';
			i = i + 2;//следующее число
			j = i;
			while (prom[i] != ':')
				i++;
			string number="   ";
			for (int k = j ; k < i - 1 ; k++)//записываем в переменную типа стринг
				number[k - j] = prom[k];
			object.size = atoi(number.c_str());//переводим из стринга в инт
			object.wagwts = new int[object.size];
			object.waglen = new int[object.size];
			i = i + 2;//следующее число
			int count = 0;
			int nacalo = i;
			for (int k = 0 ; k < 2 * object.size; k++)
			{
				j = i;
				while ((prom[i] != '\0') && (prom[i] != ' '))
					i++;
				if (k % 2 == 0)
				{
					string number1 = "    ";
					for (int k = j ; k < i ; k++)
						number1[k - j] = prom[j];//записываем в переменную типа стринг
					object.waglen[count] = atoi(number1.c_str());//переводим из стринга в инт
					count++;
				}
				i++;
			}

			i = nacalo;
			count = 0;
			for (int k = 0 ; k < 2 * object.size ; k++)
			{
				j = i;
				while ((prom[i] != '\0') && (prom[i] != ' '))
					i++;
				if (k % 2 == 1)
				{
					string number2="    ";
					for (int k=j;k<i;k++)//записываем в переменную типа стринг			
						number2[k-j] = prom[k];
					object.wagwts[count] = atoi(number2.c_str());//переводим из стринга в инт
					count++;
				}
				i++;
			}
			object.weight = 0;
			object.length = 0;
			for (int p = 0 ; p < object.size ; p++)
			{
				object.weight = object.weight + object.wagwts[p];
				object.length = object.length + object.waglen[p];
			}
			vec.push_back(object);
		}
	}
	cout<<"Входной файл прочитан и данные размещены в векторе"<<endl<<"Имена вагонов:";
	for (unsigned int i = 0 ; i < vec.size() ; i++)
		cout<<vec[i].name<<", ";
	cout<<endl<<"Число элементов вектора равняется:"<<vec.size()<<endl;
}

void masscentre(vector<Train>& vec)
{
	int num, x;
	cout<<endl<<"Информация о парке поездов:"<<endl<<"Название поезда, (#, длина, вес) вагонов, длина и вес поезда )"<<endl;
	for (unsigned int i = 0 ; i < vec.size() ; i++)
	{
		cout<<"#"<<i+1<<vec[i].name<<"    ";
		for (int j=0;j<vec[i].size;j++)
		{
			cout<<"("<<j+1<<", "<<vec[i].waglen[j]<<", "<<vec[i].wagwts[j]<<")   ";
		}
		cout<<endl;
	}
	cout<<"Введите номер вагона:";
	cin>>num;
	if (num > vec.size())
		cout<<"Error!";
	else
	{
		x = 1;
		int min = vec[num].wagwts[0] + vec[num].wagwts[2];
		for (int i = 2 ; i < vec[i].size - 1 ; i++)
			if (vec[num].wagwts[i - 1] + vec[num].wagwts[i+1] < min)
			{
				min = vec[num].wagwts[i - 1] + vec[num].wagwts[i + 1];
				x = i;
			}
	}
	cout<<endl<<"Пользователь ввел номер "<<num + 1<<endl<<"#"<<num + 1<<"Поезд "<<vec[num].name;
	cout<<"Центр тяжести: Вагон #"<<x<<"Вес слева: "<<vec[num].wagwts[x-1]<<" Вес cправа: "<<vec[num].wagwts[x+1];
	cout<<endl<<"Разница: "<<abs(vec[num].wagwts[x-1]-vec[num].wagwts[x+1]);
}

int sort(vector<Train>& vec, int index)
{
	return 1;
}

void FunnyFunction()//функция создания матрицы
{
	int n, m;
	cout<<"Введите n(строки):";
	cin>>n;
	cout<<"Введите m(столбцы):";
	cin>>m;
	int **matrix = new int*[m];
	for (int i = 0 ; i < n ; i++)
		matrix[i] = new int[m];
	for (int i = 0 ; i < n ; i++)
	{
		for (int j = 0 ; j < m ; j++)
		{
			matrix[i][j] = rand() % 99 + 1;
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl;
	for (int i = 0 ; i < n ; i++)
	{
		for (int j = 0 ; j < m ; j++)
		{
			if ((i + j) % 2 == 0)
				matrix[i][j] = 0;
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}

	for (int i = 0 ; i < n ; i++)
		delete matrix[i];
	delete matrix;
}

int main(int argc, const char * argv[])
{
	setlocale(LC_ALL,"Russian");
	vector<Train> vcTr;
	const char * data = "trains.txt";// полное имя файла с данными для обработки.
	ifstream finp(data); // открытие входного потокового объекта. 
	readfile(finp, vcTr);
	masscentre(vcTr);

	vcTr.erase(vcTr.begin(), vcTr.end());
	return 0;
}