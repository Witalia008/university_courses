class List;
class CyclicList: virtual public List
{
public:
    CyclicList(char elem);
    virtual void cons(char elem);
//    virtual char head();
    virtual void pop();
};

class DoubleSidedList: virtual public List
{
    Node * prev;
public:
    DoubleSidedList(char elem):List(elem){};
    virtual void cons(char elem);
//    virtual char head();
    virtual void pop();
};

class CyclicDoubleSidedList: public DoubleSidedList, public CyclicList
{
public:
    CyclicDoubleSidedList(char elem);
    virtual void cons(char elem);
    virtual char head();
    virtual void pop();
};
