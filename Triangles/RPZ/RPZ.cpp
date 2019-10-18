// RPZ.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "tri.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

const int N = 10;

int _tmain(int argc, _TCHAR* argv[])
{
	srand (time(NULL));
	system("cls"); 
	//Triangle* proverka = new Triangle();
	//cout << "Square:" << proverka->square() << endl;

	vector <Triangle*> vec;
	for (int i = 0 ; i < N ; i++)
	{
		bool flag = true;
		point abc1;
		point abc2;
		point abc3;
		while (flag)//генерация трех точек
		{
			abc1.x = rand() % 300;
			abc1.y = rand() % 300;
			abc2.x = rand() % 300;
			abc2.y = rand() % 300;
			abc3.x = rand() % 300;
			abc3.y = rand() % 300;
			double length1 = sqrt(pow((abc1.x - abc2.x), 2) + pow((abc1.y - abc2.y), 2));
			double length2 = sqrt(pow((abc1.x - abc3.x), 2) + pow((abc1.y - abc3.y), 2));
			double length3 = sqrt(pow((abc2.x - abc3.x), 2) + pow((abc2.y - abc3.y), 2));
			if ((length1 == length2 + length3) || (length2 == length1 + length3) || (length3 == length1 + length2))
				flag = true;
			else
				flag = false;
		}
		cout << "Insert name or your triangle:";
		string name;
		cin >> name;
		Triangle* object = new Triangle (name, abc1, abc2, abc3);
		vec.push_back(object);
		cout << "Square of " << i + 1 << "-th is:" << vec[i]->square() << endl;
	}

	cout << endl << endl << "Results after sorting:";
	for (int i = 0 ; i < N ; i++)
		for (int j = i + 1 ; j < N ; j++)
			if (vec[i]->square() < vec[j]->square())
			{
				Triangle* y = vec[i];
				vec[i] = vec[j];
				vec[j] = y;
			}
	for (int i = 0 ; i < N ; i++)
		cout << endl << vec[i]->name_of_triangle << " " << vec[i]->square();

	Triangle* max = new Triangle("maxTriangle", vec[0]->vect[0], vec[0]->vect[1], vec[0]->vect[2]);
	cout << endl << endl << "Max Triangle: " << vec[0]->name_of_triangle << ":" << vec[0]->square() << endl << "Copied triangle:  " << max->name_of_triangle << ":" << max->square() << endl;
	return 0;
}