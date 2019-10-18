// ------------------------------------------------------------------------------------------	
// Программа для обработки данных успеваемости студентов. Программа считывает			       |
// информацию из файла, выводит полную информацию об успеваемости всех студентов, а также,     |
// по желанию пользователя, информацию о конкретном факультете.                                |
// Среда разработки: Microsoft Visual C++ 2012 Express										   |
// Версия программы: 2.2  |  Автор: Денисов Д.М.,ПМИ,172									   |
// Дата последнего изменения: 31.02.2014													   |
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

const int lenname = 30;
const int lenex = 8;
const int numarr = 20;

struct TestA{
	char faculty[lenname];//название факультета
	int examn[lenex];//положительные оценки ученика (одной записи)
	char * letters;//оценки ученика в системе A - B - C
};

int readcheck(ifstream & stream, vector <TestA> &vect)
{
	TestA object;//объект типа структуры (далее просто - объект)
	int count = 0;
	char mass[lenname];//промежуточный массив чаров
	ifstream data;

	if (!stream)
	{
		cout<<"Файл не найден, какая жалость..."<<endl;
		vect.erase(vect.begin(), vect.end());
		exit(1);
	}
	else
	{
		cout<<"Входной файл прочитан и данные размещены в векторе"<<endl<<endl;
		while (stream.getline (mass, lenname, '\n'))
		{
			for (int i = 0 ; i < lenex ; i++)//зануляем массив оценок объекта
				object.examn[i] = 0;

			if (mass[0] == 'F')//если факультет (его название)
			{
				for(int i = 0 ; i < lenname ; i++)
					object.faculty[i] = mass[i];//записываем название фак-те в объект
			}
			else//если оценки
			{
				int j = 0;
				for (int i = 0 ; i < lenname ; i++)
				{
					if ((mass[i] == '1') || (mass[i] == '2') || (mass[i] == '3'))
						count++;//кол-во незачей
					if((mass[i] - '0' < 10) && (mass[i] - '0' > 3))//если зачетная оченка => записываем в объект
					{
						object.examn[j] = mass[i] - '0';
						j++;
					}
				}
				object.examn[j] = 0;//ноль в конце массива оценок
				vect.push_back(object);//добавляем объект в вектор
			}
		}

		cout<<"Число элементов вектора равняется "<<vect.size()<<endl;
		for (int j = 0 ; j < numarr - 1 ; j++)
		{
			cout<<"запись #"<<j + 1<<":"<<"   средняя оценка:";
			int i = 0, sum = 0;
			while (vect[j].examn[i] != 0)
			{
				sum = sum + vect[j].examn[i];//находим сумму одного студента (одной записи)
				i++;
			}
			double x = sum / ((double)i);//ср.арифм. одной записи
			cout<<fixed<<setprecision(2)<<x<<endl;
		}
	}
	return count;
}

void makelett(vector<TestA> &vect, int *mass)
{
	int count;
	for (int i = 0 ; i < numarr - 1 ; i++)
	{
		count = 0;
		while (vect[i].examn[count] != 0)//считаем кол-во положит. оценок
			count++;
		mass[i] = count;

		vect[i].letters = new char [lenex];
		for (int j = 0 ; j < count ; j++)
			switch (vect[i].examn[j]){
			case 9:
			case 8:vect[i].letters[j] = 'A';//"буквенную" систему записываем в специальный массив
				break;

			case 7:
			case 6:vect[i].letters[j] = 'B';
				break;

			case 5:
			case 4:vect[i].letters[j] = 'C';
				break;
		}
		vect[i].letters[count] = '\0';//записываем терминальный ноль в конце
	}

	for (int i = 0 ; i < numarr - 1 ; i++)
	{
		cout<<"запись #"<<i + 1<<": letters ---> ";
		int j = 0;
		while (vect[i].letters[j] != '\0')
		{
			cout<<vect[i].letters[j]<<" ";
			j++;
		}
		cout<<"    >число оценок = "<<mass[i]<<endl;
	}
}

void grfacul(vector<TestA> &vect, int *mass)
{
	bool flag=false;
	int sum = 0, max = -1, max_num;
	string faculty_string, name;
	cout<<"Введите название факультета: Faculty ";
	cin>>name;
	faculty_string = "Faculty " + name;

	for (int i = 0 ; i < numarr - 1 ; i++)
	{
		if (vect[i].faculty != faculty_string)
			continue;
		else
		{
			flag = true;
			int j = 0, num = 0;
			while (vect[i].letters[j] != '\0')
			{
				if (vect[i].letters[j] == 'A')
					num++;
				j++;
			}
			if (max < num)//ищем макс. кколичество оценок А у заданного факультета
			{
				max = num;
				max_num = i;
			}
		}
	}

	for (int i = 0 ; i < numarr - 1 ; i++)//ищем общее кол-во положительных оценок
	{
		if (vect[i].faculty != faculty_string)
			continue;
		else
		{
			sum = sum + mass[i];
		}
	}

	if (flag == false)
		cout<<"Не найден факультет с таким названием"<<endl;
	else
	{
		cout<<"Результат поиска:"<<endl<<endl;
		cout<<"студент (запись #"<<max_num + 1<<") имеет"<<endl<<"максимальное число 'A' ("<<max<<")"<<endl;
		cout<<"число сданных экзаменов всеми студентами 'Faculty "<<name<<"' равно "<<sum<<endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<TestA> vec1;
	int massGrades[numarr];
	const char* data = "test.txt";
	setlocale(LC_ALL,"Russian");
	string edinorog;

	do{
		ifstream ffstr(data);
		cout<<"Общее число несданных экзаменов равняется "<<readcheck(ffstr, vec1)<<endl;
		ffstr.close();
		cout<<"[x] Входной текстовый файл закрыт (операция чтения завершена)."<<endl<<endl;
		makelett(vec1, massGrades);
		grfacul(vec1, massGrades);
		cout<<"Для выхода введите q, для продолжения любой иной символ:";
		cin>>edinorog;
		vec1.erase(vec1.begin(), vec1.end());//очищаем вектор, иначе он будет каждый раз забиваться одними и теми же данными
	}while (edinorog != "q");

	for (unsigned int i = 0 ; i < vec1.size() ; i++)//освобождаем дин. память
		delete [] vec1[i].letters;
	return 0;
}