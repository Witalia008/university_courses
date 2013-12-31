#pragma once
#include <stdio.h>
#include <algorithm>
#include <list>
#include <ostream>
#include <vector>

using namespace std;

template<class T>
class Queue {
protected:
    list<T> queue;
public:
    Queue() {}
    Queue(const Queue<T>&);
    Queue(const vector<T>&);
    int size() { return queue.size(); }
    void push(T elem) { queue.push_back(elem); }
    void pop();
    T front();
    bool empty() { return queue.size() == 0; };
    void append(Queue<T>);
    friend ostream& operator<<(ostream&, const Queue<T>&);
    void output() {
        copy(queue.begin(), queue.end(), ostream_iterator<T>(cout, " "));
        cout << endl;
    }
};

template<class T>
Queue<T>::Queue(const Queue<T>& b) {
    queue.resize(b.queue.size());
    copy(b.queue.begin(), b.queue.end(), queue.begin());
}

template<class T>
Queue<T>::Queue(const vector<T>& b) {
    queue.resize(b.size());
    copy(b.begin(), b.end(), queue.begin());
}

template<class T>
void Queue<T>::pop() {
    if (queue.size() == 0)
        throw out_of_range("");
    queue.pop_front();
}

template<class T>
T Queue<T>::front() {
    if (queue.size() == 0)
        throw out_of_range("");
    return queue.front();
}

template<class T>
ostream& operator<<(ostream& out, const Queue<T> &q) {
    copy(q.queue.begin(), q.queue.end(), ostream_iterator<T>(out, " "));
    return out;
}

template<class T>
void Queue<T>::append(Queue<T> another) {
    while (!another.empty()) {
        push(another.front());
        another.pop();
    }
}

template<class T>
void quickSort(Queue<T> &q) {
    if (q.size() < 2)
        return;
    T etalon = q.front();
    Queue<T> l, r;
    int cnt = 0;
    while (!q.empty()) {
        T cur = q.front();
        q.pop();
        if (cur < etalon)
            l.push(cur);
        else if (cur > etalon)
            r.push(cur);
        else cnt++;
    }
    quickSort(l);
    quickSort(r);
    q.append(l);
    for(int i = 0; i < cnt; ++i) q.push(etalon);
    q.append(r);
}

template<class T>
void insertionSort(Queue<T> &q) {
    Queue<T> l, r;
    while (!q.empty()) {
        T cur = q.front();
        q.pop();
        while (!l.empty() && cur > l.front()) {
            r.push(l.front());
            l.pop();
        }
        r.push(cur);
        r.append(l);
        swap(l, r);
        while (!r.empty()) r.pop();
    }
    q = l;
}