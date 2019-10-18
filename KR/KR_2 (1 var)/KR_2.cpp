// Программа считывает информацию из внешнего файла, сохраняет, обрабатывает и выводит 
// считанную информацию согласно требованиям задачи.
//	Среда разработки: Microsoft Visual C++ 2012 Express                                                |
// Версия программы: 1.2  |  Автор: Денисов Д.М.,ПМИ,172										      |
// Дата последнего изменения: 20.03.2014
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

const int len = 20;//константа длины считываемой строки
const int numel = 200;//промежуточного массива, куда помещается считанная строка
const int ascii = 96;//константа для 3-ей функции, для вычисления веса буквы
struct student {
	int num1, num2;
	char * slovo;
};

void readfile(ifstream& fin, vector<student>& vec, char * pch)//функция считывания информации
{
	student object;//объект структуры, сначала заносим данные в него, после кидаем его в конец вектора
	ifstream data;
	if (!fin)
		cout<<"Файл не найден, какая жалость..."<<endl;
	else
	{
		int number = 0;
		while (fin.getline (pch, len, '\n'))
		{
			if (number % 2 == 0)//пользуемся чередованием строк
			{//если два числа
				int i = 0;
				while((i < numel) && (pch[i] != ' '))//доходим до пробела
					i++;
				string first="               ";
				for (int k = 0 ; k < i ; k++)//записываем в переменную типа стринг
					first[k] = pch[k];
				object.num1 = atoi(first.c_str());//переводим из стринга в инт
				int prev = i;
				i++;
				while ((i < numel) && (pch[i] != '\0'))//считываем второе число
					i++;
				string second = "           ";
				for (int k = prev ; k < i - 1 ; k++)//записываем в стринг
					second[k - prev] = pch[k + 1];
				object.num2 = atoi(second.c_str());//переводим стринг в инт
			}
			else//если слово
			{
				int i = 0;
				while ((i < numel) && (pch[i] != '\0'))//вычисляем длину записанного слова
					i++;
				object.slovo = new char[i];//выделяем дин.память для такого количества ячеек
				for (int j = 0 ; j < i ; j++)
					object.slovo[j] = pch[j];
				object.slovo[i] = '\0';//в конец записываем терминальный ноль
				vec.push_back(object);//запихиваем в конец
			}
			number++;
		}
		cout<<"Входной файл прочитан и данные размещены в векторе"<<endl<<"Слова вектора:";
		for (unsigned int i = 0 ; i < vec.size() ; i++)
			cout<<vec[i].slovo<<", ";
		cout<<endl<<"Число элементов вектора равняется:"<<vec.size()<<endl;
		cout<<endl<<"Полученные из внешнего файла данные помещены в вектор:"<<endl;
	}
}

void calcpr(vector<student>& vec)//функция вывода общей информации
{
	
	for (unsigned int i = 0 ; i < vec.size() ; i++)
	{
		int summa = 0;
		int summa_w = 0;
		int j = 0;
		double result;
		while (vec[i].slovo[j] != '\0')
		{
			summa = summa + (vec[i].slovo[j] - ascii) * vec[i].slovo[j];
			summa_w = summa_w + vec[i].slovo[j] - ascii;
			result = (double)summa / (double)summa_w;
			j++;
		}
		cout<<"#"<<i + 1<<":"<<"  num1="<<vec[i].num1<<"   num2="<<vec[i].num2<<"   slovo--->"<<vec[i].slovo<<"   [ w.a. = "<<fixed<<setprecision(2)<<result<<"]"<<endl;
	}
}

int count(vector<student>& vec, char* pstr)//функция вхождений заданной фразы в слова
{
	cout<<endl;
	int all = 0;//общее количество вхождений
	for (unsigned int i = 0 ; i < vec.size() ; i++)
		if ((vec[i].num1 + vec[i].num2) % 2 == 1)
		{
			int num = 0;
			int j = 0;
			while (vec[i].slovo[j+1] != '\0')
			{
				if ((vec[i].slovo[j] == pstr[0]) && (vec[i].slovo[j + 1] == pstr[1]))
					num++;
				j++;
			}
			all = all + num;
			cout<<"слово: "<<vec[i].slovo<<"   подстрока: "<<pstr<<"   число вхождений: "<<num<<endl;
		}
		return all;
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
	srand(time(NULL));
	setlocale(LC_ALL,"Russian");
	vector<student> vect;
	char * search = "at"; // строка для поиска (задание 3).
	const char * data = "kontr.txt";// полное имя файла с данными для обработки.
	char input_str[numel]; // сюда последовательно помещаются считываемые строки
	ifstream finp(data); // открытие входного потокового объекта. 
	readfile(finp, vect, input_str);
	calcpr(vect);
	int all = count(vect, search);
	cout<<"общее число вхождений строки "<<search<<" в векторе равняется "<<all<<endl;
	FunnyFunction();
	vect.erase(vect.begin(), vect.end());
	return 0;
}