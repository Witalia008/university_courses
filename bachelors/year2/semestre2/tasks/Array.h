
template <class Elem>
class Array
{
public:
    Array (int sz=defaultArraySize);
    Array (const Array&);
    ~Array() {delete []ia;}

    bool operator== (const Array&) const;
    bool operator!= (const Array&) const;

    Array& operator= (const Array&);
    Elem& operator[] (int index);
//    ���������� ������������ �������� ������
//    ��� ��������� �������
//    Elem BoundedStack::top() const
    Elem& operator[] (int index) const;

    int size() const;
    
private:
    int _size;
    Elem *ia;
    static const int defaultArraySize;
    void init(int sz, Elem* array);
};

const int IntArray::defaultArraySize=256;
