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

class Widget {
public:
    virtual void draw() = 0;
};

class TextField : public Widget {
    int width, height;
public:
    TextField(int w, int h) : width(w), height(h) {}
    void draw() override {
        cout << "TextField: " << width << " * " << height << endl;
    }
};

class Decorator : public Widget {
    Widget *wid;
public:
    Decorator(Widget *w) : wid(w) {}
    void draw() override {
        wid->draw();
    }
};

class BorderDecorator : public Decorator {
public:
    BorderDecorator(Widget *w) : Decorator(w) {}
    void draw() override {
        Decorator::draw();
        cout << " with Borders" << endl;
    }
};

class ScrollDecorator : public Decorator {
public:
    ScrollDecorator(Widget *w) : Decorator(w) {}
    void draw() override {
        Decorator::draw();
        cout << " with Scroll Bars" << endl;
    }
};

int main()
{
    Widget *widget = new BorderDecorator(new BorderDecorator(new ScrollDecorator(new TextField(20, 30))));
    widget->draw();
    return 0;
}
