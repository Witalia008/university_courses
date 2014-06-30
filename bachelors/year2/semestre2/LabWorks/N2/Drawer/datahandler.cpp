#include "datahandler.h"

DataHandler::DataHandler()
{
    _pos = 0;
}

DataHandler::DataHandler(vector<char> data, bool hasLen)
{
    if (hasLen && data.size() >= 4) {
        _len = 0;
        for (int i = 3; i >= 0; --i)
            _len = (_len << 8) | ((int(data[i]) + 255) % 255);
        data.erase(data.begin(), data.begin() + 4);
    }
    setData(data);
    _pos = 0;
}

int DataHandler::setData(vector<char> data)
{
    _data = data;
    return _data.size();
}

vector<char> DataHandler::getData()
{
    return _data;
}

vector<char> DataHandler::getSendData()
{
    vector<char> res;
    int x = _data.size();
    for (int i = 0; i < 4; ++i, x >>= 8)
        res.push_back(x & ((1 << 8) - 1));
    res.insert(res.end(), _data.begin(), _data.end());
    return res;
}

void DataHandler::push_back(vector<char> data)
{
    _data.insert(_data.end(), data.begin(), data.end());
}

void DataHandler::push_back(int data)
{
    for (int i = 0; i < 4; ++i, data >>= 8)
        _data.push_back(data & ((1 << 8) - 1));
}

int DataHandler::getInt()
{
    int res = 0;
    for (int i = 3; i >= 0; --i)
        res = (res << 8) | ((int(_data[_pos + i]) + 255) % 255);
    _pos += 4;
    return res;
}
