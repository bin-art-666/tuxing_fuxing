#include <graphics.h>
#include <conio.h>

int main1()
{
    initgraph(800, 600);

    setbkcolor(WHITE);
    cleardevice();

    int cx = 300, cy = 300, r = 180;

    double percent[6] = { 0.5, 0.2, 0.1, 0.05, 0.1, 0.05 };

    COLORREF colors[6] = {
        RGB(255, 182, 193),
        RGB(173, 216, 230),
        RGB(144, 238, 144),
        RGB(255, 255, 153),
        RGB(221, 160, 221),
        RGB(255, 204, 153)
    };

    double startAngle = 0;

    for (int i = 0; i < 6; i++)
    {
        double endAngle = startAngle + percent[i] * 2 * 3.1415926;

        setfillcolor(colors[i]);
        setlinecolor(BLACK);

        fillpie(cx - r, cy - r, cx + r, cy + r, startAngle, endAngle);

        startAngle = endAngle;
    }

    _getch();
    closegraph();

    return 0;
}