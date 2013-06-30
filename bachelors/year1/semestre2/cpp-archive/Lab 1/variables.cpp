#include "variables.h"

const string varfile = "vars";

void toFile (VarSet all)
{
    ofstream f(varfile.c_str());
    for (int i = 0; i < all.n; ++i)
        f << all.name[i] << " " << all.value[i] << endl;
    f.close();
}

void fromFile (VarSet &all)
{
    ifstream f(varfile.c_str());
    all.n = 0;
    string s = "";
    f >> s;
    for (; s != "";)
    {
        if (all.n == all.name.size())
        {
            all.name.push_back("");
            all.value.push_back("");
        }
        all.name[all.n] = s;
        f >> all.value[all.n];
        all.n++;
        s = ""; f >> s;
    }
    f.close();
}

void chk_(string &a)
{
    if (a.find("::") == -1)
        a = "main::" + a;
}

int find_var (string _name, VarSet all)
{
    for (int i = 0; i < all.n; i++)
        if (all.name[i] == _name)
            return i;
    return -1;
}

bool add_var (string _name, string _value, VarSet &all)
{
    chk_(_name);
    if (find_var(_name, all) != -1) return false;
    all.n++;
    all.name.push_back(_name);
    all.value.push_back(_value);
    fstream f(varfile.c_str(), fstream::in | fstream::out | fstream::app);
    f << _name << " " << _value << endl;
    f.close();
    return true;
}

bool set_var (string _name, string _value, VarSet &all)
{
    int x = find_var(_name, all);
    if (x == -1) return false;
    all.value[x] = _value;
    return true;
}

bool del_var (string _name, VarSet &all)
{
    chk_(_name);
    vs::iterator it1 = all.value.begin();
    for (vs::iterator it = all.name.begin(); it != all.name.end(); it++, it1++)
        if (*it == _name)
        {
            all.name.erase(it);
            all.value.erase(it1);
            all.n--;
            return true;
        }
    return false;
}
