#include <iostream>
#include <algorithm>
#include <Windows.h>

using namespace std;

auto func = [](double x) { return x * x + 4 * sin(x); };
auto deriv = [](double x) {    return 2 * x + 4 * cos(x); };
auto deriv2 = [](double x) { return 2 - 4 * sin(x); };

bool test(double a, double b, double x0, double q) {
    return q < 1 && func(a) * func(b) <= 0 && 
        func(x0) * deriv2(x0) > 0 && 
        x0 >= a && x0 <= b;
}

int n0(double eps, double q, double delta) {
    return 1 + int(log2(log(delta / eps) / log(1 / q) + 1));
}

double newton(double x0, double eps, bool is_modif, int &N) {
    double deriv_x0 = deriv(x0);
    for (;;) {
        ++N;
        double x1 = x0 - func(x0) / (is_modif || N == 1 ? deriv_x0 : deriv(x0));
        swap(x0, x1);
        if (fabs(x0 - x1) < eps / 2)
            break;
    }
    return x0;
}

double ff(double a, double b, double F(double), bool maxx) {
    double res = fabs(F(a));
    while (a < b) {
        res = maxx ? max(res, fabs(F(a))) : min(res, fabs(F(a)));
        a += 0.0001;
    }
    return res;
}

void precalc(double &delta, double &q, double a, double b, double x0) {
    delta = max(fabs(x0 - a), fabs(b - x0));
    double M2 = max(fabs(deriv2(a)), fabs(deriv2(b))), m1 = min(fabs(deriv(a)), fabs(deriv(b)));
    //double M2 = ff(a, b, deriv2, 1), m1 = ff(a, b, deriv, 0);
    q = (M2 * delta) / (2 * m1);
}

void run(double x0, double eps, double a, double b, bool fl) {
    if (a > b) swap(a, b);
    int N = 0;
    double delta, q;
    precalc(delta, q, a, b, x0);
    if (test(a, b, x0, q) == false) {
        cout << "Incorrect data!\n";
        return;
    }
    double x_res = newton(x0, eps, fl, N);
    printf("x* = %.10lf, F(x*) = %.3lf\n", x_res, func(x_res));
    printf("N = %d, n0(eps) = %d\n", N, n0(eps, q, delta));
}

void drawPlot(double F(double), double a, double b, int n) {
    a = -10; b = 10;
    int width = 200, height = 200;
    double start_y = n * height;
    a = -max(fabs(a), fabs(b)); b = -a;
    HDC hDC = GetDC(GetConsoleWindow());
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(hDC, pen);
    MoveToEx(hDC, 0, height / 2 + start_y, 0);
    LineTo(hDC, width, height / 2 + start_y);
    MoveToEx(hDC, width / 2, start_y, 0);
    LineTo(hDC, width / 2, height + start_y);
    double step = 0.01;
    for (double i = a + step; i < b; i += step) {
        MoveToEx(hDC, width * (i - a - step) / (b - a), min(max(0, height / 2 - F(i - step) * 10), height) + start_y, 0);
        LineTo(hDC, width * (i - a) / (b - a), min(max(0, height / 2 - F(i) * 10), height) + start_y);
        if (fabs(i - int(i)) < step) {
            MoveToEx(hDC, width * (i - a) / (b - a), height / 2 - 2 + start_y, 0);
            LineTo(hDC, width * (i - a) / (b - a), height / 2 + 2 + start_y);
            MoveToEx(hDC, width / 2 - 2, height * (i - a) / (b - a) + start_y, 0);
            LineTo(hDC, width / 2 + 2, height * (i - a) / (b - a) + start_y);
        }
    }
    MoveToEx(hDC, 0, start_y, 0);
    LineTo(hDC, width, start_y);
    LineTo(hDC, width, height + start_y);
    LineTo(hDC, 0, height + start_y);
    for (int i = 0; i < (height) / 12; ++i) cout << endl;
}

int main() {
    double x0, a, b, eps;
    cin >> a >> b >> x0 >> eps;

    drawPlot(func, a, b, 0);
    drawPlot(deriv, a, b, 1);
    drawPlot(deriv2, a, b, 2);

    run(x0, eps, a, b, false);
    run(x0, eps, a, b, true);
    system("pause");
    return 0;
}