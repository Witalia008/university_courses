class List;

class ListIterator
{
    bool start;
    List::Node * _first;
    List::Node * _current;
public:
    void begin(List*);
    char get();
    void next();
    bool end();
};

