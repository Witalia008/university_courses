#include "List.h"

List::List() : sz(0) {
    head = tail = new Node();
}

List::~List() {
    while (head != nullptr) {
        List::Node *cur = head;
        head = head->next;
        cur->~Node();
    }
}

void List::push_back(int a) {
    if (tail->next == nullptr) {
        head = tail = new Node(a, tail);
    } else {
        Node *p = tail->next;
        tail->next = new Node(a);
        tail = tail->next;
        tail->next = p;
    }
    ++sz;
}

void List::pop_back() {
    if (tail->next == nullptr)
        return;
    if (head == tail) {
        tail = tail->next;
        head->~Node();
        head = tail;
    } else {
        Node* p = head;
        while (p->next != tail)
            p = p->next;
        p->next = tail->next;
        tail->~Node();
        tail = p;
    }
    --sz;
}

void List::push_front(int a) {
    head = new Node(a, head);
    if (tail->next == nullptr)
        tail = head;
    ++sz;
}

void List::pop_front() {
    if (tail->next == nullptr)
        return;
    Node* p = head->next;
    head->~Node();
    head = p;
    if (head->next == nullptr)
        tail = head;
    --sz;
}

void List::emplace_back(iterator a) {
    insert_after(last(), a);
} 

void List::emplace_front(iterator a) {
    insert_before(begin(), a);
}

void List::insert_before(iterator whe, iterator what) {
    if (whe.pos == head) {
        head = what.pos;
        head->next = whe.pos;
        if (whe.pos->next == nullptr)
            tail = head;
    } else {
        Node *p = head;
        while (p != nullptr && p->next != whe.pos)
            p = p->next;
        if (p == nullptr)
            return;
        what.pos->next = whe.pos;
        p->next = what.pos;
    }
    ++sz;
}

void List::insert_after(iterator whe, iterator what) {
    if (whe.pos->next == nullptr) {
        insert_before(whe, what);
        return;
    }
    what.pos->next = whe.pos->next;
    whe.pos->next = what.pos;
    if (tail == whe.pos)
        tail = tail->next;
    ++sz;
}

List::iterator List::remove(iterator a) {
    if (a == end())
        return end();
    if (a == begin()) {
        if (head == tail)
            tail = tail->next;
        Node *p = head->next;
        head = p;
    } else {
        Node *p = head;
        while (p != nullptr && p->next != nullptr)
            p = p->next;
        if (p == nullptr)
            return end();
        p->next = a.pos->next;
    }
    --sz;
    return a;
}

int List::front() {
    if (head == nullptr)
        throw;
    return head->data;
}

int List::back() {
    if (head == nullptr)
        throw;
    return tail->data;
}

List::iterator List::begin() {
    return iterator(head);
}

List::iterator List::end() {
    return iterator(tail->next == nullptr ? tail : tail->next);
}

List::iterator List::last() {
    return iterator(tail);
}

std::ostream& operator<<(std::ostream& out, List &l) {
    for (List::iterator it = l.begin(); it != l.end(); it++)
        out << *it << " ";
    return out;
}