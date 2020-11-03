#pragma once
#pragma once

#ifndef __TRIANGLE_H__
#define __TRIANGEL_H__


#include "iostream"
#include "algorithm"
#include "cmath"
#include "vector"
const double pi = 3.1415;
using namespace std;
struct point
	{
		double x;
		double y;
	};


class triangle
{
public:
	point p1, p2, p3;
	triangle(point p_1, point p_2, point p_3) :p1(p_1), p2(p_2), p3(p_3) {}
	bool isinothertri(triangle tri,point otherp);
};

#endif
