#include "stdafx.h"
#include <cmath>
#include <string>
#include "tri.h"


Triangle::Triangle (){
	name_of_triangle = "default";
	point object;
	object.x = 0;
	object.y = 3;
	vect.push_back(object);
	object.x = 4;
	object.y = 0;
	vect.push_back(object);
	object.x = 0;
	object.y = 0;
	vect.push_back(object);
};

Triangle::Triangle (string name, point abc1, point abc2, point abc3)
{
	name_of_triangle = name;
	vect.push_back(abc1);
	vect.push_back(abc2);
	vect.push_back(abc3);
}

double Triangle::square()
{
	double length1 = sqrt(pow((vect[0].x - vect[1].x), 2) + pow((vect[0].y - vect[1].y), 2));
	double length2 = sqrt(pow((vect[0].x - vect[2].x), 2) + pow((vect[0].y - vect[2].y), 2));
	double length3 = sqrt(pow((vect[1].x - vect[2].x), 2) + pow((vect[1].y - vect[2].y), 2));
	double p = (length1 + length2 + length3) / 2;
	double S = sqrt (p * (p - length1) * (p - length2) * (p - length3));
	return S;
}
