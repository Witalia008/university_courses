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

class Meal {
public:
    Meal (string pack_name) {
        recipe += pack_name + "Menu: .\nItems are:\n";
    }
    void setMainItem(string itName) {
        recipe += "Main item: " + itName + "\n";
    }
    void setSideItem(string itName) {
        recipe += "Side item: " + itName + "\n";
    }
    void setDrink(string name) {
        recipe += "Drink: " + name + "\n";
    }
    void setToy(string name) {
        recipe += "Toy: " + name + "\n";
    }
    string getState() {
        return recipe;
    }
private:
    string recipe;
};

class MacMenuBuilder {
protected:
    vector<string> mainItem_names;
    vector<string> sideItem_names;
    vector<string> drink_names;
    vector<string> toy_names;
public:
    virtual void configureMainItem(string name) = 0;
    virtual void configureSideItem(string name) = 0;
    virtual void configureDrink(string name) = 0;
    virtual void configureToy(string name) = 0;
    Meal *getResult () {
        return result;
    }
protected:
    Meal *result;
};

void MacMenuBuilder::configureMainItem(string name) {
    if (find(mainItem_names.begin(), mainItem_names.end(), name) == mainItem_names.end())
        name = mainItem_names[rand() % mainItem_names.size()];
    result->setMainItem(name + ".");
}

void MacMenuBuilder::configureSideItem(string name) {
    if (find(sideItem_names.begin(), sideItem_names.end(), name) == sideItem_names.end())
        name = sideItem_names[rand() % sideItem_names.size()];
    result->setSideItem(name + ".");
}

void MacMenuBuilder::configureDrink(string name) {
    if (find(drink_names.begin(), drink_names.end(), name) == drink_names.end())
        name = drink_names[rand() % drink_names.size()];
    result->setDrink(name + ".");
}

void MacMenuBuilder::configureToy(string name) {
    if (find(toy_names.begin(), toy_names.end(), name) == toy_names.end())
        name = toy_names[rand() % toy_names.size()];
    result->setToy(name + ".");
}

class BigMacMenuBuilder : public MacMenuBuilder {
public:
    BigMacMenuBuilder() {
        result = new Meal("Big Mac Menu");
        mainItem_names = {"Big Mac"};
        sideItem_names = {"Fried Potatoes"};
        drink_names = {"Coke", "Sprite", "Fanta"};
        toy_names = {"Truck", "Robot", "Doll"};
    }
    void configureMainItem(string name) override {
        MacMenuBuilder::configureMainItem(name);
    }
    void configureSideItem(string name) override {
        MacMenuBuilder::configureSideItem(name);
    }
    void configureDrink(string name) override {
        MacMenuBuilder::configureDrink(name);
    }
    void configureToy(string name) override {
        MacMenuBuilder::configureToy(name);
    }
};

class HappyMealMenuBuilder : public MacMenuBuilder {
public:
    HappyMealMenuBuilder() {
        result = new Meal("Children Happy Meal Mac Menu");
        mainItem_names = {"Hamburger", "Cheeseburger", "Chicken MacNuggets"};
        sideItem_names = {"Fried Potatoes", "Carrot Sticks"};
        drink_names = {"Coke", "Sprite", "Fanta", "Apple Juice", "Exotic Juice",
                        "Fizzy Water BonAqua", "NotFizzy Water BonAqua"};
        toy_names = {"Truck", "Robot", "Doll"};
    }
    void configureMainItem(string name) override {
        MacMenuBuilder::configureMainItem(name);
    }
    void configureSideItem(string name) override {
        MacMenuBuilder::configureSideItem(name);
    }
    void configureDrink(string name) override {
        MacMenuBuilder::configureDrink(name);
    }
    void configureToy(string name) override {
        MacMenuBuilder::configureToy(name);
    }
};

class Director {
public:
    Director(MacMenuBuilder* _nb) : builder(_nb) {}
    void construct(istream &in) {
        string s;
        in >> s;
        builder->configureMainItem(s);
        in >> s;
        builder->configureSideItem(s);
        in >> s;
        builder->configureDrink(s);
        in >> s;
        builder->configureToy(s);
    }
protected:
    MacMenuBuilder* builder;
};

int main()
{
    BigMacMenuBuilder bmmb;
    Director dir(&bmmb);
    dir.construct(cin);
    cout << bmmb.getResult()->getState() << endl;

    HappyMealMenuBuilder hmmb;
    dir = Director(&hmmb);
    dir.construct(cin);
    cout << hmmb.getResult()->getState() << endl;
    return 0;
}
