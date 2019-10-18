// ------------------------------------------------------------	//
// Программа получает на вход или генирирует данные забега 25 участников(в диапозоне [15;95])
// и составляет четверку самых быстрых спортсменов,указывая их номера, результаты,а также их общий результат//
// Среда разработки: Microsoft Visual C++ 2012 Express			//
// Версия программы: 1.00  |  Автор: Денисов Д.М.,ПМИ,172			//
// Дата последнего изменения: 30.11.2013 						//
// ------------------------------------------------------------	//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 25;

int random(int x[N])	//функция рандомного заполнения массива
{

	for (int i = 0; i<N ; i++)
		x[i] = rand() % 81 + 15;

	return x[N];
}

int klava(int x[N])	//пользователь заполняет массив,вводя все элементы с клавиатуры
{

	for (int i = 0; i<N ; i++)
	{
		cout<<"Enter x["<<i<<"]:";
		cin>>x[i];
	}

	return x[N];
}

void athlets(int x[N])	//функция нахождения быстрейших спортсменов и их результатов
{
	int min;//минимальный результат
	int num = 0;//номер спортсмена
	double sum = 0;//суммированный результат лучших 4-ех спортсменов

	for (int j = 1 ; j<=4 ; j++)	//цикл от 1 до 4,так как ищем первых 4-ёх быстрейших
	{
	min = x[0];
	for (int i = 0 ; i<N ; i++)
		if (x[i] < min)
		{
			min = x[i];
			num = i;
		}
	sum = sum + ( 10 + double(x[num]) / 100);
	cout<<"Номер "<<j<<"-ого(его) быстрейшего спортсмена "<<num + 1<<".Его время:"<<10 + double(x[num]) / 100<<endl;
	x[num] = 96;	//присваиваем x[num] 96,чтобы в следующем поиске минимума не "наткнуться" на это же число
	}
	cout<<"Их общее время:"<<sum;
}
int _tmain(int argc, _TCHAR* argv[])
{
	bool rand_or_klav;	//переменная "выбора" заполнения массива
	int arr[N];

	setlocale(LC_CTYPE, "rus"); 
	srand(time(NULL));
	cout<<"Введите 1,чтобы программа сгенерировала результаты случайным образом."<<endl<<"Или введите 0,чтобы ввести все 25 результатов:";
	cin>>rand_or_klav;

    if (rand_or_klav)
		random(arr);	//заполнение случайно сгенерированными числами,лежащими в диапозоне [15;95]
	else
		klava(arr);	//заполнение массива с клавиатуры

	for (int i = 0 ; i<N ; i++)
		cout<<"Результат"<<i + 1<<"-ого(его) спортсмена:"<<10 + double(arr [i] ) / 100<<endl;//все результаты

	athlets(arr);
	return 0;
}
