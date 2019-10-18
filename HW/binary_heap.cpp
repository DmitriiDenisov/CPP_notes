// Программа считывает 7 файлов, после чего определяет, является ли дерево, лежащее в каждом файле, бинарной кучей.							  |
// После программа предоставляет возможность пользователю работать с каждой из этих кучей, а также создавать новые кучи различными способами  |
// Автор программы: Денисов Дмитрий, ПМИ 172																								  |
// Среда разработки: Microsoft Visual Studio 2012 Express																					  |	
// Дата последнего изменения: 28.04.2014																									  |

#include "stdafx.h"
#include <iostream>
#include <conio.h>//для _getch()
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int len = 200;//макс. длина строки
const int N = 7;//количество файлов
const string data = "datafilei.txt";

int proverka(string a)//проверка введенного значения
{
	int len = a.length();
	for (int i = 0 ; i < len ; i++)
		if ((a[i] - '0' < 0) || (a[i] - '0' > 9))
			return -1;//если присутствуют лишние символы
	int num = 0;
	int count = 0;
	for (int k = len - 1 ; k >= 0 ; k--)
	{
		num = num + (a[count] - '0') * pow(10.0, k);
		count++;
	}
	return num;//если все в порядке, то вернуть само значение
}

class one_yzel//класс, описывающий одну вершину (узел)
{
private:
	int zhachenie;
	one_yzel* left;
	one_yzel* right;
public:
	//конструктор
	one_yzel::one_yzel(int k, one_yzel* left, one_yzel* right)
	{
		one_yzel::zhachenie = k;
		one_yzel::left = left;
		one_yzel::right = right;
	}

	void set_int(int k)
	{
		zhachenie = k;
	}

	void set_left_pointer(one_yzel* left_send)
	{
		left = left_send;
	}

	void set_right_pointer(one_yzel* right_send)
	{
		right = right_send;
	}

	int getnum()
	{
		return zhachenie;
	}

	one_yzel* get_left_pointer()
	{
		return left;
	}

	one_yzel* get_right_pointer()
	{
		return right;
	}

	~one_yzel()//деструктор
	{
		delete left;
		delete right;
	}
};

class task6//класс для 6 - ого задания
{
private:
	vector<int> vec;
public:

	void print(int n)//функция печати для 6 задачи
	{
		cout << endl;
		int i = 0;
		int count = 1;
		int k = 0;
		while (k != n)
		{
			cout << setw(3);
			while (i != count)
			{
				if (i < n)
					cout << vec[i] << " ";
				i++;
			}
			count = pow (2, (double) k + 2 ) - 1;
			cout << endl;
			k++;
		}
	}

	task6::task6(int n, int max_or_min)//конструктор заполняет вектор случайными числами в количестве n штук
	{
		int count = 0;
		int b = rand () % 29 + 71;//генерируем b из (70; 100)
		bool flag;
		while (count != n)
		{
			flag = true;
			int x = rand() % b + 1;//генерируем x из [1;b]
			for (unsigned int i = 0 ; i < vec.size() ; i++)//проверка, было ли уже это число
				if (vec[i] == x)
					flag = false;
			if (flag)
			{
				vec.push_back(x);
				count++;
			}
		}

		for (int i = 0 ; i < n ; i ++)
		{
			for (int j = i + 1 ; j < n ; j++)
				if (((max_or_min == 2) && (vec[j] > vec[i])) || ((max_or_min == 1) && (vec[i] > vec[j])))
				{
					system("cls");
					print (n);//пошагово выводим каждый "ход"
					char q = _getch();
					int k = vec[i];
					vec[i] = vec[j];
					vec[j] = k;
				}
		}
	}
};

struct tree{//структура для всего дерева
	int level;//количество уровней дерева
	int max_or_min;//является ли дерево max или min кучей
	one_yzel* root;//первый элемент списка
};

int recursion_reading(ifstream & stream, vector<one_yzel*>& vect_of_previous, int x)//функция рекурсивного заполнения списка
{
	//vect_of_previous - вектор, содержащий предыдущую строчку
	char prom[len];
	vector<one_yzel*> newvector;
	bool flag = true;
	int i = 0;//счетчик, "идущий" по строке
	int count = 0;//счетчик, "идущий" по вектору vect_of_previous
	int s = 0;//счетчик четности. Если четн => запиши в левый указатель, иначе в правый
	if (! stream.getline (prom, len, '\n'))
		return x;
	x++;//счетчик уровня дерева

	while (flag)
	{
		int j = i;
		while ((prom[i] != ' ') && (prom[i] != '\0'))
			i++;
		if (prom[i] == '\0')//последнее ли число в строке
			flag = false;
		int num = 0;
		one_yzel *pdr = new one_yzel(num, nullptr, nullptr);
		for (int k = i - j - 1 ; k >= 0 ; k--)//переводим в инт
		{
			pdr->set_int(pdr->getnum() + pow (10.0 , k) * (prom[j] - '0'));
			j++;
		}
		if (s % 2 == 0)
			vect_of_previous[count]->set_left_pointer(pdr);//присоединяем новый созданный объект к списку
		else
			vect_of_previous[count]->set_right_pointer(pdr);
		s++;
		count = s / 2;
		i++;
		newvector.push_back(pdr);//пихаем новый объект в вектор, который далее станет vect_of_previous
		if (flag == false)//если считаны все числа
			x = recursion_reading(stream, newvector, x);
	}
	return x;
}

void readcheck(ifstream & stream, vector<tree*>& vec_of_roots, int i)//функция, заполняющая общую инфу о дереве
{
	if (!stream)
	{
		cout<<"Файл не найден, какая жалость..."<<endl;
		exit(1);
	}
	else
	{
		vector<one_yzel*> vect_of_previous;
		cout << "Прочитан " << i + 1 <<"-ый(ой) файл!"<<endl;
		char prom[len];
		tree* treeA = new tree;//создаем структурную переменную, которая будет хранить дерево и всю инфу о нем
		treeA->root = new one_yzel(0, nullptr, nullptr);//создаем корень

		stream.getline (prom, len, '\n');//считываем первое число и заносим его, как первый элемент дерева(списка)
		int i = 0;
		while (prom[i] != '\0')
			i++;
		int number = 0;
		for (int k = i - 1 ; k >= 0 ; k--)
		{
			treeA->root->set_int(treeA->root->getnum() + pow (10.0 , k) * (prom[number] - '0'));//записываем номинал числа в object
			number++;
		}
		vect_of_previous.push_back(treeA->root);
		treeA->level = recursion_reading(stream, vect_of_previous, 1);//заполняем список
		vec_of_roots.push_back(treeA);

		vect_of_previous.erase(vect_of_previous.begin(), vect_of_previous.end()); 
	}
}

bool complete_tree(int level, vector<one_yzel*>& one_tree)//функция проверка на "полность" дерева, а также конвертации списка в вектор
{
	int number_of_reading = pow(2, (double)(level - 2)) - 1;//количество объектов, которое необходимо проверить (без учета последнего ряда)
	int count = 0;//счетчик количества проверенных объектов
	while (count != number_of_reading)
	{
		if (one_tree[count]->get_left_pointer() != nullptr)
			one_tree.push_back(one_tree[count]->get_left_pointer());
		if (one_tree[count]->get_right_pointer() != nullptr)
			one_tree.push_back(one_tree[count]->get_right_pointer());
		if ((one_tree[count]->get_left_pointer() == nullptr) || (one_tree[count]->get_right_pointer() == nullptr))
			return false;
		count++;
	}
	for (int i = pow (2, (double)(level - 2)) - 1; i < pow (2, (double)(level - 1)); i++)//отдельно рассматриваем предпоследний ряд
	{
		if (one_tree[i]->get_left_pointer() != nullptr)
			one_tree.push_back(one_tree[i]->get_left_pointer());
		if (one_tree[i]->get_right_pointer() != nullptr)
			one_tree.push_back(one_tree[i]->get_right_pointer());
	}
	return true;
}

bool max_heap (one_yzel* object)//проверка на max кучу
{
	if (object->get_left_pointer() == nullptr)
		return true;
	if (object->get_left_pointer()->getnum() <= object->getnum())
	{
		if (!max_heap(object->get_left_pointer()))//передаем в эту же функцию левый указатель
			return false;
	}
	else 
		return false;

	if (object->get_right_pointer() == nullptr)
		return true;
	if (object->get_right_pointer()->getnum() <= object->getnum())
	{
		if (!max_heap(object->get_right_pointer()))//передаем в эту же функцию правый указатель
			return false;
	}
	else 
		return false;
	return true;
}

bool min_heap (one_yzel* object)//провека на min кучу
{
	if (object->get_left_pointer() == nullptr)
		return true;
	if (object->get_left_pointer()->getnum() >= object->getnum())
	{
		if (!min_heap(object->get_left_pointer()))
			return false;
	}
	else 
		return false;

	if (object->get_right_pointer() == nullptr)
		return true;
	if (object->get_right_pointer()->getnum() >= object->getnum())
	{
		if (!min_heap(object->get_right_pointer()))
			return false;
	}
	else 
		return false;
	return true;
}

void vivod_pyramid(vector<one_yzel*>& one_tree, int level)//вывод пирамидой
{
	int count = 0;//количество выводов
	int otstyp = pow (2, (double)level) - 1;
	int x = 0;//с какого номера печатать
	int y = 1;//до какого номера печатать
	int z = 0;//регулятор отступа
	double k = 1;
	while (count < level)
	{
		cout << setw(otstyp - z) ;
		for (int i = x ; i < y ; i++)
		{
			if (i < one_tree.size())
				cout << one_tree[i]->getnum() << "  ";
		}
		x = pow (2, k) - 1;
		y = pow (2, k + 1) - 1;
		k++;
		count++;
		cout<<endl;
		z = z + 2;//уменьшаем отступ от левого края
	}
}

void vivod_stolbik(int level, vector<one_yzel*>& one_tree)//вывод столбиком
{
	cout << endl;
	unsigned int i = 0;//счетчик выведенных чисел в одной строке
	int count = 1;//требуемое количество выводов в одной строке
	int k = 0;//счетчик выводов
	while (k != level)
	{
		cout << setw(3);
		while (i != count)
		{
			if (i < one_tree.size())
				cout << one_tree[i]->getnum() << " ";
			i++;
		}
		count = pow (2, (double) k + 2 ) - 1;
		cout << endl;
		k++;
	}
}

int addition_rec(vector<one_yzel*>& one_tree, int num_prev, int num_now, int max_or_min)//функция рекурсивного добавления нового узла (задача 4)
{
	if (num_prev < 0)//отец рассматриваемого элемента
		return 1;
	if (((one_tree[num_prev]->getnum() <= one_tree[num_now]->getnum()) && (max_or_min == 2)) || ((one_tree[num_prev]->getnum() >= one_tree[num_now]->getnum()) && (max_or_min == 1)))
	{//"поднятие" элемента по алгоритму
		int k = one_tree[num_prev]->getnum();
		one_tree[num_prev]->set_int(one_tree[num_now]->getnum());
		one_tree[num_now]->set_int(k);
		num_now = num_prev;

		if (num_prev % 2)
		{
			num_prev = (num_prev - 1) / 2;//дедушка рассматриваемого элемента
			addition_rec(one_tree, num_prev, num_now, max_or_min);
		}
		else
		{
			num_prev = (num_prev - 2) / 2;//дедушка рассматриваемого элемента
			addition_rec(one_tree, num_prev, num_now, max_or_min);
		}
	}
	else 
		return 1;
	return 1;
}

void put_2_numbers_for_max_or_min(vector<one_yzel*>& one_tree, int x, int y, int max_or_min)//функция замены двух узлов (5 задача)
{
	int zapret_x = -1;//если икс еще не записали, то эта переменная равна -1
	int zapret_y = -1;//если игрек еще не записали, то эта переменная равна -1
	int prev;//отец рассматриваемого элемента
	for (unsigned int i = 0 ; i < one_tree.size() ; i++)
	{
		if (i == 0)
			prev = 0;
		else
		{
			if (i % 2)
				prev = (i - 1) / 2;
			else
				prev = (i - 2) / 2;
		}
		//для икса

		if ((max_or_min == 2) && ((one_tree[prev]->getnum() >= x) || ((prev == 0) && (one_tree[prev]->getnum() <= x))) && (zapret_x == -1))//для max кучи. икс
		{
			if ((2 * i + 1 >= one_tree.size()) || ((one_tree[2 * i + 1]->getnum() <= x) && (2 * i + 2 >= one_tree.size())) || ((one_tree[2 * i + 1]->getnum() <= x) && (one_tree[2 * i + 2]->getnum() <= x)))//левая не сущ, левая меньше и правая несущ, обе меньш
			{
				one_tree[i]->set_int(x);
				zapret_x = i;
				continue;
			}
		}
		if ((max_or_min == 1) && ((one_tree[prev]->getnum() <= x) || ((prev == 0) && (one_tree[prev]->getnum() >= x))) && (zapret_x == -1))//для min кучи. икс
		{
			if ((2 * i + 1 >= one_tree.size()) || ((one_tree[2 * i + 1]->getnum() >= x) && (2 * i + 2 >= one_tree.size())) || ((one_tree[2 * i + 1]->getnum() >= x) && (one_tree[2 * i + 2]->getnum() >= x)))//левая не сущ, левая меньше и правая несущ, обе меньш
			{
				one_tree[i]->set_int(x);
				zapret_x = i;
				continue;
			}
		}

		//max куча. игрек
		if ((max_or_min == 2) && ((one_tree[prev]->getnum() >= y) || ((prev == 0) && (one_tree[prev]->getnum() <= y))) && (zapret_y == -1))
		{
			if ((2 * i + 1 >= one_tree.size()) || ((one_tree[2 * i + 1]->getnum() <= y) && (2 * i + 2 >= one_tree.size())) || ((one_tree[2 * i + 1]->getnum() <= y) && (one_tree[2 * i + 2]->getnum() <= y)))//левая не сущ, левая меньше и правая несущ, обе меньш
			{
				one_tree[i]->set_int(y);
				zapret_y = i;
				continue;
			}
		}
		if ((max_or_min == 1) && ((one_tree[prev]->getnum() <= y) || ((prev == 0) && (one_tree[prev]->getnum() >= y))) && (zapret_y == -1))//min куча. игрек
		{
			if ((2 * i + 1 >= one_tree.size()) || ((one_tree[2 * i + 1]->getnum() >= y) && (2 * i + 2 >= one_tree.size())) || ((one_tree[2 * i + 1]->getnum() >= y) && (one_tree[2 * i + 2]->getnum() >= y)))//левая не сущ, левая меньше и правая несущ, обе меньш
			{
				one_tree[i]->set_int(y);
				zapret_y = i;
				continue;
			}
		}
	}
}

void generation_for_6task()
{
	string a, b;
	int count = 0;
	int n, max_or_min;
	do{
		cout << "(Задание 6)Введите количество элементов в новом массиве(  5 < n < 25  ):";
		cin >> a;
		n = proverka(a);
	}while((n <= 5) || (n >= 25));
	do{
		cout << "(внимание, после следующего ввода консоль будет очищена!)" << endl << "Введите 1 для формирования min кучи, 2 для max:";
		cin >> b;
		max_or_min = proverka(b);
	}while ((max_or_min != 1) && (max_or_min != 2));
	system("cls");

	task6 mass(n, max_or_min);//объявление элемента 6 - го задания. Формирование массива и его сортировка происходит прямо в конструкторе
	system("cls");
	cout << "Получившаяся куча:";
	mass.print(n);
}

bool sort_spisok(one_yzel* object, int max_or_min)//сортировка списка для задания 6А
{
	if (object->get_left_pointer() == nullptr)
		return false;
	if (((max_or_min == 1) && (object->getnum() > object->get_left_pointer()->getnum())) || ((max_or_min == 2) && (object->getnum() < object->get_left_pointer()->getnum())))
	{
		int k = object->getnum();
		object->set_int(object->get_left_pointer()->getnum());
		object->get_left_pointer()->set_int(k);
	}
	if (object->get_right_pointer() == nullptr)
		return false;
	if (((max_or_min == 1) && (object->getnum() > object->get_right_pointer()->getnum())) || ((max_or_min == 2) && (object->getnum() < object->get_right_pointer()->getnum())))
	{
		int k = object->getnum();
		object->set_int(object->get_right_pointer()->getnum());
		object->get_right_pointer()->set_int(k);
	}
	sort_spisok(object->get_left_pointer(), max_or_min);
	sort_spisok(object->get_right_pointer(), max_or_min);
	return false;
}

bool conv_mass_to_tree_for_6a (vector<int> vec, one_yzel* now, int k, unsigned int i)//конвертация массива в список для задания 6А
{
	if (i >= vec.size())
		return false;
	one_yzel* x = new one_yzel(k, nullptr, nullptr);//создаем новый элемент списка
	if (i % 2)
		now->set_left_pointer(x);//now - объект списка, в который мы заносим указатели его сыновей
	else
		now->set_right_pointer(x);
	unsigned int j =  2 * i + 1;//новый сын
	if (j < vec.size())
		k = vec[j];
	if (!conv_mass_to_tree_for_6a (vec, x, k, j))
	{
		unsigned int j = 2 * i + 2;
		if (j < vec.size())
			k = vec[j];
		if (!conv_mass_to_tree_for_6a (vec, x, k, j))
			return false;
	}
}

void generation_for_6atask()
{
	string a, b;
	int count = 0;//Отвечает за то, чтобы массив заполнился n различными числами
	bool flag;
	int n, max_or_min;
	do{
		cout << "(Задание 6а)Введите количество элементов в новом массиве(  5 < n < 25  ):";
		cin >> a;
		n = proverka(a);
	}while((n <= 5) || (n >= 25));
	do{
		cout << endl << "Введеите 1 для формирования min кучи, 2 для max:";
		cin >> b;
		max_or_min = proverka(b);
	}while ((max_or_min != 1) && (max_or_min != 2));

	vector<int> vec;
	while (count != n)//заполняем вектор случайными числами
	{
		flag = true;
		int x = rand() % 29 + 71;
		for (unsigned int i = 0 ; i < vec.size() ; i++)
			if (vec[i] == x)
				flag = false;
		if (flag)
		{
			vec.push_back(x);
			count++;
		}
	}

	int x = vec.size();
	count = 0;
	while (x > 0)//определяем уровень будущего дерева
	{
		x = x - pow(2, count);
		count++;
	}
	tree drevo;//создаем объект типа структуры
	drevo.level = count;//заносим туда описание дерева и корень дерева
	drevo.max_or_min = max_or_min;
	drevo.root = new one_yzel(vec[0], nullptr, nullptr);
	conv_mass_to_tree_for_6a (vec, drevo.root, vec[1], 1);//переносим массив в список (левая ветка)
	conv_mass_to_tree_for_6a (vec, drevo.root, vec[2], 2);//переносим массив в список (правая ветка)
	while (((max_or_min == 2) && (!max_heap(drevo.root))) || ((max_or_min == 1) && (!min_heap(drevo.root))))
		sort_spisok(drevo.root, max_or_min);//сортируем полученный список

	vector<one_yzel*> one_tree;
	one_tree.push_back(drevo.root);
	complete_tree(drevo.level, one_tree);//переводим список в массив, чтобы вывести на экран

	cout << "Вывести новое дерево - кучу (1 - пирамидой, 2 - стобиком:)";
	char q = _getch();
	cout << endl;
	if (q == '1')
		vivod_pyramid(one_tree, drevo.level);
	if (q == '2')
		vivod_stolbik(drevo.level, one_tree);
	if ((q != '1') && (q != '2'))
		cout << "Вы ввели иной символ" << endl;
	one_tree.erase(one_tree.begin(), one_tree.end());
	vec.erase(vec.begin(), vec.end());
}

int _tmain(int argc, _TCHAR* argv[])

{
	bool flag;
	setlocale (LC_ALL, "Russian");
	srand(time(NULL));
	vector<tree*> vec_of_roots;//вектор корней деревьев (всего будет 7 деревьев)

	for (int i = 0 ; i < N ; i++)//считываем 7 файлов (1 задача)
	{
		string name_of_file = data;
		name_of_file[8] = i + 1 + '0';//устанавливаем название файла
		ifstream ffstr(name_of_file);
		readcheck(ffstr, vec_of_roots, i);
		if (i == N - 1 )
			ffstr.close();
	}

	for (int i = 0 ; i < N ; i++)//(2 задача - проверка, является ли кучей)
	{
		vector<one_yzel*> one_tree;//вектор одного дерева, представляем дерево в виде массива (3 задача)
		one_tree.push_back(vec_of_roots[i]->root);//кладем первый элемент
		cout << endl;
		flag = false;
		if (complete_tree(vec_of_roots[i]->level, one_tree))//первая проверка (здесь же и 3 задача - представление кучи в виде массива)
		{
			if (max_heap(vec_of_roots[i]->root))//проверка на максимум
			{
				flag = true;
				vec_of_roots[i]->max_or_min = 2;
				cout << i + 1 << "-ое дерево: " << "MAX_heap" << endl;
			}
			if (min_heap(vec_of_roots[i]->root))//проверка на минимум
			{
				flag = true;
				vec_of_roots[i]->max_or_min = 1;
				cout << i + 1 << "-ое дерево :" << "MIN_heap" << endl;
			}
			if (!flag)
			{
				vec_of_roots[i]->max_or_min = 0;
				cout << i + 1 << "-ое дерево: " << "Not heap!" << endl;
			}
			if (flag)//3 - я задача: аккуратный вывод дерева
			{
				cout << "Выберите способ вывода (1 - пирамидой, 2 - стобиком:)";
				char a = _getch();
				cout << endl;

				if (a == '1')
					vivod_pyramid(one_tree, vec_of_roots[i]->level);
				if (a == '2')
					vivod_stolbik(vec_of_roots[i]->level, one_tree);
				if ((a != '1') && (a != '2'))
					cout << "Вы ввели иной символ" << endl;
			}	
		}
		else
			if (!flag)
			{
				vec_of_roots[i]->max_or_min = 0;
				cout << i + 1 << "-ое дерево: " << "Not heap!" << endl;
			}
			one_tree.erase(one_tree.begin(), one_tree.end());//очищаем вектор
	}

	string q = "";
	while (q != "q")
	{
		cout << endl << endl << endl << "Введите:" << endl << " 1 - для добавления нового узла" << endl << " 2 - для замены двух узлов" << endl << " q - для выхода" << endl << " 3 - для перехода к заданиям 6 и 6а" << endl;
		cin >> q;
		if (q == "1")
		{
			for (int i = 0 ; i < N ; i++)//4 - ая задача, добавление элемента
			{
				if (vec_of_roots[i]->max_or_min)//рассматриваем только кучи
				{
					int x;
					vector<one_yzel*> one_tree;
					do{
						cout << "Введите значение, которое хотите добавить в " << i + 1 << " дерево - кучу:";
						string a;
						cin >> a;
						x = proverka(a);
					}while(x == -1);
					one_tree.push_back(vec_of_roots[i]->root);//кладем первый элемент
					complete_tree(vec_of_roots[i]->level, one_tree);//формируем из списка массив, чтобы было удобнее работать
					one_yzel* k = new one_yzel(x, nullptr, nullptr);
					one_tree.push_back(k);
					int num_prev;//отец рассматриваемого элемента
					int num_now = one_tree.size() - 1;//начинаем с самого последнего элемента
					if (num_now % 2)
					{//создаем новый узел и кладем его в конец в зависимости от четности отца нового последнего
						num_prev = (num_now - 1) / 2;
						one_tree[num_prev]->set_left_pointer(one_tree[num_now]);
					}
					else
					{
						num_prev = (num_now - 2) / 2;
						one_tree[num_prev]->set_right_pointer(one_tree[num_now]);
					}
					addition_rec(one_tree, num_prev, num_now,vec_of_roots[i]->max_or_min);//сама функция добавления

					int q = 0;
					int c = one_tree.size();
					while (c > 0)//смотрим, каков стал новый уровень полученной кучи
					{
						c = c - pow (2.0 , q);
						q++;
					}
					if (c != vec_of_roots[i]->level)
						vec_of_roots[i]->level = q;

					cout << "Вывести новое дерево - кучу (1 - пирамидой, 2 - стобиком:)";
					char a = _getch();
					cout << endl;
					if (a == '1')
						vivod_pyramid(one_tree, vec_of_roots[i]->level);
					if (a == '2')
						vivod_stolbik(vec_of_roots[i]->level, one_tree);
					if ((a != '1') && (a != '2'))
						cout << "Вы ввели иной символ" << endl;

					one_tree.erase(one_tree.begin(), one_tree.end());//очищаем вектор
				}
				else
					continue;
			}
		}

		if (q == "2")
		{
			for (int i = 0 ; i < N ; i++)//задание 5 - замена двух элементов
			{
				if (vec_of_roots[i]->max_or_min)//рассматриваем только кучи
				{
					int x, y;
					vector<one_yzel*> one_tree;
					one_tree.push_back(vec_of_roots[i]->root);//кладем первый элемент
					complete_tree(vec_of_roots[i]->level, one_tree);//формируем из списка массив, чтобы было удобнее работать
					do{
						cout << "Введите два значения, которые заменят два узла " << i + 1 << " дерева - кучи: ";
						string a;
						cin >> a;
						x = proverka(a);
						cin >> a;
						y = proverka (a);
					}while((x == -1) || (y == -1));
					if (((vec_of_roots[i]->max_or_min == 2) && (x < y)) || ((vec_of_roots[i]->max_or_min == 1) && (x > y)))//меняем местами
					{
						int k = x;
						x = y;
						y = k;
					}
					put_2_numbers_for_max_or_min(one_tree, x, y, vec_of_roots[i]->max_or_min);//сама функция поиска мест для двух введенных значений и их записи	
					cout << "Вывести новое дерево - кучу (1 - пирамидой, 2 - стобиком:)";
					char a = _getch();
					cout << endl;
					if (a == '1')
						vivod_pyramid(one_tree, vec_of_roots[i]->level);
					if (a == '2')
						vivod_stolbik(vec_of_roots[i]->level, one_tree);
					if ((a != '1') && (a != '2'))
						cout << "Вы ввели иной символ" << endl;

					one_tree.erase(one_tree.begin(), one_tree.end());//очищаем вектор
				}
			}
		}
		if (q == "3")
		{
			generation_for_6task();//6 задание
			generation_for_6atask();//6а задание
		}
	}

	cout << "Thanks for using! Have a nice day!" << endl;
	for (unsigned int i = 0 ; i < vec_of_roots.size() ; i++)//удаляем динамически выделенные объекты класса
		delete vec_of_roots[i]->root;
	vec_of_roots.erase(vec_of_roots.begin(), vec_of_roots.end());//очищаем вектор
	return 1;
}