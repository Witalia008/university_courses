#pragma once
#include <exception>
#include <iostream>

class List
{
    friend class ListIterator;
public:
    struct Node
    {
        char _elem;
        Node * _next;
        Node(char q) : _elem(q), _next(nullptr) {}
    };
    class BadList{};
    List(char elem) {
        node = new Node(elem);
    }
    virtual bool cons(char elem) {
        for (Node *i = node; i != nullptr; i = i->_next) {
            if (i->_elem == elem)
                return true;
        }
        return false;
    }
    virtual char head() throw(std::exception) {
        if (node == nullptr)
            throw std::exception("Empty");
        return node->_elem;
    }
    virtual void pop() throw(std::exception) {
        if (node == nullptr)
            throw std::exception("Empty");
        Node *hd = node->_next;
        delete node;
        node = hd;
    }
    virtual void push(char elem) {
        if (node == nullptr)
            node = new Node(elem);
        else {
            Node *p = node;
            while (p->_next != nullptr) p = p->_next;
            p->_next = new Node(elem);
        }
    }
    virtual ListIterator iterate();
    virtual void show() {
        if (node == nullptr) {
            std::cout << "Empty" << std::endl;
            return;
        }
        Node *i = node;
        do {
            cout << i->_elem << " ";
            i = i->_next;
        } while (i != nullptr && i != node);
        std::cout << std::endl;
    }
protected:
    Node * node;
};

class ListIterator
{
    bool start;
    List::Node * _first;
    List::Node * _current;
public:
    void begin(List *lst) {
        _first = _current = lst->node;
        start = true;
    }
    char get() throw(std::exception) {
        if (_current == nullptr)
            throw std::exception("Out of bounds");
        return _current->_elem;
    }
    void next() {
        if (_current == nullptr)
            throw std::exception("Out of bounds");
        _current = _current->_next;
        start = false;
    }
    bool end() {
        return _current == nullptr || _current->_next == _first;
    }
};

ListIterator List::iterate()  {
    ListIterator res;
    res.begin(this);
    return res;
}