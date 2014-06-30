#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <random>

using namespace std;

class Visitor {
public:
    virtual void visit(class ClothsStore*) = 0;
    virtual void visit(class ShoesStore*) = 0;
};

class StoreElement {
protected:
    vector<string> items;
public:
    virtual void accept(Visitor*) = 0;
    string getItem() {
        return items[rand() % items.size()];
    }
};

class ClothsStore : public StoreElement {
public:
    ClothsStore() {
        items = {"T-Shirt", "Shirt", "Pants", "Panties", "Pantyhose", "Hat"};
    }
    void accept(Visitor* v) {
        v->visit(this);
    }
};

class ShoesStore : public StoreElement {
public:
    ShoesStore() {
        items = {"Sneakers", "Boots", "Other"};
    }
    void accept(Visitor* v) {
        v->visit(this);
    }
};

class Stores : public StoreElement {
    vector<StoreElement*> stores;
public:
    void attach(StoreElement* a) {
        stores.push_back(a);
    }
    void accept(Visitor *v) {
        for (auto i : stores)
            i->accept(v);
    }
};

class WomenVisitor : public Visitor {
    string name;
public:
    WomenVisitor(string n) : name(n) {}
    void visit(StoreElement* store) {
        for (int i = 0; i < 10; ++i)
            cout << name << " has bought " << rand() % 10 + 1 <<
                " pairs of " << store->getItem() << endl;
    }
    void visit(ClothsStore* store) override {
        cout << "Cloth Store:\n";
        visit((StoreElement*)store);
    }
    void visit(ShoesStore* store) override {
        cout << "Shoes Store:\n";
        visit((StoreElement*)store);
    }
};

class MenVisitor : public Visitor {
    string name;
public:
    MenVisitor(string n) : name(n) {}
    void visit(StoreElement* store) {
        cout << name << " has bought one pair of " << store->getItem() << endl;
    }
    void visit(ClothsStore* store) override {
        cout << "Cloth Store:\n";
        visit((StoreElement*)store);
    }
    void visit(ShoesStore* store) override {
        cout << "Shoes Store:\n";
        visit((StoreElement*)store);
    }
};

int main()
{
    Stores st;
    st.attach(new ClothsStore());
    st.attach(new ShoesStore());
    WomenVisitor *wm = new WomenVisitor("Woman");
    MenVisitor *m = new MenVisitor("Man");
    st.accept(wm);
    st.accept(m);
    return 0;
}
