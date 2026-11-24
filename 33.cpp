
#include <iostream>
#include <graphics.h>
#include <conio.h>

using namespace std;

// 字符W的坐标点
struct Point {
    int x, y;
};

Point W[] = {
    { 0, 0 },
    { 10, 40 },
    { 20, 20 },
    { 30, 40 },
    { 40, 0 }
};

// 绘制字符
void drawText(int x, int y, Point p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        line(
            x + p[i].x, y + p[i].y,
            x + p[i + 1].x, y + p[i + 1].y
        );
    }
}

int main33() {
    initgraph(600, 400);

    setbkcolor(WHITE);
    cleardevice();
    setlinecolor(BLACK);

    // 绘制字母W
    drawText(200, 150, W, 5);

    _getch();
    closegraph();

    return 0;
}
