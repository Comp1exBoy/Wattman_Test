#include "triangle.h"



int main()
{
	point tri1p1, tri1p2, tri1p3;
	point tri2p1, tri2p2, tri2p3;
	cin >> tri1p1.x >> tri1p1.y;
	cin >> tri1p2.x >> tri1p2.y;
	cin >> tri1p3.x >> tri1p3.y;
	cin >> tri2p1.x >> tri2p1.y;
	cin >> tri2p2.x >> tri2p2.y;
	cin >> tri2p3.x >> tri2p3.y;
	int flag = 0;
	triangle tri1(tri1p1, tri1p2, tri1p3);
	triangle tri2(tri2p1, tri2p2, tri2p3);
	if (tri1.isinothertri(tri1, tri2p1)) flag++;
	if (tri1.isinothertri(tri1, tri2p2)) flag++;
	if (tri1.isinothertri(tri1, tri2p3)) flag++;
	if (flag == 0) cout << "Not intersect" << endl;
	else if (flag == 3) cout << "Not intersect,but include" << endl;
	else cout << "inrersesct" << endl;


}