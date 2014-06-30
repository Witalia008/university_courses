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

class Command {
public:
    virtual void execute() = 0;
};

class Person;

class TalkCommand : public Command {
    Person *receiver;
    void (Person:: *method) ();
public:
    TalkCommand(Person *obj = 0, void (Person:: *meth)() = 0):
        receiver(obj), method(meth) {}
    void execute() {
        (receiver->*method)();
    }
};

class Person {
    string name;
    Command *cmd;
public:
    Person(string n, Command *c) : name(n), cmd(c) {}
    void talk()
    {
        cout << name << " is talking" << endl;
        cmd->execute();
    }
    void passOn()
    {
        cout << name << " is passing on" << endl;
        cmd->execute();
    }
    void gossip()
    {
        cout << name << " is gossiping" << endl;
        cmd->execute();
    }
    void listen()
    {
        cout << name << " is listening" << endl;
    }
};

int main()
{
    Person wilma("Wilma", new TalkCommand());
    Person betty("Betty", new TalkCommand(&wilma, &Person::listen));
    Person barney("Barney", new TalkCommand(&betty, &Person::gossip));
    Person fred("Fred", new TalkCommand(&barney, &Person::passOn));
    fred.talk();
    return 0;
}
