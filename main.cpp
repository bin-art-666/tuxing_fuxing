#include <iostream>
#include <windows.h>
#include <imm.h>
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <cmath>

#pragma comment(lib, "imm32.lib")

using namespace std;

// 二维点
struct pp {
    int x, y;
};

// 边结构
struct Edge {
    int ymax;
    double x;
    double dx;
};

// 多边形顶点
pp p[6] = {
    { 3,18 },{ 13,14 },{ 25,22 },
    { 25,11 },{ 13,2 },{ 3,6 }
};

int ox = 100;
int oy = 600;
int k = 20;

// 数学坐标转换为屏幕坐标
int sx(int x) {
    return ox + x * k;
}

int sy(int y) {
    return oy - y * k;
}

// 绘制坐标系和多边形
void draw() {
    setbkcolor(WHITE);
    cleardevice();

    setlinecolor(BLACK);

    // 坐标轴
    line(ox, oy, 750, oy);
    line(ox, oy, ox, 100);

    // X轴刻度
    settextcolor(BLACK);
    settextstyle(15, 0, L"Consolas");

    for (int i = 0; i <= 30; i += 2) {
        line(sx(i), oy - 4, sx(i), oy + 4);

        wchar_t s[10];
        swprintf_s(s, L"%d", i);
        outtextxy(sx(i) - 8, oy + 10, s);
    }

    // Y轴刻度
    for (int i = 2; i <= 24; i += 2) {
        line(ox - 4, sy(i), ox + 4, sy(i));

        wchar_t s[10];
        swprintf_s(s, L"%d", i);
        outtextxy(ox - 30, sy(i) - 8, s);
    }

    // 绘制多边形
    for (int i = 0; i < 6; i++) {
        int j = (i + 1) % 6;

        line(
            sx(p[i].x), sy(p[i].y),
            sx(p[j].x), sy(p[j].y)
        );
    }

    // 操作提示
    outtextxy(100, 35,
        L"1: Seed Fill    2: Scanline Fill    R: Reset    ESC: Exit");
}

// 种子填充算法
void seedFill() {
    vector<pp> a;

    pp seed;
    seed.x = sx(13);
    seed.y = sy(10);

    a.push_back(seed);

    while (!a.empty()) {
        pp t = a.back();
        a.pop_back();

        // 判断是否越界
        if (t.x < 0 || t.x >= 800 ||
            t.y < 0 || t.y >= 680) {
            continue;
        }

        // 判断像素颜色
        if (getpixel(t.x, t.y) != WHITE) {
            continue;
        }

        // 填充当前像素
        putpixel(t.x, t.y, RGB(255, 150, 60));

        // 向四个方向扩展
        pp q;

        q.x = t.x + 1;
        q.y = t.y;
        a.push_back(q);

        q.x = t.x - 1;
        q.y = t.y;
        a.push_back(q);

        q.x = t.x;
        q.y = t.y + 1;
        a.push_back(q);

        q.x = t.x;
        q.y = t.y - 1;
        a.push_back(q);
    }
}

// 扫描线填充算法
void scanlineFill() {

    // 建立边表
    vector<Edge> ET[500];

    for (int i = 0; i < 6; i++) {

        pp a = p[i];
        pp b = p[(i + 1) % 6];

        // 忽略水平边
        if (a.y == b.y) {
            continue;
        }

        // 保证 a 是较低端点
        if (a.y > b.y) {
            pp t = a;
            a = b;
            b = t;
        }

        // 计算斜率倒数
        double dx = double(b.x - a.x) / (b.y - a.y);

        Edge e;
        e.ymax = b.y * k;
        e.x = a.x * k + dx * 0.5;
        e.dx = dx;

        int low = a.y * k;

        // 插入边表
        ET[low].push_back(e);
    }

    // 建立活动边表
    vector<Edge> AET;

    // 从最低扫描线开始
    for (int y = 2 * k; y < 22 * k; y++) {

        // 1. 删除已经失效的边
        for (int i = 0; i < (int)AET.size();) {
            if (AET[i].ymax <= y) {
                AET.erase(AET.begin() + i);
            }
            else {
                i++;
            }
        }

        // 2. 将新边加入活动边表
        for (int i = 0; i < (int)ET[y].size(); i++) {
            AET.push_back(ET[y][i]);
        }

        // 3. 按照交点 X 坐标排序
        for (int i = 0; i < (int)AET.size(); i++) {
            for (int j = i + 1; j < (int)AET.size(); j++) {

                if (AET[i].x > AET[j].x) {
                    Edge t = AET[i];
                    AET[i] = AET[j];
                    AET[j] = t;
                }
            }
        }

        // 4. 两两配对，绘制扫描线
        setlinecolor(BLUE);

        for (int i = 0; i + 1 < (int)AET.size(); i += 2) {

            int x1 = (int)ceil(AET[i].x - 0.5);
            int x2 = (int)floor(AET[i + 1].x - 0.5);

            if (x1 <= x2) {
                line(
                    ox + x1,
                    oy - y - 1,
                    ox + x2,
                    oy - y - 1
                );
            }
        }

        // 5. 更新交点 X 坐标
        for (int i = 0; i < (int)AET.size(); i++) {
            AET[i].x = AET[i].x + AET[i].dx;
        }
    }
}

// 主函数
int main() {

    // 图形窗口只处理快捷键，避免输入法拦截按键。
    ImmDisableIME(static_cast<DWORD>(-1));
    initgraph(800, 680);

    draw();

    while (true) {

        ExMessage m = getmessage(EX_KEY);

        if (m.message != WM_KEYDOWN) {
            continue;
        }

        // 退出
        if (m.vkcode == VK_ESCAPE) {
            break;
        }

        // 恢复原图
        if (m.vkcode == 'R' || m.vkcode == 'r') {
            draw();
        }

        // 种子填充
        if (m.vkcode == '1') {
            draw();
            seedFill();
        }

        // 扫描线填充
        if (m.vkcode == '2') {
            draw();
            scanlineFill();

            // 重新绘制边界
            setlinecolor(BLACK);

            for (int i = 0; i < 6; i++) {
                int j = (i + 1) % 6;

                line(
                    sx(p[i].x), sy(p[i].y),
                    sx(p[j].x), sy(p[j].y)
                );
            }
        }
    }

    closegraph();

    return 0;
}
