#include "head.h"

typedef vector<string> matr;

struct Matr
{
    matr a;
    int n, m;
};

struct step
{
    int i1, j1, i2, j2, pos1, pos2, pl;
    string str;
    step () {}
    step (int _i1, int _j1, int _i2, int _j2, int _pos1, int _pos2, int _pl, string _str){
        i1 = _i1; j1 = _j1; i2 = _i2; j2 = _j2; pos1 = _pos1; pos2 = _pos2; pl = _pl; str = _str;
    }
};

void gen_matrs (Matr & a, Matr &b, string alph, int hm);

void gen_matrix (Matr& a, string alph);

void out_matrix (Matr a);

void refresh (Matr &a, Matr &b);

void change_letter (Matr &a, char from, char to); 
bool add_letter (Matr &a, int i, int j, char q, int hm);
bool put_letter (Matr &a, char q, int hm);
bool find_letter (Matr a, char q);

bool do_step (Matr &a, Matr &b, step &cur);
void out_step (step a);

step machine (Matr& a, Matr &b);
step human (Matr &a, Matr &b);

vector<step> all_variants (Matr &a, Matr &b);

step human_penalty (Matr &a, Matr &b);
step machine_penalty (Matr &a, Matr &b);

bool do_penalty (Matr &a, step o);