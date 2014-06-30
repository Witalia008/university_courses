#pragma once
#include "List.h"

class CyclicList: virtual public List
{
public:
    CyclicList(char elem)
        :List(elem) {
        node->_next = node;
    }
    virtual bool cons(char elem) override {
        if (node == nullptr)
            return false;
        Node *hd = node;
        do {
            if (hd->_elem == elem)
                return true;
            hd = hd->_next;
        } while (hd != node);
        return false;
    }
    virtual void push(char elem) override {
        if (node == nullptr) {
            node = new Node(elem);
            node->_next = node;
            return;
        }
        Node *p = node;
        while (p->_next != node) p = p->_next;
        p->_next = new Node(elem);
        p->_next->_next = node;
    }
//    virtual char head();
    virtual void pop() throw(std::exception) override {
        if (node == nullptr)
            throw std::exception("Empty");
        Node *p = node;
        if (node->_next != node) {
            Node *q = node->_next;
            while (q->_next != node) q = q->_next;
            q->_next = node->_next;
            node = node->_next;
        }
        else node = nullptr;
        delete p;
    }
};

class DoubleSidedList: virtual public List
{
protected:
    Node * prev;
public:
    DoubleSidedList(char elem)
        : List(elem)
    {
        prev = node;
    }
    virtual bool cons(char elem) override {
        return List::cons(elem);
    }
    virtual void push(char elem) override {
        if (node == nullptr) node = prev = new Node(elem);
        else prev = prev->_next = new Node(elem);
    }
    //    virtual char head();
    virtual void pop() throw(std::exception) override {
        if (node == nullptr)
            throw std::exception("Empty");
        Node *p = node;
        if (node == prev)
            node = prev = nullptr;
        else {
            node = node->_next;
            if (prev->_next != nullptr)
                prev->_next = node;
        }
        delete p;
    }
};

class CyclicDoubleSidedList: public DoubleSidedList, public CyclicList
{
public:
    CyclicDoubleSidedList(char elem)
        :  List(elem), DoubleSidedList(elem), CyclicList(elem) {

    }
    virtual bool cons(char elem) override {
        return CyclicList::cons(elem);
    }
    virtual char head() throw(std::exception) override {
        return List::head();
    }
    virtual void push(char elem) override {
        CyclicList::push(elem);
        while (prev->_next != node) prev = prev->_next;
    }
    virtual void pop() throw(std::exception) override {
        DoubleSidedList::pop();
    }
};
