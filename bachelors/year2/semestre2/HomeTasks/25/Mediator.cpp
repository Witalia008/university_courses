#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <random>

using namespace std;

class Mediator {
public:
    virtual void send(string, class User*) = 0;
    virtual void addUser(User*) = 0;
protected:
    vector<User*> users;
};

class ChatMediator : public Mediator {
public:
    void send(string msg, User *sender) override;
    void addUser(User *new_user) override {
        for (auto i : users)
            if (i == new_user)
                return;
        users.push_back(new_user);
    }
};

class User {
protected:
    Mediator *mediator;
public:
    User(Mediator *med) : mediator(med) {
        med->addUser(this);
    }
    virtual void send(string) = 0;
    virtual void notify(string) = 0;
};

class Admin : public User {
public:
    Admin(Mediator *m) : User(m) {}
    void send(string msg) override {
        cout << "God verbs: " << msg << endl;
        mediator->send(msg, this);
    }
    void notify(string msg) override {
        cout << "God hears somewhere someone's yarning.\n";
    }
};

class Dummy : public User {
public:
    Dummy(Mediator *m) : User(m) {}
    void send(string msg) override {
        cout << "Slave prays: " << msg << endl;
        mediator->send(msg, this);
    }
    void notify(string msg) override {
        cout << "Slave contemplates the god speech.\n";
    }
};

void ChatMediator::send(string msg, User* sender) {
    for (auto i : users)
        if (i != sender)
            i->notify(msg);
}

int main()
{
    ChatMediator messager;
    Admin *admin = new Admin(&messager);
    Dummy *user = new Dummy(&messager);
    admin->send("Hello");
    user->send("Hi");
    return 0;
}
