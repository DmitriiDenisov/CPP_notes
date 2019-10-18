// Программа имитирует работу человека с автоматом по размене купюр
// Автор: Денисов Дмитрий, ПМИ 172
// Среда разработки: Microsoft Visual Studio 2010

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

const int len = 50;//длина считываемой строки
const int summa = 6166;//общая сумма всех возможных купюр по одной: 1 + 5 + 10 + 50 + ...
int mass[7] = {5000, 1000, 100, 50, 10, 5, 1};

struct currency{
	int nominal;
	char name[len];
	int num;
};

void readfile (ifstream& fin, vector<currency>& vec)//считывание файла, первая задача
{
	char prom[len];
	char prom_for_nominala[len];
	char prom_for_number[len];
	int i;
	currency object;
	ifstream data;
	if(!fin)
		cout<<"Файл не найден, какая жалость";
	else
	{
		cout << endl << "Все данные прочитаны и размещены в векторе."<<endl;
		while (fin.getline (prom, len, '\n'))
		{
			object.num = 0;
			object.nominal = 0;
			for (int j = 0 ; j < len ; j++)
				object.name[j] = ' ';
			
			i = 0;
			while (prom[i] != ':')//доходим до конца номинала
				i++;
			int j;
			for (j = 0; j < i - 1 ; j++)//записываем в промежуточный массив номинал
				prom_for_nominala[j] = prom[j];

			prom_for_nominala[j] = '\0';
			int number = 0;
			for (int k = i - 2 ; k >= 0 ; k--)
			{
				
				object.nominal = object.nominal + pow (10.0 , k) * (prom_for_nominala[number] - '0');//записываем номинал числа в object
				number++;
			}
			i = i + 2;
			j = i;//запомниаем i, как начало названия купюры
			while (prom[j] != ':')//доходим дальше по считанной строке до названия
				j++;
			for (int k = i ; k < j - 1 ; k++)//записываем сразу в object название
				object.name[k - i] = prom[k];

			j = j + 2;
			i = j;
			while (prom[i] != '\0')//считываем количество купюр
				i++;
			for (int k = j ; k < i ; k++)//записываем в промежуточный массив количество
				prom_for_number[k - j] = prom[k];
			int count = 0;
			for (int k = i - j - 1 ; k >= 0 ; k--)
			{
				object.num = object.num + pow (10.0 , k) * (prom_for_number[count] - '0');//записываем количество купюры в object
				count++;
			}
			vec.push_back(object);
		}
	}
}

bool razmen(int kupura, int i, int j, vector<int>& numbers)//вторая задача
{
	if (kupura == 0)//если равно нулю=>можно разменять
		return true;
	if (i > 6)//иначе, нет
		return false;
	if (kupura >= mass[i])//если значение купюры больше, чем сравниваемый номинал
	{
		kupura = kupura - mass[i];//вычитаем из введенного пользователем числа номинал
		numbers.push_back(mass[i]);
		i++;//следующий номинал
		if (razmen (kupura, i, j, numbers))//рек
			return true;
		else
			return false;
	}

	if (kupura < mass[i])//если купюра меньше номинала, его не рассматриваем
	{
		i++;//следующий номинал
		if (razmen(kupura, i, j, numbers))
			return true;
		else
			return false;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	vector<currency> vect;
	const char * data = "currency.txt";
	ifstream finp(data);
	readfile(finp, vect);
	
	int kupura;//начало второй задачи
	cout<<"Введите купюру, которую нужно разменять:";
	cin>>kupura;
	vector<int> numbers;
	if (razmen(kupura, 0 , 0, numbers))
	{
		cout<<"Размен:";
		for (int i = 0 ; i < numbers.size() ; i++)
			cout<<numbers[i]<<" ";
	}
	else
		cout<<"К сожалению, разменять купюру не удалось!";
	return 0;
}

