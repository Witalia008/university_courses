
template <class Elem>
class ProtectedArray
{
public:
    ProtectedArray (int sz=defaultProtectedArraySize);
    ProtectedArray (const ProtectedArray&);
    ~ProtectedArray() {delete []ia;}

    bool operator== (const ProtectedArray&) const;
    bool operator!= (const ProtectedArray&) const;

    ProtectedArray& operator= (const ProtectedArray&);
    Elem& operator[] (int index);
//    ���������� ������������ �������� ������
//    ��� ��������� �������
//    Elem BoundedStack::top() const
    Elem& operator[] (int index) const;

    int size() const;
protected:
    Elem *ia;    
private:
    int _size;
    static const int defaultProtectedArraySize;
    void init(int sz, Elem* ProtectedArray);
};

const int IntProtectedArray::defaultProtectedArraySize=256;
