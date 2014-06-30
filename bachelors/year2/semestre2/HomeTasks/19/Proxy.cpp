#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <iterator>

using namespace std;

class Subject {
public:
    virtual void request() = 0;
};

class RealSubject : public Subject {
public:
    void request() override {
        cout << "Request to real subject completed!" << endl;
    }
};

class Proxy : public Subject {
    RealSubject *real_s;
public:
    Proxy() : real_s(nullptr) {}
    void request() {
        if (real_s == nullptr)
            real_s = new RealSubject();
        real_s->request();
    }
};

int main()
{
    Proxy p;
    p.request();
    return 0;
}
