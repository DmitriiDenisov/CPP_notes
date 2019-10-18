// ------------------------------------------------------------	
// Программа считывает из файла имена и фамилии учеников, а также их оценки, после чего
// выводит информацию об их успеваемости.
// Также программа имитирует пересдачу, а также подсчитывает успеваемость 
// студентов после пересдач. Прим. Система оценивания - 10-ти бальная (оценки 0 быть не может)
// Среда разработки: Microsoft Visual C++ 2010 Express			
// Версия программы: 2.2  |  Автор: Денисов Д.М.,ПМИ,172			
// Дата последнего изменения: 09.02.2013 

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

struct vedomost
{
	string name;//имя+фамилия студента
	double grade;//ср,оценка
	unsigned int fail;//кол-во хвостов
	double grade_without_otr;//средняя оценку после сессии (без неудв. оценками),разделенная на 10
};

double srednee(vector<char> marks,int N)//вычисляет среднюю оценку после сессии (вместе с неудв. оценками)
{
	double summ = 0;
	double sred;
	int dlina = marks.size();

	for (int i = 0 ; i < dlina ; i++)
	{
		switch (marks[i]){
		case ';': break;
		case '0': summ = summ + 9;
			break;
		default: summ = summ + marks[i] - '0';
			break;
		}
	}

	sred = summ / N;
	return sred;
}

double srednee_bez_otr(vector<char> marks, int N)//вычисляет среднюю оценку после сессии (без неудв. оценками) и делит рез-т на 10
{
	double sred1 = 0;
	int dlina = marks.size();

	for (int i = 0 ; i < dlina ; i++)
	{
		switch (marks[i])
		{
		case '1': if ((i != dlina - 1) && (marks[ i + 1 ] == '0'))
					  sred1 = sred1 + 10;
			break;
		case '2':
		case '3':
		case ';': break;
		default:  sred1 = sred1 + marks[i] - '0';
			break;
		}
	}

	sred1 = sred1 / N;
	return sred1;
}

int nezachi (vector<char> marks)//вычисляет количество незачей у одного студента
{
	int dlina = marks.size();
	int num = 0;

	for (int i = 0 ; i < dlina ; i++)
	{
		switch (marks[i]){
		case '2':
		case '3': num++;
			break;
		case '1': if ((i == dlina-1) || (marks[i+1] != '0'))
					  num++;
			break;
		}
	}

	return num;
}

void inout_put(vedomost *y, int i, string s, int N)//функция, считывающая данные
{
	vector<char> marks;
	int dlina = s.length();

	if (i % 2 == 0)//если имя и фамилия
	{	
		y[i/2].name = s;//заносим имя студента в массив
		cout<<y[i/2].name<<endl;
	}
	else//если оценки
	{
		marks.erase(marks.begin(), marks.end());//удаляем в векторе предыдущие значения (оценки предыдущего ученика)

		for (int j = 0 ; j < dlina ; j++)
			marks.push_back(s[j]);//записываем в вектор оценки ученика

		y[i/2].grade_without_otr = srednee_bez_otr (marks, N);
		y[i/2].grade = srednee (marks, N);
		cout<<"Средняя оценка:"<<fixed<<setprecision(2)<<y[i/2].grade<<endl;
		y[i/2].fail = nezachi (marks);
		cout<<"Количество незачетов:"<<y[i/2].fail<<endl;
		if (nezachi (marks) >= 3)
			cout<<"На отчисление!"<<endl;
	}

}

void gen_peres(vector<char>& resul_peres, int fail)//генерирует оценки пересдавших
{
	int k;

	for (int i = 0; i < fail; i++)//fail-кол-во несданных экзов
	{
		k= 1 + rand() % 8;
		resul_peres.push_back ( k + '0');
	}

}

int summa_peres (vector<char> marks)//вычисляет сумму оценок, полученных на пересдаче
{
	int sigma = 0;
	int dlina = marks.size();

	for (int i = 0 ; i < dlina ; i++)
		sigma = sigma + marks[i] - '0';

	return sigma;
}

int main(int argc, const char * argv[])
{
	const int kol_marks = 7, kol_of_stud = 10, N = 10;//N-кол-во оценок
	string name_or_ocenki;//промежуточная переменная хранения оценок
	int flag = 0;//"пееременная оформления"
	vector<char> marks;
	setlocale(LC_ALL,"Russian");
	srand(time(NULL));	
	vedomost *student;
	student = new vedomost[N];

	ifstream file("Students.txt");
	if (!file)
	{
		cout<<"Файл не найден, какая жалость..."; 
		return 1;
	}

	for (int i = 0; i < 20; i++)
	{
		getline(file, name_or_ocenki, '\n');
		inout_put(student, i, name_or_ocenki, N);
		flag++;
		if (flag % 2 == 0)
			cout<<endl;
	}

	//cout<<"ВНИМАНИЕ!! ПРоверка!";
	//for (int i=0; i<kol_of_stud; i++)
	//{
	//	cout<<"i="<<i<<"; Name:"<<student[i].name<<"; grade="<<student[i].grade<<"; fail="<<student[i].fail<<endl<<"Среднее, без учета плохих:"<<fixed<<setprecision(2)<<student[i].grade_without_otr<<endl;
	//}


	cout<<endl<<"Пересдача. Информация о пересдающих студентах:"<<endl<<endl;

	for (int i = 0 ; i < kol_of_stud ; i++)
	{
		if ((student[i].fail != 0) && (student[i].fail < 3))
		{
			vector<char> res_peres;//вектор результатов пересдачи
			gen_peres(res_peres, student[i].fail);//генерируем оценки пересдачи	
			cout<<student[i].name<<endl<<"Оценки пересдачи:";
			for (unsigned int j = 0 ; j < student[i].fail ; j++)
				cout<<res_peres[j]<<" " ;
			cout<<endl<<"Средняя оценка за пересдачу:"<<fixed<<setprecision(2)<<srednee (res_peres, student[i].fail)<<endl;
			cout<<"Новая средняя оценка:"<<(summa_peres(res_peres) / 10.0 + student[i].grade_without_otr)<<endl;
			cout<<"Количество незачей:"<<nezachi(res_peres)<<endl;
			if (nezachi(res_peres) != 0)
				cout<<"На отчислениe!"<<endl;
			cout<<endl;
		}
	}
	return 0;
}