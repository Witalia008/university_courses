#ifndef _SortPack_h_
#define _SortPack_h_
class ArrayOfItems;
class SortedItems;
class IntToSort;
class SortPack
{
    ArrayOfItems * items;
    int quantity;
    int counter;
public:
    SortPack():counter(0){};
    void bubble();
    void select();
    void insert();
    void shell();
    void quick();
    void attach(ArrayOfItems&, int);
    void show();
    void discardCounter();
    void increaseConter();

};
class ArrayOfItems
{
public:
    virtual SortedItems& operator[](int)=0;
    virtual void fill()=0;
    virtual void show()=0;
};
class ArrayOfInt:public ArrayOfItems
{
    IntToSort* arrayToSort;
    int length;
public:     
    ArrayOfInt(int);
    ~ArrayOfInt();
    SortedItems& operator[](int);
    void fill();
    void show();
};
class SortedItems
{
public:
    virtual bool operator<(const SortedItems&) const=0;
    virtual void showItem()=0;

};
class IntToSort: public SortedItems
{
    int value;
public:
    IntToSort(){};
    IntToSort(int i):value(i){};
    bool operator<(const SortedItems&) const;
    void showItem();
};
#endif