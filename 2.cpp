#include <graphics.h>
#include <cmath>

const double PI = 3.141592653589793;

struct Point {
    double x, y;
};

struct Matrix {
    double a[3][3];
};

Point p[5] = {
    { 0, 0 },{ 10, 30 },{ 20, 0 },
    { 5, 15 },{ 15, 15 }
};

Matrix multiply(Matrix A, Matrix B) {
    Matrix C = {};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                C.a[i][j] += A.a[i][k] * B.a[k][j];
    return C;
}

Point transform(Point p, Matrix M) {
    Point q;
    q.x = p.x * M.a[0][0] + p.y * M.a[1][0] + M.a[2][0];
    q.y = p.x * M.a[0][1] + p.y * M.a[1][1] + M.a[2][1];
    return q;
}

Matrix translate(double x, double y) {
    return { { { 1, 0, 0 },{ 0, 1, 0 },{ x, y, 1 } } };
}

Matrix scale(double x, double y) {
    return { { { x, 0, 0 },{ 0, y, 0 },{ 0, 0, 1 } } };
}

Matrix rotate(double angle) {
    double c = cos(angle * PI / 180);
    double s = sin(angle * PI / 180);
    return { { { c, s, 0 },{ -s, c, 0 },{ 0, 0, 1 } } };
}

Matrix shearX(double angle) {
    double k = tan(angle * PI / 180);
    return { { { 1, 0, 0 },{ k, 1, 0 },{ 0, 0, 1 } } };
}

void drawLine(Point a, Point b) {
    line(400 + (int)round(a.x * 3), 300 - (int)round(a.y * 3),
        400 + (int)round(b.x * 3), 300 - (int)round(b.y * 3));
}

void drawShape(Point p[]) {
    for (int i = 0; i < 3; i++)
        drawLine(p[i], p[(i + 1) % 3]);
    drawLine(p[3], p[4]);
}

void drawAxes() {
    setlinecolor(BLACK);
    line(20, 300, 780, 300);
    line(400, 20, 400, 580);
    outtextxy(770, 310, L"X");
    outtextxy(410, 20, L"Y");
    outtextxy(380, 310, L"O");
}

int main2() {
    initgraph(800, 600);
    setbkcolor(WHITE);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, L"Consolas");

    Matrix M[6];
    M[0] = translate(52, 60);
    M[1] = rotate(75);
    M[2] = scale(2, 2);
    M[3] = scale(0.5, 0.5);
    M[4] = shearX(15);
    M[5] = multiply(multiply(translate(-10, -15), rotate(90)),
        translate(10, 15));

    const wchar_t* title[6] = {
        L"Translation (52,60)", L"Rotation 75",
        L"Scale 2.0", L"Scale 0.5", L"ShearX 15",
        L"Rotation around (10,15)"
    };

    Point q[5];
    int i = 0;
    bool running = true;

    while (running) {
        cleardevice();
        drawAxes();
        outtextxy(20, 20, title[i]);

        setlinecolor(BLACK);
        drawShape(p);

        for (int j = 0; j < 5; j++)
            q[j] = transform(p[j], M[i]);

        setlinecolor(RED);
        drawShape(q);

        setlinecolor(BLACK);
        rectangle(650, 530, 770, 570);
        outtextxy(685, 540, L"Next");

        while (true) {
            ExMessage msg = getmessage(EM_MOUSE | EM_KEY);
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
                running = false;
                break;
            }
            if (msg.message == WM_LBUTTONDOWN &&
                msg.x >= 650 && msg.x <= 770 &&
                msg.y >= 530 && msg.y <= 570) {
                i = (i + 1) % 6;
                break;
            }
        }
    }

    closegraph();
    return 0;
}
