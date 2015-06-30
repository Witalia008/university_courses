#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <Windows.h>
#include <initializer_list>
#include <iomanip>
#include <valarray>

using namespace std;

typedef valarray<double> args;

typedef double (*functype)(args);

class EqSystem {
protected:
    vector<pair<functype, functype>> syst;
public:
    EqSystem(initializer_list<pair<functype, functype>> lst) : syst(lst) {}
    args process(args a) {
        args res(a.size());
        for (int i = 0; i < res.size(); ++i)
            res[i] = (syst[i].second)(a);
        return res;
    }
    double get(int idx, args a) {
        return (syst[idx].first)(a);
    }
    args get(args a) {
        args res(a.size());
        for (int i = 0; i < res.size(); ++i)
            res[i] = (syst[i].first)(a);
        return res;
    }
};

double step = 0.01;

auto sqr = [](double x) {
    return x * x;
};

auto Abs = [](double x) {
    return x < 0 ? -x : x;
};

double norm(args a) {
    double res = 0;
    for (auto i : a)
        res += abs(i);
    return res;
}

double eps = 1e-7;

args approx(args a0, EqSystem st) {
    for (;;) {
        args cur = st.process(a0);
        if (norm(a0 - cur) < eps)
            return cur;
        a0 = cur;
    }
}

void output(args res) {
    for (auto i : res)
        cout << i << " ";
    cout << endl;
}


auto F0 = [](args a) { return sqr(a[0]) / 4 + sqr(a[1]) + sqr(a[2]) / 9 - 1; };
auto F1 = [](args a) { return sqr(a[0]) + sqr(a[1]) / 9 + sqr(a[2]) / 4 - 1; };

auto phi0 = [](args a) { return 2 * sqrt(1 - sqr(a[2]) / 9 - sqr(a[1])); };
auto phi1 = [](args a) { return 3 * sqrt(1 - sqr(a[2]) / 4 - sqr(a[0])); };
auto phi2 = [](args a) { return a[2]; };

double c = 0.3;
auto X = [](double z0) { return sqrt((1 - sqr(z0) / 4) / (1 + 9 / sqr(c))); };
auto Y = [](double z0) { return sqrt((1 - sqr(z0) / 9) / (1 + 4 / sqr(c))); };

int main() {
    //freopen("output.txt", "w", stdout);

    /*EqSystem st = {
        { [](args a) { return 5 * a[0] - 6 * a[1] + 20 * log(a[0]) + 16; }, [](args a) { return exp((6 * a[1] - 6 * a[0] - 16) / 20); } },
        { [](args a) { return 2 * a[0] + a[1] - 10 * log(a[1]) - 4; }, [](args a) { return exp((2 * a[0] + a[1] - 4) / 10); } }
    };

    args res = approx({ 1.25, 0 }, st);
    output(res);
    output(st.get(res));*/

    /*EqSystem st = {
        { [](args a) { return 3 * sqr(a[0]) + 1.5 * sqr(a[1]) + sqr(a[2]) - 5; }, [](args a) { return sqrt(5 - 1.5 * sqr(a[1]) - sqr(a[2])) / 3; } },
        { [](args a) { return 6 * a[0] * a[1] * a[2] - a[0] + 5 * a[1] + 3 * a[2]; }, [](args a) { return (6 * a[0] * a[1] * a[2] - a[0] + 3 * a[2]) / (-5); } },
        { [](args a) { return 6 * a[0] * a[2] - a[1] * a[2] - 1; }, [](args a) { return (a[1] * a[2] + 1) / (6 * a[0]); } }
    };

    args res = approx({1.25, 0, 0.25}, st);
    output(res);
    output(st.get(res));*/

    /*EqSystem st = {
        { [](args a) { return 2 * sqr(a[0]) - a[0] * a[1] - 5 * a[0] + 1; }, [](args a) { return sqrt((a[0] * (a[1] + 5) - 1) / 2); } },
        { [](args a) { return a[0] + 3 * log(a[0]) / log(10) - sqr(a[1]); }, [](args a) { return sqrt(a[0] + 3 * log(a[0]) / log(10)); } }
    };

    args res = approx({ 3.5, 2.5 }, st);
    cout << res[0] << " " << res[1] << endl;*/

    /*EqSystem st = {
        {F0, phi0},
        {F1, phi1},
        {nullptr, phi2}
    };

    for (double zi = 0; zi <= 0; zi += step) {
        args s = approx({ X(zi), Y(zi), zi }, st);
        cout << s[0] << " " << s[1] << " " << s[2] << " " << st.get(0, s) << " " << st.get(1, s) << endl;
    }*/

    system("pause");
    return 0;
}