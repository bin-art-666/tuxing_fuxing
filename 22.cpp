#include<iostream>
#include<conio.h>
#include<cmath>
#include<graphics.h>

using namespace std;

const double PI = 3.141592653589793;

struct Point2D {
	double x, y,z;
};

struct Matrix {
	double m[3][3];
};

Point2D zhuanhuan(Point2D p, Matrix m) {
	Point2D newp;

	newp.x = p.x * m.m[0][0] + p.y * m.m[1][0] + m.m[2][0];
	newp.y = p.x * m.m[0][1] + p.y * m.m[1][1] + m.m[2][1];
	newp.z = p.x * m.m[0][2] + p.y * m.m[1][2] + m.m[2][2];
	newp.z = 1;
	newp.x /= newp.z;
	newp.y /= newp.z;

	return newp;
}

Matrix juzhencheng(Matrix a, Matrix b) {
	Matrix c = { { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } } };
	for (int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				c.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return c;
}


int main22() {
	initgraph(800, 800);
	setbkcolor(WHITE);
	cleardevice();

	int n = 4;
	Point2D points[4] = { { 300,300,1},{ 300,500 ,1},{ 500,500 ,1},{ 500,300 ,1}};

	for (int i = 0; i < n-1; i++) {
		setlinecolor(BLACK);
		line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
	}
	line(points[n - 1].x, points[n - 1].y, points[0].x, points[0].y);

	Point2D newpoints[4];
	//先平移
	double yiX = -400;
	double yiY = -400;

	Matrix yiM = { { { 1,0,0 },{ 0,1,0 },{ yiX,yiY,1 } } };

	//再放大
	double bigX = 1.1;
	double bigY = 1.1;

	Matrix bigM = { { { bigX,0,0 },{ 0,bigY,0 },{ 0,0,1 } } };

	//旋转
	double angle = 15 * PI / 180;
	Matrix xuanM = { { { cos(angle),sin(angle),0 },{ -sin(angle),cos(angle), 0 },{ 0,0,1 } } };

	//沿着x错切
	double k = tan(angle);
	Matrix cuoM = { { { 1,1/k,0 },{ 1, 1, 0 },{0,0,1} } };
	
	//再平移
	Matrix yiM2 = { { { 1,0,0 },{ 0,1,0 },{ -yiX,-yiY,1 } } };

	Matrix zongM = juzhencheng(juzhencheng(yiM, cuoM), yiM2);
	//Matrix zongM = cuoM;

	for (int i = 0; i < n; ++i) {
		newpoints[i] = zhuanhuan(points[i], zongM);
	}

	//再一次打印
	for (int i = 0; i < n - 1; i++) {
		setlinecolor(RED);
		line(newpoints[i].x, newpoints[i].y, newpoints[i + 1].x, newpoints[i + 1].y);
	}
	line(newpoints[n - 1].x, newpoints[n - 1].y, newpoints[0].x, newpoints[0].y);


	_getch();

	return 0;


}