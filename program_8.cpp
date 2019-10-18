// ------------------------------------------------------------	//
// Программа  вычисляет среднее арифметическое в левой половине массива (элементы с индексами[0..14]),//
//также считает среднее арифметическое в правой половине массива(элементы с индексами [15...29]
//После чего вычисляет сумму элементов массива, которые расположены между ближайшими(по значению)
//к вычисленным средним  значениям элементами(исключая "граничные" значения).
//Заполнение:Так как в задаче не было сказано про значения в массиве, то автор программы выбрал
//произвольный промежуток значений [1;50],таким образом,массив заполняется случайными
//целыми числами из отрезка [1;50].В программе реализована
//одна пользовательская функция, которая вычисляет сумму.Вывод среднего значения первой и второй половины
//массива выводится в функции main,ровно как и сумма элементов между вычисленными элементами массива. Под средние арифметические
//отводится 3 знака после запятой//
// Среда разработки: Microsoft Visual C++ 2012 Express			//
// Версия программы: 1.02  |  Автор: Денисов Д.М.,ПМИ,172			//
// Дата последнего изменения: 14.12.2013 						//
// ------------------------------------------------------------	//

#include "stdafx.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;

int summa(int *arr,double sr1,double sr2,int left,int right)//в задаче прототип функции был именно такой
														//Однако функция никак не использует две переменные  типа double,которые
													//были в задаче,поэтому их можно было и убрать
{
	int sum=0;//переменная суммы.Отвечает за сумму между left и right,не включая их
	for (int i=left+1;i<right;i++)//считаем сумму между left и right,не включая их
		sum=sum+arr[i];
	return sum;//возвращаем полученное значение для вывода в main-е
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int N=30;//размерность массива
	const int gran=14;//делит массив на 2 части-левую и правую
	double sr_right;//среднее значение правой части
	double sr_left;//среднее значение левой части
	double sigma=0;//промежуточная переменная,вычисляющая сумму левой и правой частей
	int arr[N];

	srand(time(NULL));
	setlocale(LC_ALL, "Rus");

	for(int i=0;i<N;i++)//заполнение массива
		arr[i]=rand()%50+1;

	//for (int i=0;i<N;i++)//для удобства можете включить вывод всех элементов на экран,чтобы лично убедиться,что программа работает правильно
		//cout<<"The"<<i<<"-th number = "<<arr[i]<<endl;

	for(int i=0;i<=gran;i++)//вычисляем сумму левой части
		sigma=sigma+arr[i];

	sr_left=sigma/15;//вычисляем среднее арифметическое левой части
	sigma=0;//будем использовать эту же переменную и для вычисления суммы правой части

	for (int i=gran+1;i<N;i++)//вычисляем сумму правой части
		sigma=sigma+arr[i];

	sr_right=sigma/15;//вычисляем среднее арифметическое правой части

	double min_left=abs(sr_left-arr[0]);//Будем искать элемент,наиболее близкий по значению к среднему
	int num_left=0;						//арифметическому левой части.Предполагаем,что это элемент с индексом 0
										
	for (int i=1;i<=gran;i++)//запускаем цикл от [1;14] чтобы найти элемент наименее отличающийся от левого ср.арифм.
		if(abs(sr_left-arr[i])<min_left)//если меньше=>запоминаем это число и его номер
		{
			min_left=abs(sr_left-arr[i]);
			num_left=i;
		}

		double min_right=abs(sr_right-arr[gran+1]);//по аналогии делаем и для правой части
		int num_right=gran+1;

		for (int i=gran+2;i<N;i++)
			if(abs(sr_right-arr[i])<min_right)
			{
				min_right=abs(sr_right-arr[i]);
				num_right=i;
			}
			cout<<fixed<<setprecision(3)<<"Среднее значение первой половины массива:"<<sr_left<<endl<<"Среднее значение второй половины массива="<<sr_right<<endl;//3 знака после запятой
			cout<<"Сумма элементов с позиции "<<num_left+1<<" по "<<num_right+1<<"="<<summa(arr,sr_left,sr_right,num_left,num_right)<<endl;//передаем в функцию:массив,ср.ариф.левой части
			return 0;									//ср.арифм. правой и номера элементов правой и левой частей, наименее отличающихся от соотв. средних арифм.
														//P.S прибавляем к num_left 1,так как в массиве счет начинается с нуля.Аналогично и для num_right
}

