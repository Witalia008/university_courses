#include "tools.h"

inline long long gcd (long long a, long long b) {
    return (!b ? a : gcd (b, a % b));
}

int rand15() {
    return rand() % (1 << 15);
}

int rand30() {
    return (rand15() << 15) + rand15();
}

int rand(int L, int R) {
    if (L > R) return R;
    return rand30() % (R - L + 1) + L;
}

double random(double L, double R) {
    return rand(ceil((L - eps) * 100), floor((R + eps) * 100)) / 100.0;
}

string toStr(double a) {
    char *s = new char[100];
    sprintf(s, "%lf", a);
    string res(s);
    delete[] s;
    if (res.find(".") != -1) {
        while (res[res.size() - 1] == '0') {
            res.erase(res.size() - 1, 1);
        }
        if (res[res.size() - 1] == '.') {
            res.erase(res.size() - 1, 1);
        }
    }
    if (res == "") {
        res = "0";
    }
    return res;
}

double fromStr(string a) {
    double res = 0;
    sscanf(a.c_str(), "%lf", &res);
    return res;
}

bool check_symb(istream &f, char symb) {
    ignore_whitespace(f);
    if (f.eof() == false && f.peek() == symb) {
        f.get();
        return true;
    }
    cerr << "Not found " << symb << "!\n";
    return false;
}

string read_dig_seq(istream &f) {
    string res = "";
    while (f.eof() == false && isdigit(f.peek())) {
        res += f.get();
    }
    return res;
}

char prev_symb(istream &f) {
    do {
        f.unget();
    } while (is_white_ch(f.peek()));
    ignore_whitespace(f);
    return f.get();
}

string next_symbs(istream &f, int cnt) {
    ignore_whitespace(f);
    string res = "";
    for (int i = 0; i < cnt && f.peek() != -1; i++) {
        res += f.get();
    }
    for (int i = 0; i < res.size(); i++) {
        f.unget();
    }
    return res;
}

void ignore_whitespace(istream &f) {
    for (;f.peek() != -1;) {
        if (is_white_ch(f.peek())) {
            f.ignore(1);
        } else {
            break;
        }
    }
}

bool is_white_ch(char q) {
    bool to_ignore = (q == ' ');
    for (int i = 0; i < cnt_white_symbs; i++) {
        to_ignore |= (q == spec_symb[i]);
    }
    return to_ignore;
}

bool is_integer(double a) {
    return Abs(a - int(a)) < eps;
}

bool is_string(string a) {
    return a != "" && a[0] == '"';
}

bool is_number(string a) {
    return is_string(a) == false && a != "true" && a != "false";
}

bool is_char(string a) {
    return a != "" && a[0] == '\'';
}

void del_spec_symbs(string &a) {
    int pos;
    for (int i = 0; i < cnt_spec_symb; i++) {
        while ((pos = a.find(spec_symb_str[i])) != -1) {
            a[pos] = spec_symb[i];
            a.erase(pos + 1, spec_symb_str[i].size() - 1);
        }
    }
}

string str_to_print(string a) {
    del_spec_symbs(a);
    if (a != "" && a[0] == '"') {
        a.erase(0, 1);
    }
    if (a != "" && a[a.size() - 1] == '"') {
        a.erase(a.size() - 1, 1);
    }
    return a;
}

char symb_at(istream &f, int n) {
    char res = ' ';
    REP(i, n)
        f.get();
    res = f.get();
    REP(i, n + 1)
        f.unget();
    return res;
}

bool end_of_name(istream &f, int n) {
    char x = symb_at(f, n);
    bool res = !isalpha(x) && x != '_';
    if (!x)
        res &= !isdigit(x);
    return res;
}

bool reserved_name(istream &f) {
    for (int i = 0; i < cnt_reserv; i++)
        if (next_symbs(f, reserved[i].size()) == reserved[i] && end_of_name(f, reserved[i].size()))
            return true;
    return false;
}
