#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <iterator>
#include <ctime>

using namespace std;

class Subject {
    vector<class Observer*> views;
    int bid;
    bool now_nf, need_nf;
public:
    Subject() : bid(0) {}
    void attach(Observer *obs) {
        views.push_back(obs);
    }
    void setBid(int newBid) {
        if (bid < newBid) {
            bid = newBid;
            if (!now_nf)
                notifyAll();
            else
                need_nf = true;
        }
    }
    int getBid() {
        return bid;
    }
    void notifyAll();
};

class Observer {
protected:
    Subject *model;
    string name;
public:
    Observer(Subject *mod, string n) :
        name(n), model(mod)
    {
        model->attach(this);
    }
    virtual void update() = 0;
protected:
    Subject* getSubject() {
        return model;
    }
    string getName() {
        return name;
    }
};

void Subject::notifyAll() {
    now_nf = true;
    for (auto i: views)
        i->update();
    now_nf = false;
    if (need_nf) {
        need_nf = false;
        notifyAll();
    }
}

class BidObserver : public Observer {
    int lastBid;
public:
    BidObserver(Subject* mod, string name, int lb = -1) :
        Observer(mod, name), lastBid(lb) {}
    void update() {
        cout << name << ", current bid is " << model->getBid() << ". Do you want to increase it?[y / n]: ";
        string ans;
        cin >> ans;
        if (ans == "y") {
            cin >> lastBid;
            model->setBid(lastBid);
        }
    }
};

int main()
{
    Subject auct;
    BidObserver first(&auct, "First");
    BidObserver second(&auct, "Second");
    BidObserver third(&auct, "Third");
    auct.setBid(10);
    return 0;
}
