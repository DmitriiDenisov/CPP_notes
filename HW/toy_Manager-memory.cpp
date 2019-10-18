// ------------------------------------------------------------------------------------------	
// Игрушечный менеджер памяти. Программа имитирует работу с памятью.						   |
// Среда разработки: Microsoft Visual C++ 2010 Express										   |
// Версия программы: 13.2  |  Автор: Денисов Д.М.,ПМИ,172									   |
// Дата последнего изменения: 22.02.2014													   |
//
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

struct one_block
{
	int num_of_take;//количество занятый байт(всего в одном блоке 8 байт)
	int depends_on;//блок зависит от такого-то блока
	bool allocation;//занят ли блок
	bool main;//главный ли блок(от него зависят)
};

struct all_bloks
{
	one_block* mass_bloki;//указатель на дин. массив
	int num_blokov_free;//кол-во не выделенных блоков
};

void toymp_Initializememorymanager(size_t N, all_bloks &bloks)//инициализация массива блоков
{
	bloks.num_blokov_free = N;
	bloks.mass_bloki = new one_block[N];
}

bool proverka(string a)//проверка, содержит ли число посторонние символы(буквы, точки и тд)
{
	int len = a.length();

	for (int i = 0;i < len ; i++)
		if ((a[i] < '0') || (a[i] > '9'))
			return false;

	return true;
}

int num_need_bloks(int num)//количество необходимых блоков, чтобы заполнить информацию
{
	int need = num / 8;
	int promez = num % 8;
	if (promez != 0)
		need++;
	return need;
}

int type_definition(string a)//определяет тип переменной(для ввода типа array,struct)
{
	int sum = 0;
	if (a == "char")
		sum = sizeof(char);
	if (a == "short int")
		sum = sizeof(short int);
	if (a == "int")
		sum = sizeof(int);
	if (a == "long int")
		sum = sizeof(long int);
	if (a == "float")
		sum=sizeof(float);
	if (a=="double")
		sum=sizeof(double);
	return sum;
}

void inf_blok(all_bloks &bloks, int number)//информация об одном блоке
{
	if (bloks.mass_bloki[number].allocation == false)
		cout<<"Блок еще не выделен"<<endl;
	else
	{
		cout<<hex<<showbase<<endl<<"Внутренний адрес блока:"<<number;
		cout<<endl<<"Машинный адрес блока:"<<&(bloks.mass_bloki[number])<<endl;
		cout<<dec<<"В блоке занято "<<bloks.mass_bloki[number].num_of_take<<" байт"<<endl;
	}
}

void inf_all(all_bloks &bloks, const int N)//информация о всех блоках
{
	cout<<endl<<"Информация о текущем состоянии памяти:"<<endl;

	for (int j = 0 ; j < N ; j++)
	{
		cout<<endl<<"Информация о "<<j + 1<<" блоке:";
		inf_blok(bloks, j);
	}
}

void* toymp_allocateBlock(int sposob, int need, const int N, all_bloks &bloks)//возвращает указатель на блок, начиная с которого нужно записывать
{
	int i = 0,j = 0;
	switch(sposob)
	{
	case 1: //для первой тактики

		while ((j < need) && (i < N))
		{
			if (bloks.mass_bloki[i].allocation == false)
				j++;
			else
				j = 0;
			i++;
		}

		if ((i == N) && (j < need))
			return NULL;	
		else
		{
			void* ptr;
			ptr = &(bloks.mass_bloki[i - need]);
			return ptr;
		}

		break;

	case 3:
	case 2:	//для второй и третьей:ищем все промежутки пустых блоков и выбираем наименьший промежуток (или наибольший)
		int max = -1,min = N + 1,number_of_min = -1,number_of_max = -1;

		do
		{
			if (bloks.mass_bloki[i].allocation == false)
				j++;
			else
			{
				if ((j >= need) && (min > j))
				{
					min = j;
					number_of_min = i - j;
				}
				if ((j >= need) && (max < j))
				{
					max = j;
					number_of_max = i - j;
				}
				j = 0;
			}
			i++;
		}while (i < N);

		if ((j != 0) && (min > j))
			number_of_min = i - j;
		if ((j != 0) && (max < j))
			number_of_max = i - j;

		if (sposob == 2)
		{
			if (number_of_min == -1)
			{
				void* ptr;
				ptr = NULL;
				return ptr;
			}
			void* ptr;
			ptr = &(bloks.mass_bloki[number_of_min]);
			return ptr;
		}
		if (sposob == 3)
		{
			if (number_of_max == -1)
			{
				void* ptr;
				ptr = NULL;
				return ptr;
			}
			void* ptr;
			ptr = &(bloks.mass_bloki[number_of_max]);
			return ptr;
		}
	}
}

void filling(all_bloks &bloks, const int N, int k, int num)//заполняет блоки
{
	int main_number = k;
	int promez1 = num / 8;
	int promez2 = num % 8;
	if (promez2 != 0)
		promez1++;
	bloks.mass_bloki[k].main = true;
	bloks.mass_bloki[k].depends_on = -1;

	while (num >= 8)
	{
		num = num - 8;
		bloks.mass_bloki[k].num_of_take = 8;
		bloks.mass_bloki[k].allocation = true;
		if (bloks.mass_bloki[k].main == false)
			bloks.mass_bloki[k].depends_on = main_number;
		k++;
	}

	if (num != 0)
	{
		bloks.mass_bloki[k].num_of_take = promez2;
		bloks.mass_bloki[k].allocation = true;
		if (bloks.mass_bloki[k].main == false)
			bloks.mass_bloki[k].depends_on = main_number;
	}

	cout<<"Выделено памяти:"<<promez1 * 8<<" байт"<<endl<<"Потребовалось ячеек памяти:"<<promez1;
	bloks.num_blokov_free = (bloks.num_blokov_free) - promez1;
	cout<<endl<<"Осталось свободных ячеек памяти:"<<bloks.num_blokov_free<<endl<<endl;
}

void toymp_FreeBlock(void * number)//очищение блока по указателю
{
	one_block * pointer = (one_block*)number;
	pointer->allocation = false;
	pointer->main = false;
	pointer->depends_on = -1;
}

bool text_and_input(all_bloks &bloks, int &N, int &sposob, bool flag)//текстовый интерфейс
{
	int command, number, i, x;
	void* k;
	string dannye, type, chislo;
	if (flag == true)//при первом запуске попадаем сюда
	{
		cout<<"Добро пожаловать в Toy ""Memory Manager"""<<endl;
		do
		{
			cout<<"Введите способ(1-first fit,2-best fit,3-worst fit):";
			getline(cin, chislo);	
			x = atoi(chislo.c_str());
		}while ((proverka(chislo) == false)||((x != 1) && (x != 2) && (x !=3 )));//проверки, далее все вводные данные по аналогии проверяются

		sposob = x;

		do
		{
			cout<<"Введите количество блоков, необходимое вам для работы:";
			getline(cin, chislo);
			x = atoi(chislo.c_str());
		}while ((proverka(chislo) == false) || (x == 0));

		N = x;
	}
	else
	{

		do
		{
			cout<<endl<<"(1 - выделение памяти, 2 - выход из программы, 3 - стереть блок, 4-информация"<<endl<<"об одном блоке, 5-информация о всех блоках,6-стереть все блоки,7-смена тактики)"<<endl;
			cout<<"Введите команду (1/2/3/4/5/6/7):";
			getline(cin, chislo);
			x = atoi(chislo.c_str());
		}while((proverka(chislo) == false) || ((x != 1) && (x != 2) && (x != 3) && (x != 4) && (x != 5) && (x != 6) && (x != 7)));

		command = x;

		switch (command)
		{

		case 1:
			cout<<endl<<"Подсказка:(fixedsize(size), struct(char,short int, int, long int, float, double, end), array(type,size))";
			cout<<endl<<"Введите спецификацию данных(fixedsize/struct/array):";
			getline(cin, dannye);

			if (dannye == "fixedsize")
			{

				do{	
					cout<<"Введите параметр:";
					getline(cin, chislo);
					x = atoi(chislo.c_str());
				}while((proverka(chislo) == false) || (x == 0));

				number = x;
				k = toymp_allocateBlock(sposob, num_need_bloks(number), N, bloks);//определяем блок, начиная с которого нужно записывать

				if (k != 0)
				{
					int q = 0;
					while ((k != &(bloks.mass_bloki[q])))
						q++;
					filling(bloks, N, q, number);//заполняем массив
				}

				else
					cout<<"Не хватает памяти! Советуем очистить занятые ячейки!"<<endl;
			}

			if (dannye == "struct")
			{
				number = 0;
				string edinorog=" ";

				while (edinorog != "end")
				{
					cout<<"Введите параметр:";
					getline(cin, edinorog);
					if (edinorog != "end")
						number = number + type_definition(edinorog);
				}

				if (number == 0)
					cout<<"Введенные данные некорректны!";
				else
				{
					k = toymp_allocateBlock(sposob, num_need_bloks(number), N, bloks);//определяем, начиная с какого номера нужно записывать

					if (k != 0)
					{
						int q = 0;
						while ((k != &(bloks.mass_bloki[q])))
							q++;
						filling(bloks, N, q, number);//заполняем
					}

					else
						cout<<"Не хватает памяти! Советуем очистить занятые ячейки!"<<endl;
				}
			}

			if (dannye == "array")
			{
				cout<<"Введите параметр type:";
				getline(cin, type);
				int z = type_definition(type);

				while (z == 0)
				{
					cout<<"Введите параметр type:";
					getline(cin, type);
					z = type_definition(type);
				}

				do{
					cout<<"Введите параметр size:";
					getline(cin, chislo);
					x = atoi(chislo.c_str());
				}while((proverka(chislo) == false) || (x == 0));

				number = x;
				number = number * z;
				k = toymp_allocateBlock(sposob, num_need_bloks(number), N, bloks);//определяем, с какого блока нужно записывать

				if (k != 0)
				{
					int q = 0;
					while ((k != &(bloks.mass_bloki[q])))
						q++;
					filling(bloks, N, q, number);//записываем
				}

				else
					cout<<"Не хватает памяти! Советуем очистить занятые ячейки!"<<endl;
			}
			break;

		case 2:
			cout<<endl<<"Спасибо за использование! Удачного дня!"<<endl;
			return false;

		case 3: cout<<"Вы можете стереть:";

			for (int j = 0 ; j < N ; j++)
				if (bloks.mass_bloki[j].allocation == true)
					cout<<" "<<j + 1;

			cout<<" блоки.";

			do{	
					cout<<endl<<"Введите номер блока, который вы хотите стереть:";
					getline(cin, chislo);
					x = atoi(chislo.c_str());
			}while((proverka(chislo) == false) || (x == 0) || (x > N));
			i=x-1;

			if (bloks.mass_bloki[i].main == true)//если блок главный(т.е. от него зависят другие блоки)
			{
				void* ptr1;
				ptr1 = &(bloks.mass_bloki[i]);
				toymp_FreeBlock(ptr1);//очищаем главный блок
				cout<<"Блок успешно стёрт!"<<endl;
				bloks.num_blokov_free = bloks.num_blokov_free + 1;

				int x = i + 1;
				while ((x < N) && (bloks.mass_bloki[x].depends_on == i))//очищаем зависимые блоки
				{
					ptr1 = &(bloks.mass_bloki[x]);
					toymp_FreeBlock(ptr1);
					bloks.num_blokov_free = bloks.num_blokov_free + 1;
					x++;
				}
			}
			else
				cout<<"Блок стереть нельзя, так как он не является началом ранее записанной информации или еще не выделен"<<endl;
			break;

		case 4:
			do{
				cout<<"Введите номер блока, информацию о котором вы хотите узнать:";
				getline(cin, chislo);
				x = atoi(chislo.c_str());
			}while((proverka(chislo) == false) || (x == 0) || (x > N));

			number = x - 1;
			inf_blok(bloks, number);
			break;

		case 5: inf_all(bloks, N);
			break;
		case 6:
				for (int i = 0 ; i < N ; i++)
				{
					void * ptr1;
					ptr1 = &(bloks.mass_bloki[i]);
					toymp_FreeBlock(ptr1);
				}
				bloks.num_blokov_free=N;
					cout<<"Все блоки успешно стерты!"<<endl;
				break;
		case 7:	
			do{
				cout<<"Выберете тактику:(1-first fit, 2-best fit, 3-worst fit):";
				getline(cin, chislo);
				x = atoi(chislo.c_str());
			}while((proverka(chislo) == false) || ((x != 1) && (x != 2) && (x != 3)));

			sposob = x;
			break;
		}
	}
	return true;
}

void toymp_DeinitializeMemoryManager(all_bloks &bloks)//финализация менеджера памяти
{
	delete bloks.mass_bloki;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N, sposob;
	bool flag;
	void* ykaz;
	all_bloks bloks;
	setlocale(LC_ALL,"Russian");
	system("color F0");
	text_and_input(bloks, N, sposob, true);//первый ввод-вводим N и sposob
	toymp_Initializememorymanager(N, bloks);//инициализируем

	for (int i = 0 ; i < N ; i++)//зполняем по умолчанию
	{	
		ykaz = &(bloks.mass_bloki[i]);
		toymp_FreeBlock(ykaz);
	}

	do
	flag = text_and_input(bloks, N, sposob, false);//бесконечный ввод, выход осуществляется при вводе 2
	while (flag);

	toymp_DeinitializeMemoryManager(bloks);//финализация менеджера памяти(удаляем динамический массив)
	return 0;
}