
template <class Elem>
class BoundedStackAgregatingArray: public Stack
{
private:
    static const int bos; //bottom of stack
    int _top;
    Array<Elem> stackArray;

public:
    class BadStack{};
    explicit BoundedStack(int size):
        stackArray(size),_top(bos){};
    bool empty() const
        {return _top==bos;}
    bool full() const
        {return _top==stackArray.size()-1;}
    const Elem& top() const
        {return stackArray[_top];}
    void pop()
    {
        if (empty())
            throw BadStack();
        _top--;
    }
    void push(const Elem& value)
    {
        if (full())
            throw BadStack();
        stackArray[++_top]=value;
    }
//delegating:
    int size() const
        {return stackArray.size();}
};
const int BoundedStack::bos=-1;

