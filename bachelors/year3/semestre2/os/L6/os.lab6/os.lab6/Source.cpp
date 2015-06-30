#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>

#include "FS.h"

using namespace std;

FS fs;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string cmd;
    fs.init(nullptr);
    for (int id = 0; !cin.eof(); ++id)
    {
        string s;
        getline(cin, s);
        if (s == "")
        {
            cout << endl;
            continue;
        }
        istringstream iss(s);
        iss >> cmd;
        if (cmd == "in") // restore disk's state or create new
        {
            cmd = "";
            iss >> cmd;
            if (cmd == "")
            {
                fs.init(nullptr);
                cout << "disk initialized" << endl;
            }
            else
            {
                fs.init(cmd.c_str());
                cout << "disk restored" << endl;
            }
        }
        else if (cmd == "sv") //save disk's state
        {
            iss >> cmd;
            fs.save(cmd.c_str());
            cout << "disk saved" << endl;
        }
        else if (cmd == "cr") // create new file
        {
            string name;
            iss >> name;
            char *err = fs.create((char *)name.c_str());
            if (err == nullptr)
            {
                cout << name << " created" << endl;
            }
            else
            {
                cout << "error " << string(err) << endl;
            }
        }
        else if (cmd == "de") // delete file
        {
            string name;
            iss >> name;
            char *err = fs.destroy((char *)name.c_str());
            if (err == nullptr)
            {
                cout << name << " destroyed" << endl;
            }
            else
            {
                cout << "error " << string(err) << endl;
            }
        }
        else if (cmd == "op") // open file
        {
            string name;
            iss >> name;
            int id = fs.open((char *)name.c_str());
            if (id > 0)
            {
                cout << name << " opened " << id << endl;
            }
            else
            {
                cout << "error " << id << endl;
            }
        }
        else if (cmd == "cl") // close file
        {
            int index;
            iss >> index;
            char *err = fs.close(index);
            if (err == nullptr)
            {
                cout << index << " closed" << endl;
            }
            else
            {
                cout << "error " << string(err) << endl;
            }
        }
        else if (cmd == "rd") // read
        {
            int index, count;
            iss >> index >> count;
            unsigned char *buff = new unsigned char[count + 1];
            int nr = fs.read(index, buff, count);
            for (int i = 0; i < nr; ++i)
                if (!buff[i])
                    buff[i] = buff[0];
            if (nr == -1)
            {
                cout << "error" << endl;
            }
            else
            {
                buff[nr] = 0;
                cout << string((char *)buff) << endl;
            }
            delete[] buff;
        }
        else if (cmd == "wr") // write
        {
            int index, count;
            char val;
            iss >> index >> val >> count;
            unsigned char *buff = new unsigned char[count];
            for (int i = 0; i < count; ++i)
                buff[i] = val;
            int wr = fs.write(index, buff, count);
            if (wr == -1)
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wr << " bytes written" << endl;
            }
        }
        else if (cmd == "sk") // seek
        {
            int index, pos;
            iss >> index >> pos;
            char *err = fs.lseek(index, pos);
            if (err == nullptr)
            {
                cout << "position is " << pos << endl;
            }
            else
            {
                cout << "error " << string(err) << endl;
            }
        }
        else if (cmd == "dr") // get directory content
        {
            char *cont = fs.directory();
            cout << string(cont) << endl;
        }
        else
        {
            cout << s << " " << cmd << endl;
            cout << "command unrecognized" << endl;
        }
    }
    return 0;
}