// ------------------------------------------------------------	//
// //Программа выполняет три арифметических действия (сложение,вычитание,
// умножение) чисел, выходящих за рамки стандартных типов int и др.)
// Среда разработки: Microsoft Visual C++ 2010 Express			//
// Версия программы: 3.2  |  Автор: Денисов Д.М.,ПМИ,172			//
// Дата последнего изменения: 22.12.2013 						//
// ------------------------------------------------------------	//
#include "stdafx.h"
#include <iomanip>
#include <windows.h>//требуется для "красивого" вывода
#include <string>
#include <iostream>
using namespace std;

int scetcik = 0;//счетчик количества неверно введённых значений. Необходим для "красивого" вывода

int proverka(string a, int num)//функция, проверяющая, подходят ли введенные числа
{
	int count = 0;
	int flag = 1;
	int x = a.length();

	if (x > 31)
	{
		scetcik++;
		cout<<"Одно из чисел слишком большое!"<<endl;
		cout<<"Не издевайтесь над программой!"<<endl;
		return 0;
	}



	if ((!(a[0] == '+')) && (!(a[0] == '-'))&&(!((a[0] >= 48) && (a[0] <= 57))))//отдельно проверяем нулевой элемент, из-за наличия знака
		flag=0;

	for (int i = 1;i < x ; i++)
		if ((a[i] < 48) || (a[i] > 57))//проверяем остальные элементы на наличие посторонних символов
			flag = 0;

	if (flag == 0)
	{
		scetcik++;
		cout<<"Вы ввели посторонние символы!"<<endl<<"Не издевайтесь над программой!"<<endl;
		if (num > 10)//датчик тролля
		{
			cout<<"Программа поняла, что вы троль и и поэтому вынуждена закрыться!"<<endl<<"Всего хорошего!"<<endl;
			exit(0);
		}
		return 0;
	}
	return 1;
}

void vivod(char *arr)
{
	int i = 1;

	while ((i <= 31) && (arr[i] == '0'))
		i++;

	if (i == 32)
		cout<<0;

	for (int j = i ; j < 32 ; j++)
		cout<<arr[j];

	cout<<endl;
}

void zanyl(char *mass)
{
	for (int i = 0 ; i < 32 ; i++)
		mass[i] = '0';
}

char deist(string a, string b, char sposob)
{
	char sign;
	bool flag = 0;

	do{
		if (flag == 1)//случай, если введённый знак не +,-,*
		{
			scetcik++;
			cout<<"К сожалению, вы ввели недопустимый символ."<<endl<<"Не мучайте программу!"<<endl<<"Попробуйте еще раз"<<endl;
		}
		cout<<"Пожалуйста, введите знак(+,- или *):"<<a<<" "<<b<<"=";

		int d = 0;
		while ((d-2) != b. length())//цикл переводит курсор между двумя числами
		{
			d++;
			cout<<"\b";
		}

		cin>>sign;
		flag=!((sign == '+') || (sign == '-') || (sign == '*'));
	}while(flag);//пока не будет введен один из знаков +,-,* цикл будет повторяться

	if (sposob == '0')//если пользователь выбрал "красивый" формат вывода, то курсор
		//перемещается на клетку после знака равно
	{
		int c = 38+a. length()+b. length();
		COORD position = {c,4+4*scetcik}; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
	}
	return sign;
}

char znac_chisla(string a)//возвращает знак числа
{
	char flag;

	if (a[0] == 45)
		flag = '-';
	else
		flag = '+';
	return flag;
}

string ydal_znak(string a)
{
	if ((a[0] == 43) || (a[0] == 45))
		a. erase(0, 1);
	return a;
}

int sravnenie(string a, string b)//сранивает введенные числа, без учета знака
{
	int flag;
	int y = b. length();
	int x = a. length();

	if (x > y)
		flag = 1;
	if (x < y)
		flag = 2;
	if (x == y)//длины равны
	{
		int i = 0;
		while ((i < x) && (a[i] == b[i]))//используется факт того, что ASCII коды цифр удовлетворяют
			//тем же неравенствам, что и неравенства между цифрами
			i++;
		if (i == x)//случай,если числа равны
			flag = 0;
		else
		{
			if (a[i] > b[i])
				flag = 1;
			else
				flag = 2;
		}
	}
	return flag;//возвращает 1-первое больше,2-второе,0-равны
}

void zapolnenie(char *mass, string str, int dlina)//заполняет наши массивы цифрами.Заполнение идет с конца
{
	int n = 31;

	while(dlina > 0)
	{
		mass[n] = str[dlina - 1];
		n--;
		dlina--;
	}
}

void summa(char *arr1, char *arr2)
{
	for (int i = 31 ; i >= 1 ; i--)//в нулевом знак, поэтому до i <= 1
	{
		if(arr1[i] + arr2[i] - '0' > '9')//если сумма локального столбца превысит 10
		{
			if (i == 1)//случай переполнения разрядной сетки
			{
				cout<<"К сожалению, вы превысили данный вам лимит в 32 символа,поэтому программа вынуждена закрыться";
				exit(0);
			}
			arr1[i] = '0' + (arr1[i] + 2 + arr2[i] - '0') % 10;
			arr1[i - 1] = arr1[i - 1] + 1;//в следующий разряд переносим 1
		}
		else
			arr1[i]=arr1[i] + arr2[i] - '0';
	}
}

void razn(char *arr1, char *arr2)
{
	for (int i = 31 ; i >= 1 ; i--)//в нулевом знак, поэтому до i <= 1
	{
		if(arr1[i] - arr2[i] + '0' < '0')//случай, если в локальном столбце вычитаем из меньшего бОльшее
		{
			arr1[i - 1] = arr1[i - 1] - 1;//переносим 1 из старшего разряда
			arr1[i]=arr1[i] + 10 - arr2[i] + '0';//получаем 10 в нашем локальном столбце
		}
		else
			arr1[i] = arr1[i] - arr2[i] + '0';
	}
}

void ymnoz_na_chislo(char *arr, char *arr_rez, char cons, int num, int dlina)
{
	char arr_prom[32];//промежуточный массив, в нем хранится результат умножения конкретной цифры на первое число
	int k = 0;
	int flags[32];//массив, отвечающий за идентификацию нулей, получившихся в рез-те вычислений
	//то есть отличаем нули, которые были изначально от тех, которые мы перезаписали

	for (int i = 0 ; i <= 31 ; i++)
		flags[i] = 0;

	for (int i = 0 ; i <= 31 ; i++)
		arr_prom[i] = '0';

	for (int i = 31 ; i >= dlina ; i--)//рассматриваем первое число с конца
	{
		int x = (arr[i] - '0')*(cons - '0');//умножаем две цифры
		if(x >= 10)//дальше идет много вариаций развития мобытий, разобраны все возможные случаи
		{
			if (k == 0)
			{
				k = x / 10;
				arr_prom[i - num]=x % 10 + '0';
				if (arr_prom[i - num] == '0')
					flags[i - num] = 1;
			}
			else
			{
				if (x % 10 + k >= 10)
				{
					arr_prom[i - num] = (x % 10 + k) % 10 + '0';
					if (arr_prom[i - num] == '0')
						flags[i - num] = 1;
					k = (x + k) / 10;
				}
				else
				{
					arr_prom[i - num]=x % 10 + k + '0';
					k = x / 10;
				}
			}
		}
		else
			if (x + k + '0' > '9')
			{
				arr_prom[i - num] = (x + k) % 10 + '0';
				if (arr_prom[i - num] == '0')
					flags[i - num] = 1;
				k = (x + k) / 10;
			}
			else
			{
				arr_prom[i - num] = x + k + '0';
				k = 0;
			}
	}
	if (k > 0)
	{
		int i = 0;

		while ((i <= 31) && (arr_prom[i] == '0') && (flags[i] == 0))//определяем "начало"полученного числа, именно здесь нужно отличать нули при помощи flags													
			i++;

		arr_prom[i - 1] = k + '0';
	}
	summa(arr_rez, arr_prom);//суммируем результирующий и промежуточный
}

void ymnoz(char *arr1, char *arr2)
{
	char arr_rez[32];//в этом массиве будет хранится итоговый результат

	for (int i = 0 ; i <= 31 ; i++)
		arr_rez[i] = '0';

	int i = 31;
	int scetc = 0;//переменная "сдвига":при умножении столбиком у нас получается "лестница",
	//эта переменная отвечает за этот сдвиг.
	int j = 0;

	int dlina_mass1 = 1;

	while ((dlina_mass1 <= 31) && (arr1[dlina_mass1] == '0'))//вычисляем "начало" первого числа
		dlina_mass1++;

	int dlina_mass2 = 1;

	while ((dlina_mass2 <= 31) && (arr2[dlina_mass2] == '0'))//вычисляем "начало" второго числа
		dlina_mass2++;

	int c = 31;
	while (c >= dlina_mass2)//рассматриваем по одной цифре второго числа и всё первое число
	{
		ymnoz_na_chislo(arr1, arr_rez, arr2[c], scetc, dlina_mass1);
		c--;
		scetc++;
	}

	vivod(arr_rez);
}

int _tmain(int argc, _TCHAR* argv[])
{
	char mass1[32];//массив первого числа
	char mass2[32];//массив второго числа
	string chislo1;
	string chislo2;
	int flag;
	int count;
	char edinorog;//необычная переменная, отвечает за бесконечный ввод
	char znak_deist_char;
	char sposob;//параметр опционного вывода

	setlocale(LC_ALL, "Russian");

	do{
		cout<<"Здравствуйте!Введите 0 для красивого вывода(  ВНИМАНИЕ! вся ответсвенность за"<<endl<<"некорректный вывод лежит на пользователе!) или 1 для обычного вывода:";
		cin>>sposob;
	}while((!(sposob == '0')) && (!(sposob == '1')));

	do{
		count = 0;

		zanyl(mass1);
		zanyl(mass2);

		do{
			count++;
			cout<<"Введите chislo1:";
			cin>>chislo1;
			cout<<"Введите chislo2:";
			cin>>chislo2;
		}
		while (!(proverka(chislo1, count) && proverka(chislo2, count)));

		char sgn_chislo1 = znac_chisla(chislo1);//запоминаем знак числа1
		char sgn_chislo2 = znac_chisla(chislo2);//запоминаем знак числа2

		znak_deist_char = deist(chislo1, chislo2, sposob);//пользователь вводит знак действия

		if (sposob == '1')
			cout<<"Результат:";


		chislo1 = ydal_znak(chislo1);//удаляем знаки чисел, после чего сравниваем их (то есть сравниваем по модулю)
		chislo2 = ydal_znak(chislo2);

		switch(sravnenie(chislo1, chislo2)){
		case 2:	
			flag = 1;//переменная идентифицирует, что произошел "переворот" - второе число
			//записалось в первый массив и наоборот
			mass1[0] = sgn_chislo2;//знак записывается в массив!
			mass2[0] = sgn_chislo1;
			zapolnenie(mass1, chislo2, chislo2. length());
			zapolnenie(mass2, chislo1, chislo1. length());
			break;
		case 1:
			flag = 0;
			mass1[0] = sgn_chislo1;
			mass2[0] = sgn_chislo2;
			zapolnenie(mass1, chislo1, chislo1. length());
			zapolnenie(mass2, chislo2, chislo2. length());
			break;
		case 0:	
			mass1[0] = sgn_chislo2;
			mass2[0] = sgn_chislo1;
			zapolnenie(mass1, chislo2, chislo2. length());
			zapolnenie(mass2, chislo2, chislo2. length());
			break;
		}


		switch (znak_deist_char){//разветвление на операции (сложение,разность,умножение)
		case '*':
			if (mass1[0] != mass2[0])
				cout<<"-";
			ymnoz(mass1, mass2);
			break;
		case '+':
		case '-':
			if (mass1[0] == '+')//далее идут все возможные варианты сложения и вычитания. Разобраны все случаи
			{
				if (mass2[0] == znak_deist_char)
				{
					if (sgn_chislo1 == '-')
						cout<<"-";
					summa(mass1, mass2);
					vivod(mass1);
				}
				else
				{
					if ((flag == 1) && (!(sgn_chislo1 == '-')))
						cout<<"-";
					razn(mass1, mass2);
					vivod(mass1);
				}
			}
			else
			{
				if (mass2[0] == znak_deist_char)
				{
					if ((flag == 0) || (sgn_chislo1 == '+'))
						cout<<"-";
					razn(mass1, mass2);
					vivod(mass1);
				}
				else
				{
					if ((flag == 0) || (sgn_chislo1 == '-'))
						cout<<"-";
					summa(mass1, mass2);
					vivod(mass1);
				}
			}
			break;
		}
		cout<<"Введите 0, чтобы программа отдохнула,для продолжения-любой символ:";
		cin>>edinorog;
		scetcik++;//та самая переменная "красивого" вывода
	}while (!(edinorog == '0'));

	cout<<"Спасибо!"<<endl;
	return 0;
}