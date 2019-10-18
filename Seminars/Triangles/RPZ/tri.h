#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct point{
	int x;
	int y;
};

class Triangle{
public:
	vector <point> vect;
	string name_of_triangle;
	Triangle();
	Triangle(string, point, point, point);
	~Triangle();
	double square();
};