#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <memory.h>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <queue>
#include <stack>
#include <complex>
#include <limits.h>
#include <cassert>
#include <chrono>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <valarray>

using namespace std;
using namespace std::chrono;

using ll = long long;
const int Inf = 1000000000;

stack<double> st;

void output()
{
    cout << "stack:";
    stack<int> s;
    while (!st.empty())
    {
        s.push(st.top());
        st.pop();
    }
    while (!s.empty())
    {
        cout << " " << s.top();
        st.push(s.top());
        s.pop();
    }
    cout << endl;
}

//#define ONLINE_JUDGE
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    int cur;
    for (;;)
    {
        string op = "";
        cin >> op;
        if (op == "")
            break;
        if (op == "push")
        {
            double x;
            cin >> x;
            if (st.size() < 8)
                st.push(x);
        }
        else if (op == "pop")
        {
            if (st.size())
            {
                cout << st.top() << endl;
                st.pop();
            }
            else
                cout << "Empty\n";
        }
        else if (op == "add" || op == "sub" || op == "mul" || op == "div" || op == "rev")
        {
            if (st.size() >= 2)
            {
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                if (op == "add")
                {
                    st.push(a + b);
                }
                else if (op == "sub")
                {
                    st.push(a - b);
                }
                else if (op == "mul")
                {
                    st.push(a * b);
                }
                else if (op == "div")
                {
                    st.push(a / b);
                }
                else
                {
                    st.push(a);
                    st.push(b);
                }
            }
        }
        else if (op == "dup")
        {
            if (st.size() < 8)
            {
                st.push(st.top());
            }
        }
        output();
        _sleep(2000);
    }
    return 0;
}