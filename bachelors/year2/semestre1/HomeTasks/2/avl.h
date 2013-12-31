#ifndef AVL_H
#define AVL_H

template<class T>
class AvlSet {
    class TreeNode {
        T data;
        int height;
        TreeNode *leftSon;
        TreeNode *rightSon;
        TreeNode(const T&);
        void updateHeight();
        int getHeight();
        int getBalance();
        TreeNode* balance();
        TreeNode* rotateLeft();
        TreeNode* rotateRight();
        TreeNode* insert(const T&);
        TreeNode* find(const T&);
        pair<TreeNode*, TreeNode*> eraseMin();
        TreeNode* erase(const T&);
        void output();
        bool isAvl();
        friend class AvlSet;
    };
    TreeNode *tree;
    bool isAvl();
    void output();
public:
    AvlSet();
    void insert(const T&);
    void erase(const T&);
};

template<class T>
AvlSet<T>::AvlSet() {
    tree = nullptr;
}

template<class T>
AvlSet<T>::TreeNode::TreeNode(const T& nodeData) {
    data = nodeData;
    leftSon = rightSon = nullptr;
    height = 1;
}

template<class T>
int AvlSet<T>::TreeNode::getHeight() {
    return height;
}

template<class T>
void AvlSet<T>::TreeNode::updateHeight() {
    height = 0;
    if (leftSon != nullptr)
        height = max(height, leftSon->getHeight());
    if (rightSon != nullptr)
        height = max(height, rightSon->getHeight());
    height++;
}

template<class T>
int AvlSet<T>::TreeNode::getBalance() {
    int balance = 0;
    if (leftSon != nullptr)
        balance = leftSon->getHeight();
    if (rightSon != nullptr)
        balance -= rightSon->getHeight();
    return balance;
}

template<class T>
auto AvlSet<T>::TreeNode::balance() -> TreeNode* {
    TreeNode *res = this;
    res->updateHeight();
    if (getBalance() == 2) {
        if (leftSon->getBalance() == -2)
            leftSon = leftSon->rotateLeft();
        res = rotateRight();
    } else if (getBalance() == -2) {
        if (rightSon->getBalance() == 2)
            rightSon = rightSon->rotateRight();
        res = rotateLeft();
    }
    res->updateHeight();
    return res;
}

template<class T>
auto AvlSet<T>::TreeNode::rotateLeft() -> TreeNode* {
    if (getHeight() == 1)
        return this;
    TreeNode *temp = rightSon;
    rightSon = temp->leftSon;
    temp->leftSon = this;
    updateHeight();
    temp->updateHeight();
    return temp;
}

template<class T>
auto AvlSet<T>::TreeNode::rotateRight() -> TreeNode* {
    if (getHeight() == 1)
        return this;
    TreeNode *temp = leftSon;
    leftSon = temp->rightSon;
    temp->rightSon = this;
    updateHeight();
    temp->updateHeight();
    return temp;
}

template<class T>
auto AvlSet<T>::TreeNode::insert(const T& newData) -> TreeNode* {
    if (data == newData)
        return this;
    if (newData < data) {
        if (leftSon == nullptr)
            leftSon = new TreeNode(newData);
        else
            leftSon = leftSon->insert(newData);
    } else {
        if (rightSon == nullptr)
            rightSon = new TreeNode(newData);
        else
            rightSon = rightSon->insert(newData);
    }
    return balance();
}

template<class T>
auto AvlSet<T>::TreeNode::find(const T& eData) -> TreeNode* {
    if (data == eData)
        return this;
    if (eData < data)
        return leftSon == nullptr ? nullptr : leftSon->find(eData);
    else
        return rightSon == nullptr ? nullptr : rightSon->find(eData);
}

template<class T>
auto AvlSet<T>::TreeNode::eraseMin() -> pair<TreeNode*, TreeNode*> {
    if (leftSon == nullptr) {
        return make_pair(this, rightSon);
    }
    auto ls = leftSon->eraseMin();
    leftSon = ls.second;
    return make_pair(ls.first, this);
}

template<class T>
auto AvlSet<T>::TreeNode::erase(const T& eData) -> TreeNode* {
    if (data == eData) {
        TreeNode *res = nullptr;
        if (rightSon == nullptr) {
            res = leftSon;
        } else {
            auto it = rightSon->eraseMin();
            res = it.first;
            res->leftSon = leftSon;
            res->rightSon = it.second;
        }
        if (res != nullptr)
            res = res->balance();
        return res;
    } else {
        if (eData < data)
            leftSon = leftSon == nullptr ? nullptr : leftSon->erase(eData);
        else
            rightSon = rightSon == nullptr ? nullptr : rightSon->erase(eData);
        return balance();
    }
}

template<class T>
void AvlSet<T>::insert(const T& newData) {
    if (tree == nullptr)
        tree = new TreeNode(newData);
    else
        tree = tree->insert(newData);
}

template<class T>
void AvlSet<T>::erase(const T& eData) {
    if (tree != nullptr)
        tree = tree->erase(eData);
}

template<class T>
void AvlSet<T>::TreeNode::output() {
    if (leftSon != nullptr)
        leftSon->output();
    cout << data << endl;
    if (rightSon != nullptr)
        rightSon->output();
}

template<class T>
void AvlSet<T>::output() {
    if (tree != nullptr)
        tree->output();
}

template<class T>
bool AvlSet<T>::TreeNode::isAvl() {
    int curBalance = getBalance();
    return curBalance > -2 && curBalance < 2 && (leftSon == nullptr || leftSon->isAvl()) && (rightSon == nullptr || rightSon->isAvl());
}

template<class T>
bool AvlSet<T>::isAvl() {
    return tree == nullptr || tree->isAvl();
}

#endif