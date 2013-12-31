#pragma once
#include <vector>
#include <iostream>

using namespace std;

template<class T>
class Node final {
    template<class T>
    friend class BTree;
    vector<T> data;
    vector<Node<T>*> sons;
    Node<T> *par;

    Node(const T&);
    Node(vector<T>, vector<Node<T>*>);
    void add_data(const T&);
    void add_son_after(Node<T>*, Node<T>*);
    bool is_leaf() { return sons.size() == 0; }
    bool is_full(int t) { return data.size() >= 2 * t; }
    Node<T> *splice(int, int);
    void erase(int, int, bool, bool);

    Node<T> *get_son(int);
    T get_data(int);
    void set_data(int, const T&);
    int get_id(Node<T>*);
    int get_pos(const T&);

    Node<T>* merge_nodes(int);

    T max_el() { return data.back(); }
    T min_el() { return data[0]; }
};

template<class T>
Node<T>::Node(const T& data) {
    this->data.assign(1, data);
    this->sons.clear();
    par = nullptr;
}

template<class T>
Node<T>::Node(vector<T> data, vector<Node<T>*> sons) {
    this->data = data;
    this->sons = sons;
    for (auto &i : sons)
        i->par = this;
    par = nullptr;
}

template<class T>
void Node<T>::add_data(const T& data) {
    for (int i = this->data.size() - 1; i >= 0; --i) {
        if (this->data[i] <= data) {
            this->data.insert(this->data.begin() + i + 1, data);
            return;
        }
    }
    this->data.insert(this->data.begin(), data);
}

template<class T>
void Node<T>::add_son_after(Node<T>* wher, Node<T>* wat) {
    if (wher == nullptr) {
        this->sons.insert(this->sons.begin(), wat);
    }
    else {
        for (int i = 0; i < this->sons.size(); ++i) {
            if (this->sons[i] == wher) {
                this->sons.insert(this->sons.begin() + i + 1, wat);
            }
        }
    }
    wat->par = this;
}

template<class T>
Node<T> *Node<T>::splice(int from, int to) {
    return new Node<T>(vector<T>(data.begin() + from, data.begin() + to),
        sons.size() ? vector<Node<T>*>(sons.begin() + from, sons.begin() + to + 1) : vector<Node<T>*>());
}

template<class T>
void Node<T>::erase(int from, int to, bool with_l, bool with_r) {
    data.erase(data.begin() + from, data.begin() + to);
    if (sons.size())
        sons.erase(sons.begin() + from + (!with_l), sons.begin() + to + with_r);
}

template<class T>
Node<T> *Node<T>::get_son(int id) {
    return sons[id];
}

template<class T>
T Node<T>::get_data(int pos) {
    return data[pos];
}

template<class T>
void Node<T>::set_data(int pos, const T& new_d) {
    data[pos] = new_d;
}

template<class T>
int Node<T>::get_id(Node<T>* son) {
    for (int i = 0; i < sons.size(); ++i) {
        if (sons[i] == son)
            return i;
    }
    return -1;
}

template<class T>
int Node<T>::get_pos(const T& item) {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] == item)
            return i;
    }
    return -1;
}

template<class T>
Node<T>* Node<T>::merge_nodes(int id) {
    Node<T> *left = get_son(id);
    Node<T> *right = get_son(id + 1);
    left->data.push_back(get_data(id));
    erase(id, id + 1, false, true);
    left->data.insert(left->data.end(), right->data.begin(), right->data.end());
    left->sons.insert(left->sons.end(), right->sons.begin(), right->sons.end());
    for (auto i : right->sons)
        i->par = left;
    return left;
}



template<class T>
class BTree {
public:
    BTree(int t) : param(t), root(nullptr) {}
    bool insert(const T&);
    bool find(const T&) const;
    bool remove(const T&);

    template<class T>
    friend ostream& operator << (ostream &out, const BTree<T>&);
private:
    Node<T> *find_t(Node<T>*, const T&) const;
    void insert_t(Node<T>*, const T&);
    void delete_t(Node<T>*, const T&);
    T get_min(Node<T>*) const;
    T get_max(Node<T>*) const;
    void output(Node<T>*, ostream&) const;
    void check_underflow(Node<T>*);

    int param;
    Node<T> *root;
};

template<class T>
Node<T> *BTree<T>::find_t(Node<T>* t, const T& target) const {
    if (t == nullptr)
        return nullptr;
    for (int i = t->data.size() - 1; i >= 0; --i) {
        if (t->data[i] == target)
            return t;
        if (target >= t->data[i]) {
            if (t->sons.size())
                return find_t(t->sons[i + 1], target);
        }
    }
    if (t->sons.size())
        return find_t(t->sons[0], target);
    return nullptr;
}


template<class T>
void BTree<T>::insert_t(Node<T>* t, const T& item) {
    if (t == nullptr) {
        root = new Node<T>(item);
        return;
    }
    if (t->is_leaf()) { 
        t->add_data(item);
    }
    else {
        bool fl = false;
        for (int i = t->data.size() - 1; i >= 0 && !fl; --i) {
            if (item >= t->data[i]) {
                insert_t(t->sons[i + 1], item);
                fl = true;
            }
        }
        if (!fl) insert_t(t->sons[0], item);
    }
    if (t->is_full(param)) {
        int sz = t->data.size();
        if (t == root) {
            root = new Node<T>({ t->data[sz / 2] }, { t->splice(0, sz / 2), t->splice(sz / 2 + 1, sz) });
        }
        else {
            t->par->add_data(t->data[sz / 2]);
            t->par->add_son_after(t, t->splice(sz / 2 + 1, sz));
            t->erase(sz / 2, sz, false, true);
        }
    }
}

template<class T>
void BTree<T>::delete_t(Node<T>* t, const T& item) {
    if (t->is_leaf()) {
        if (t == root || t->data.size() >= param) {
            t->erase(t->get_pos(item), t->get_pos(item) + 1, 0, 0);
        }
        else {
            int id = t->par->get_id(t);
            Node<T> *left = id > 0 ? t->par->get_son(id - 1) : nullptr;
            Node<T> *right = id < t->par->sons.size() - 1 ? t->par->get_son(id + 1) : nullptr;
            if (left != nullptr && left->data.size() >= param) {
                t->set_data(t->get_pos(item), t->par->get_data(id - 1));
                t->par->set_data(id - 1, left->max_el());
                left->erase(left->data.size() - 1, left->data.size(), 0, 0);
            }
            else if (right != nullptr && right->data.size() >= param) {
                t->set_data(t->get_pos(item), t->par->get_data(id));
                t->par->set_data(id, right->min_el());
                right->erase(0, 1, 0, 0);
            }
            else {
                t = t->par->merge_nodes(left != nullptr ? id - 1 : id);
                t->erase(t->get_pos(item), t->get_pos(item) + 1, 0, 0);
            }
        }
        return;
    }
    if (t->get_pos(item) != -1) {
        int pos = t->get_pos(item);
        Node<T> *left = t->get_son(pos);
        Node<T> *right = t->get_son(pos + 1);
        if (left->data.size() >= param) {
            T a = get_max(left);
            t->set_data(pos, a);
            delete_t(left, a);
        }
        else if (right->data.size() >= param) {
            T a = get_min(right);
            t->set_data(pos, a);
            delete_t(right, a);
        }
        else {
            t = t->merge_nodes(pos);
            delete_t(t, item);
            check_underflow(t);
        }
    }
    else {
        int id = -1;
        for (int i = t->data.size() - 1; i >= 0; --i) {
            if (item >= t->data[i]) {
                id = i;
                break;
            }
        }
        delete_t(t->get_son(id + 1), item);
        check_underflow(t);
    }
}

template<class T>
void BTree<T>::check_underflow(Node<T>* t) {
    if (t->data.size() < param - 1) {
        if (t == root) {
            if (t->data.size() == 0) {
                if (root->sons.size()) {
                    root->sons[0]->par = nullptr;
                    root = root->sons[0];
                }
                else {
                    root = nullptr;
                }
                delete t;
            }
        }
        else {
            int id = t->par->get_id(t);
            t->par->merge_nodes(id > 0 ? id - 1 : id);
        }
    }
}

template<class T>
T BTree<T>::get_max(Node<T>* t) const {
    if (t == nullptr)
        return T();
    if (t->sons.size())
        return get_min(t->sons.back());
    return t->data.back();
}

template<class T>
T BTree<T>::get_min(Node<T>* t) const {
    if (t == nullptr)
        return T();
    if (t->sons.size())
        return get_min(t->sons[0]);
    return t->data[0];
}

template<class T>
bool BTree<T>::insert(const T& new_el) {
    if (!find(new_el)) {
        insert_t(root, new_el);
        return true;
    }
    return false;
}

template<class T>
bool BTree<T>::find(const T& item) const {
    return find_t(root, item) != nullptr;
}

template<class T>
bool BTree<T>::remove(const T& item) {
    if (find(item)) {
        delete_t(root, item);
        return true;
    }
    return false;
}

template<class T>
void BTree<T>::output(Node<T> *t, ostream &out) const {
    for (int i = 0; i < t->data.size(); ++i) {
        if (!t->is_leaf())
            output(t->sons[i], out);
        out << t->data[i] << " ";
    }
    if (!t->is_leaf())
        output(t->sons.back(), out);
}

template<class T>
ostream& operator << (ostream &out, const BTree<T>& t) {
    t.output(t.root, out);
    return out;
}