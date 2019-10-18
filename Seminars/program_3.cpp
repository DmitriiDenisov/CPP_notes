 ------------------------------------------------------------	
 Программа вычисляет сумму цифр семизначного числа.Также выполняется проверка,
 является ли таковым число.
 Среда разработки Microsoft Visual C++ 2012 Express			
 Версия программы 1.00   Автор Денисов.Д.М,ПМИ,172				
 Дата последнего изменения 30.11.2013 			
 ------------------------------------------------------------	
#include stdafx.h
#include iostream
using namespace std;

int summa_cifr(int a)	пользовательская функция,вычисляющая сумму цифр числа
{
	int sigma = 0;

	while (a)
	{
		sigma = sigma + a % 10;
		a = a  10;
	}

	return sigma;
}

int _tmain(int argc, _TCHAR argv[])
{
	int chislo;

	coutPlease,enter the number;
	cinchislo;

	while ((chislo1000000)(chislo9999999))	Проверка условия задачи(проверяет оба условия задачи)
	{
		coutError!Enter chislo'n';
		cinchislo;
	}

	coutSumma cifrsumma_cifr(chislo);
	return 0;
}

