#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <Windows.h>
#include <initializer_list>
#include <iomanip>

using namespace std;

double step = 0.01;

auto F = [](double x) {
    return x * sin(x);
};

double integr(double a, double b) {
    double mul = 1;
    if (a > b) {
        swap(a, b);
        mul = -1;
    }
    double res = (F(a) + F(b)) / 2;
    for (double i = a; i < b; i += step)
        res += 2 * F(i + step / 2);
    for (double i = a + step; i < b; i += step)
        res += F(i);
    res *= step / 3;
    return res * mul;
}

void drawPlot(double a, double b) {
    int width = 1200, height = 700;
    double coef = .5 * height * (b - a) / width;

    HDC hDC = GetDC(GetConsoleWindow());
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(hDC, pen);
    MoveToEx(hDC, 0, height / 2, 0);
    LineTo(hDC, width, height / 2);
    if (a < 0 && b > 0) {
        MoveToEx(hDC, (-a / (b - a)) * width, 0, 0);
        LineTo(hDC, (-a / (b - a)) * width, height);
    }
    double I = 0;
    I = integr(0, a);
    for (double i = a + step; i < b; i += step) {
        MoveToEx(hDC, width * (i - step - a) / (b - a), (1 - I / coef) * height / 2, 0);
        I += integr(i - step, i);
        LineTo(hDC, width * (i - a) / (b - a), (1 - I / coef) * height / 2);//try to put 20 intead of coef
    }
}

int main() {
    //freopen("output.txt", "w", stdout);

    double a, b;
    cin >> a >> b;
    drawPlot(a, b);
    system("pause");
    return 0;
}