#include<iostream>
#include<graphics.h>
#include<conio.h>

using namespace std;

const double PI = 3.1415926535897;

int main11() {
	cout << "Hello world" << endl;

	int n = 3;
	double percent[3] = {0.2,0.3,0.5};
	COLOR16 color[3] = { RED,BLACK,GREEN };

	double startAngel = 0;
	double endAngel=0;

	initgraph(800, 800);
	setbkcolor(WHITE);
	cleardevice();

	for (int i = 0; i < n; i++) {
		startAngel = endAngel;
		endAngel = startAngel + 2.0 * PI * percent[i];

		//setlinecolor(color[i]);
		//pie(200, 200, 600, 600, startAngel, endAngel);

		setfillcolor(color[i]);
		fillpie(200, 200, 600, 600, startAngel, endAngel);
	}
	

	_getch();
	return 0;
}