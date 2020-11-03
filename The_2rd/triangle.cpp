#include "triangle.h"


bool triangle::isinothertri(triangle tri, point otherp)
{
	vector<point> a,b;
	point tempa,tempb,tempc;
	tempa.x = tri.p1.x - otherp.x;
	tempa.y = tri.p1.y - otherp.y;
	tempb.x = tri.p2.x - otherp.x;
	tempb.y = tri.p2.y - otherp.y;
	tempc.x = tri.p3.x - otherp.x;
	tempc.y = tri.p3.y - otherp.y;
	double disa = sqrt(tempa.x * tempa.x + tempa.y * tempa.y);
	double disb = sqrt(tempa.x * tempa.x + tempb.y * tempb.y);
	double disc = sqrt(tempb.x * tempb.x + tempc.y * tempc.y);
	double theta1 = (tempa.x * tempb.x + tempa.y * tempb.y)
					/ (disa * disb);
	double theta2 = tempa.x * tempc.x + tempa.y * tempc.y
					/ (disa * disc);
	double theta3 = tempc.x * tempb.x + tempc.y * tempb.y
					/ (disb * disc);
	if (theta1 + theta2 + theta3 - 2 * pi <= 0.001) return true;
	else return false;
}



