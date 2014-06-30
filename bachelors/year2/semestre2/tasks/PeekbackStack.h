template <class Elem>
class PeekbackStack : public BoundedStackDerivedArray
{
public:
    PeekbackStack(int size):BoundedStackDerivedArray (size){};
    bool PeekbackStack::peekback(int, Elem&) const;
};
