
#include <iostream>
#include <graphics.h>
#include <conio.h>

using namespace std;

// 8×8 字母 A 点阵
unsigned char font[8] = {
    0x18,
    0x24,
    0x42,
    0x42,
    0x7E,
    0x42,
    0x42,
    0x42
};

// 绘制点阵
void drawFont(int x, int y, int scale) {
    setfillcolor(BLACK);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            // 判断当前像素是否为1
            if (font[i] & (0x80 >> j)) {
                solidrectangle(
                    x + j * scale,
                    y + i * scale,
                    x + (j + 1) * scale - 1,
                    y + (i + 1) * scale - 1
                );
            }

        }
    }
}

int main3() {
    initgraph(400, 300);

    setbkcolor(WHITE);
    cleardevice();

    // 绘制放大5倍的字母A
    drawFont(120, 70, 20);

    _getch();

    closegraph();

    return 0;
}
