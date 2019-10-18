// Программа считывает из файла данные об игроках. Выводит информацию о них, а также создает список, основанные на векторе, содержащем информацию об игроках.
// Aвтор: Денисов Дмитрий, 172
// Cреда разработки: Microsoft Visual Studio 2012
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int N = 100;

struct Footballer_list{//структура для задачи 2
	Footballer_list* next;//указатель на следующий элемент списка
	char* name;
	char* position;
	int* goals;
	int num_of_matces;//количество матчей, требуется для корректного вывода
	int total_goals;
};

struct Footballer{//структура задачи 1
	char* name;
	char* position;
	int* goals;
	int num_of_matces;//количество матчей, требуется для корректного вывода
	int total_goals;
};

Footballer_list new_node(Footballer object)//функция преобразования из Footballer из Footballer_list
{
	Footballer_list a;
	a.name = object.name;
	a.num_of_matces = object.num_of_matces;
	a.position = object.position;
	a.total_goals = object.total_goals;
	a.goals = new int[object.num_of_matces];
	for (int i = 0 ; i < object.num_of_matces ; i++)
		a.goals[i] = object.goals[i];
	return a;
}

int recursion_list(vector<Footballer> vec, unsigned int i, Footballer_list* ykaz_prev)//функция рекурсивного создания списка
{
	if (i < vec.size())
	{
		Footballer_list ob = new_node(vec[i]);
		ykaz_prev = &ob;
		recursion_list(vec, i++, ob.next);
	}
	return 1;
}

void readcheck(ifstream& ffstr, vector<Footballer>& vec)//функция чтения
{
	char mass[N];
	if(!ffstr)
	{
		cout << "Ошибка: не удалось открыть файл...\n";
		exit(EXIT_FAILURE);		 
	}

	while(!ffstr.eof( ))		// пока не достигнут конец файла...
	{
		Footballer object;//объект типа стурктуры
		ffstr.getline(mass, N);//считываем построчно из файла
		int i = 0;
		while (mass[i] != ':')//считываем имя
			i++;
		object.name = new char[i];
		int j = 0;
		for (j = 0 ; j < i ; j++)//записываем в объект имя
			object.name[j] = mass[j];
		object.name[j - 1] = '\0';

		i = i + 2;//cчитываем позицию
		int begin = i;
		while (mass[i] != ':')
			i++;
		object.position = new char[i - begin];
		for (j = begin ; j < i; j++)//записываем в объект позицию
			object.position[j - begin] = mass[j];
		object.position[j - begin] = '\0';

		i = i + 2;//считываем голы игрока
		int num_of_matces = 0;//количество матчей
		vector<int> prom_goals;//промежуточный вектор, содержащий голы
		while (mass[i - 1] != '\0')
		{
			num_of_matces++;
			int k = mass[i] - '0';
			prom_goals.push_back(k);
			i = i + 3;//через 3 повторяются числа - голы (каждое число <10, поэтому можем идти через 3)
		}
		object.num_of_matces = num_of_matces;
		object.goals = new int[prom_goals.size()];//записываем голы в объект структуры
		for (unsigned int s = 0 ; s < prom_goals.size() ; s++)
			object.goals[s] = prom_goals[s];

		int sum = 0;
		for (unsigned int s = 0 ; s < prom_goals.size() ; s++)// считаем сумму всех голов
			sum = sum + prom_goals[s];
		object.total_goals = sum;

		vec.push_back(object);//кидаем объект в вектор структуры
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL,"RUS");
	vector<Footballer> vec;//вектор структуры
	string name_of_file;
	cout << "Enter full name of file:";//пользователь вводит путь
	getline (cin,name_of_file);
	ifstream ffstr(name_of_file);
		readcheck(ffstr, vec);//считываем файл
	ffstr.close();

	for (unsigned int i = 0 ; i < vec.size() ; i++)//вывод
	{
		cout << i + 1 << ">>";
		int j = 0;
		while (vec[i].name[j] != '\0')
		{
			cout << vec[i].name[j];
			j++;
		}
		cout << " : ";
		j = 0;
		while (vec[i].position[j] != '\0')
		{
			cout << vec[i].position[j];
			j++;
		}
		cout << " : ";

		for (int s = 0 ; s < vec[i].num_of_matces ; s++)
			cout << vec[i].goals[s] << ", ";
		cout << "            total goals:" << vec[i].total_goals; 

		cout << endl;
	}

	//ЗАДАЧА 2.
	Footballer_list* root = nullptr;//создаем корень списка
	recursion_list(vec, 0, root);
	return 0;
}

