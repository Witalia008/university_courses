#pragma once
#include <ostream>
class List {
protected:
    class Node {
    friend class List;
    protected:
        int data;
        Node *next;
    public:
        Node() : data(0), next(nullptr) {}
        Node(int d) : data(d), next(nullptr) {}
        Node(int d, Node *nxt) : data(d), next(nxt) {}
        ~Node() {}
    };
    Node *head, *tail;
    int sz;
public:
    class iterator {
    friend class List;
    private:
        Node *pos;
    public:
        iterator() {};
        iterator(Node*a) : pos(a) {}
        iterator(iterator&a) : pos(a.pos) {}
        int operator*() {
            return pos->data;
        }
        iterator operator++() {
            iterator res = *this;
            if (pos->next)
                pos = pos->next;
            return res;
        }
        iterator operator++(int) {
            if (pos->next)
                pos = pos->next;
            return *this;
        }
        bool operator==(iterator b) {
            return this->pos == b.pos;
        }
        bool operator!=(iterator b) {
            return !(*this == b);
        }
    };
    List();
    List(const List&);
    ~List();
    int size() { return sz; }
    void push_back(int data);
    void pop_back();
    void push_front(int data);
    void pop_front();
    void emplace_back(iterator);
    void emplace_front(iterator);
    void insert_before(iterator, iterator);
    void insert_after(iterator, iterator);
    iterator remove(iterator);
    int front() throw();
    int back() throw();
    iterator begin();
    iterator end();
    iterator last();
};

std::ostream& operator<<(std::ostream& out, List &l);