#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <vector>
#include <iostream>

using namespace std;

class DataHandler
{
protected:
    vector<char> _data;
    int _len;
    int _pos;
public:
    DataHandler();
    DataHandler(vector<char>, bool);
    int setData(vector<char>);
    vector<char> getData();
    vector<char> getSendData();
    void push_back(vector<char>);
    int length() { return _len; }
    int realLength() { return _data.size(); }
    void setPos(int pos) { _pos = pos; }
    void push_back(int);
    int getInt();
    char getChar() { return _data[_pos++]; }
    int getByte() { return ((int(_data[_pos++]) + 255) % 255); }
};

#endif // DATAHANDLER_H
