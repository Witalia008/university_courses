#ifndef TOOLS_H
#define TOOLS_H

#include "master.h"

const int cnt_spec_symb = 5;
const int cnt_white_symbs = 3;
const int cnt_reserv = 3;
const char spec_symb[] = {'\n', '\t', '\a', '\\', '"'};
const string spec_symb_str[] = {"\\n", "\\t", "\\a", "\\\\", "\\\""};
const string reserved[] = {"if", "while", "for"};

inline long long gcd(long long a, long long b);
int rand15();
int rand30();
int rand(int, int);
double random(double, double);
string read_dig_seq(istream&);
bool check_symb(istream&, char);
string toStr(double a);
double fromStr(string a);
char prev_symb(istream&);
string next_symbs(istream&, int);
char symb_at(istream&, int);
void ignore_whitespace(istream &f);
bool is_integer(double a);
bool is_string(string a);
bool is_number(string a);
bool is_char(string a);
void del_spec_symbs(string&);
string str_to_print(string);
bool end_of_name(istream&, int);
bool reserved_name(istream&);
bool is_white_ch(char q);
#endif //TOOLS_H
