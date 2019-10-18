// ------------------------------------------------------------	//
// Программа случайным образом заполняет 13 из 15 элементов массива.
// Пользователь вводит два числа, которые программа ставит перед и после
// максимального элемента массива
// Среда разработки: Microsoft Visual C++ 2012 Express			//
// Версия программы: 1.00  |  Автор: Денисов Д.М.,ПМИ,172			//
// Дата последнего изменения: 30.11.2013 						//
// ------------------------------------------------------------	//


#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int random(int x[15])	//заполнение массива случайными числами
{
	for (int i = 0 ; i<=12 ; i++)
	{
		x[i] = rand();
		cout<<"arr["<<i<<"]="<<x[i]<<endl;
	}
	return x[15];
}

int num_max(int x[15])	//поиск максимального элемента
{
	int max = x[0];
	int num;

	for (int i = 0 ; i<=12 ; i++)
		if (x[i] > max)
		{
			max = x[i];
			num = i;
		}

	return num;	//возвращаем в main номер,так как нам не нужно само значение,нам нужен только номер
}

int first_perevod(int x[15],int num,int chislo)	//"сдвиг" значений,начиная с максимума(включая) вправо
{
	for(int i = 13 ; i>num ; i--)
		x[i] = x[i-1];

	x[num] = chislo;

	return x[15];

}

void second_perevod(int x[15],int num,int chislo)	//"сдвиг", начиная с максимума(не включая) вправо
{
	for(int i = 14 ; i>(num+2) ; i--)
		x[i] = x[i-1];

	x[num+2] = chislo;
	cout<<"Преобразованный массив:";	//не возвращаемся в main и в этой же функции выводим преобразованный массив
	
	for (int i = 0 ; i<=14 ; i++)
		cout<<"arr["<<i<<"]="<<x[i]<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int arr[15];
	int a,b;

	setlocale(LC_CTYPE, "rus");
	srand(time(NULL));
	cout<<"Введите первое число,которое будет вставлено перед максимальным числом:";
	cin>>a;
	cout<<"Введите второе число,которое будет вставлено после максимального числа:";
	cin>>b;
	cout<<"Случайно сгенерированный массив:";
	random(arr);
	int max=num_max(arr);	//номер максимального элемента массива
	cout<<"Номер максимального элемента:"<<max<<endl;
	first_perevod(arr,max,a);
	second_perevod(arr,max,b);

	return 0;
}

