#pragma once

using std::ostream;
/**
 * Class - Node of Red-Black tree
 * Key - type of data to be stored
 * Has it's color - Red or Black
 * Pointers to father and both sons
 * and one sentinel vertex
 */
template<class Key>
class Node final {
    template<class Key, class Comp>
    friend class Tree;
    enum class NodeColor : char { Red = 'r', Black = 'b'};
    static Node<Key>* const NIL;
    Key key;
    Node<Key> *parent;
    Node<Key> *left, *right;
    NodeColor color;
    Node () {
        parent = left = right = nullptr;
        color = NodeColor::Black;
        key = Key();
    }
    Node (const Key &key) {
        parent = nullptr;
        left = right = NIL;
        color = NodeColor::Red;
        this->key = key;
    }
};

/**
 * Class - Set of data with type Key (sorted using predicate of type Comp).
 * Able to insert, remove and find some data.
 * Or output whole tree in sorted order.
 */
template<class Key, class Comp = std::less<Key>>
class Tree {
protected:
    typedef typename Node<Key>::NodeColor nColor;
    Node<Key> *root;
    mutable Comp cmp;
    static Node<Key>* const & NIL;

    virtual Node<Key> *rotate_left(Node<Key>*);
    virtual Node<Key> *rotate_right(Node<Key>*);
    virtual void insert_fixup(Node<Key>*);
    virtual void delete_fixup(Node<Key>*);
    virtual Node<Key>* rb_insert(const Key&);
    virtual void rb_delete(Node<Key>*);
    virtual Node<Key>* rb_find(const Key&) const;
    virtual void output(Node<Key>*, ostream&) const;
public:
    Tree() : root(nullptr) {}
    Tree(Comp c) : root(nullptr), cmp(c) {}
    virtual void insert(const Key&);
    virtual bool remove(const Key&);
    virtual bool find(const Key&) const;
    template<class Key, class Comp>
    friend ostream& operator << (ostream&, const Tree<Key, Comp>&);
};

/* sentinel nodes */
template<class Key>
Node<Key>* const Node<Key>::NIL = new Node<Key>();
template<class Key, class Comp>
Node<Key>* const &Tree<Key, Comp>::NIL = Node<Key>::NIL;

/**
 * Rotates tree to the left around current node an returns pointer to node,
 * with which it was replaced.
 */
template<class Key, class Comp>
auto Tree<Key, Comp>::rotate_left(Node<Key>* x) -> Node<Key>* {
    if (x == nullptr || x == NIL || x->right == NIL)
        return x;
    Node<Key>* y = x->right;

    /* left son of right son is not right son */
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;

    /* swap cur vertex and it's right son */
    y->parent = x->parent;
    if (x->parent != nullptr) {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        root = y;
    }

    /* previous vertex is now left son of current */
    y->left = x;
    x->parent = y;
    return y;
}

/* mirror image of rotate_left */
template<class Key, class Comp>
auto Tree<Key, Comp>::rotate_right(Node<Key>* x)  -> Node<Key>* {
    if (x == nullptr || x == NIL || x->left == NIL)
        return x;
    Node<Key>* y = x->left;
    
    x->left = y->right;
    if (y->right != NIL)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent != nullptr) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        root = y;
    }

    x->parent = y;
    y->right = x;
    return y;
}

template<class Key, class Comp>
void Tree<Key, Comp>::insert_fixup(Node<Key>* x) {
    while (x != root && x->parent->color == nColor::Red) {
        if (x->parent == x->parent->parent->left) {
            //get uncle
            Node<Key>* y = x->parent->parent->right;
            if (y->color == nColor::Red) { //uncle is red
                //paint parent as black and grandpa as red and continue doing repair for grapndpa
                x->parent->color = y->color = nColor::Black;
                x->parent->parent->color = nColor::Red;
                x = x->parent->parent;
            } else { //uncle is black
                //make sure that cur vertex is left son of it's parent
                if (x == x->parent->right)
                    x = rotate_left(x->parent)->left;
                x->parent->parent->color = nColor::Red;
                x->parent->color = nColor::Black;
                x = rotate_right(x->parent->parent);
            }
        } else { //mirror image of prev case 
            Node<Key>*y = x->parent->parent->left;
            if (y->color == nColor::Red) {
                x->parent->color = y->color = nColor::Black;
                x->parent->parent->color = nColor::Red;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left)
                    x = rotate_right(x->parent)->right;
                x->parent->parent->color =nColor::Red;
                x->parent->color = nColor::Black;
                x = rotate_left(x->parent->parent);
            }
        }
    }
    root->color = nColor::Black;
}

template<class Key, class Comp>
Node<Key>* Tree<Key, Comp>::rb_insert(const Key &data) {    
    Node<Key>* cur = root, *par = nullptr;

    //find appropriate place for inserting
    while (cur != NIL && cur != nullptr) {
        par = cur;
        if (cmp(cur->key, data))
            cur = cur->right;
        else if (cmp(data, cur->key))
            cur = cur->left;
        else return cur;
    }

    Node<Key>* it = new Node<Key>(data);
    if (par == nullptr)
        root = it;
    else {
        //check if it's left or right son of it's new parent
        if (cmp(it->key, par->key))
            par->left = it;
        else
            par->right = it;
    }
    //connect to parent and restore structure
    it->parent = par;
    insert_fixup(it);
    return it;
}

template<class Key, class Comp>
void Tree<Key, Comp>::delete_fixup(Node<Key>* x) {
    if (x == NIL || x == nullptr)
        return;

    while (x != root && x->color == nColor::Black) {
        if (x == x->parent->left) {
            Node<Key>* w = x->parent->right;
            if (w->color == nColor::Red) { //if brother is red - make it black
                w->color = nColor::Black;
                x->parent->color = nColor::Red;
                rotate_left(x->parent);
                w = x->parent->right;
            }
            //now brother is black
            if (w->left->color == nColor::Black && w->right->color == nColor::Black) {
                //if brother has two black children - make him red and continue doing fixup for parent
                w->color = nColor::Red;
                x = x->parent;
            } else {
                //if one of children is red
                //make sure that right one is red
                if (w->right->color == nColor::Black) {
                    w->color = nColor::Red;
                    w->left->color = nColor::Black;
                    w = rotate_right(w);
                }
                w->color = x->parent->color;
                x->parent->color = nColor::Black;
                w->right->color = nColor::Black;
                rotate_left(x->parent);
                x = root;
            }
        } else { //mirror image
            Node<Key>* w = x->parent->left;
            if (w->color == nColor::Red) {
                w->color = nColor::Black;
                x->parent->color = nColor::Red;
                rotate_right(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == nColor::Black && w->right->color == nColor::Black) {
                w->color = nColor::Red;
                x = x->parent;
            } else {
                if (w->left->color == nColor::Black) {
                    w->right->color = nColor::Black;
                    w->color = nColor::Red;
                    w = rotate_left(w);
                }
                w->color = x->parent->color;
                x->parent->color = nColor::Black;
                x->left->color = nColor::Black;
                rotate_right(x->parent);
                x = root;
            }
        }
    }

    x->color = nColor::Black;
}

template<class Key, class Comp>
void Tree<Key, Comp>::rb_delete(Node<Key>* t) {
    if (t == nullptr || t == NIL)
        return;
    
    //find the node with no left son, which is bigger that cur
    Node<Key> *x, *y;
    if (t->left == NIL || t->right == NIL) {
        y = t;
    } else {
        y = t->right;
        while (y->left != NIL) y = y->left;
    }

    //get another son of it
    if (y->left == NIL)
        x = y->right;
    else
        x = y->left;

    //delete found vertex (put it's only son instead of it)
    x->parent = y->parent;
    if (y->parent != nullptr) {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    } else {
        root = y;
    }

    //swap vertex to delete with vertex with no sons
    if (y != t) swap(y->key, t->key);

    //If deleted vertex was black - fix it
    if (y->color == nColor::Black)
        delete_fixup(x);

    delete y;
}

template<class Key, class Comp>
Node<Key>* Tree<Key, Comp>::rb_find(const Key &data) const {
    Node<Key>* cur = root;
    while (cur != NIL && cur != nullptr) {
        if (cmp(cur->key, data))
            cur = cur->right;
        else if (cmp(data, cur->key))
            cur = cur->left;
        else return cur;
    }
    return nullptr;
}

template<class Key, class Comp>
void Tree<Key, Comp>::output(Node<Key>* t, ostream& out) const {
    if (t == nullptr || t == NIL)
        return;
    output(t->left, out);
    out << t->key << " ";
    output(t->right, out);
}

template<class Key, class Comp>
void Tree<Key, Comp>::insert(const Key& data) {
    rb_insert(data);
}

template<class Key, class Comp>
bool Tree<Key, Comp>::remove(const Key& data) {
    Node<Key>* item = rb_find(data);
    rb_delete(item);
    return item != nullptr;
}

template<class Key, class Comp>
bool Tree<Key, Comp>::find(const Key& data) const {
    return rb_find(data) != nullptr;
}

template<class Key, class Comp>
ostream& operator << (ostream& out, const Tree<Key, Comp>& tree) {
    tree.output(tree.root, out);
    return out;
}