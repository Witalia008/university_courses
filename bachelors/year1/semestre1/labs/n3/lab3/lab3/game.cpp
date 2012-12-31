#include "game.h"

void gen_matrs (Matr & a, Matr &b, string alph, int hm)
{
    if (hm < 0 || hm > 10) return;
    srand(time(NULL));
    a.a.clear(); b.a.clear();
    a.a.resize(a.n * a.m);
    b.a.resize(b.n * b.m);
    int cnt = rand() % (a.n * a.m * (hm - 1) + 1) + a.n * a.m;
    int pa = a.n * a.m, pb = b.n * b.m;
    int cnt1 = 0;
    REP(i, alph.length())
    {
        int fora = rand () % (cnt - alph.length() + i + 1) + 1;
        if (i == alph.length() - 1) fora = cnt;
        cnt -= fora;
        int delt = rand() % 9 - 4;
        int forb = max (fora + delt, 1);
        if (cnt1 + forb > b.n * b.m * hm - alph.length() + i + 1)
            forb = max (fora - 4, 1);
        cnt1 += forb;
        REP(j, fora)
            put_letter (a, alph[i], hm);
        REP(j, forb)
            put_letter (b, alph[i], hm);
    }
    REP(i, a.a.size())
        random_shuffle(a.a[i].begin(), a.a[i].end());
    REP(i, b.a.size())
    {
        if (!b.a[i].length())
            b.a[i] += alph[rand() % alph.length()];
        random_shuffle(b.a[i].begin(), b.a[i].end());
    }
}

bool put_letter (Matr &a, char q, int hm)
{
    int whi, whj;
    whi = whj = -1;
    REP(i, a.n)
        REP(j, a.m)
            if (!a.a[i * a.m + j].length())
                whi = i, whj = j;
    if (whi == -1)
    {
        do {
            whi = rand() % a.n;
            whj = rand() % a.m;
        } while (a.a[whi * a.m + whj].length() >= hm);
    }
    return add_letter (a, whi, whj, q, hm);
}

bool find_letter (Matr a, char q)
{
    REP(i, a.a.size())
        REP(j, a.a[i].length())
            if (a.a[i][j] == q)
                return true;
    return false;
}

void gen_matrix (Matr & a, string alph)
{
    a.a.clear();
    a.a.resize(a.n * a.m);
    vector<int> used(alph.size(), 0);
    REP(i, a.a.size())
    {
        int len = rand() % 10 + 1;
        REP(j, len)
        {
            int pos = rand() % alph.length();
            a.a[i] += alph[pos];
            ++used[pos];
        }
    }
    REP(i, alph.size())
        if (!used[i])
        {
            REP(j, alph.size())
                if (used[j] > 1)
                {
                    change_letter(a, alph[i], alph[j]);
                    used[j]--; used[i]++;
                    break;
                }
        }
}

void change_letter (Matr &a, char from, char to)
{
    REP(i, a.a.size())
        REP(j, a.a[i].length())
            if (a.a[i][j] == from)
            {
                if (!to)
                    a.a[i].erase(j, 1);
                else
                    a.a[i][j] = to;
                return;
            }
}

bool add_letter (Matr &a, int i, int j, char q, int hm)
{
    if (i == -1 && j == -1)
    {
        for (i = 0; i < a.a.size(); ++i)
            if (a.a[i].length() < hm)
                break;
        if (i == a.a.size()) return false;
    } else i = i * a.m + j;
    a.a[i] += q;
    return true;
}

void out_matrix (Matr a)
{
    REP(i, a.n)
    {
        cout << i << " - ";
        REP(j, a.m)
        {
            cout << j << ":" << a.a[i * a.m + j];
            REP(k, 10 - a.a[i * a.m + j].length() + 2)
                cout << " ";
        }
        cout << endl;
    }
    cout << "\n\n";
}

void refresh (Matr &a, Matr &b)
{
    int ca [N], cb[N];
    CLR(ca, 0); CLR(cb, 0);
    REP(i, a.a.size())
        REP(j, a.a[i].length())
            ca[a.a[i][j]]++;
    REP(i, b.a.size())
        REP(j, b.a[i].length())
            cb[b.a[i][j]]++;
    REP(i, N)
        if (Abs(ca[i] - cb[i]) > 4)
        {
            int et = 0;
            REP(j, N)
                if (ca[j] - cb[j] && (ca[i] - cb[i]) * (ca[j] - cb[j]) < 0)
                {
                    et = ca[j] - cb[j];
                    while (Abs(ca[i] - cb[i]) > 4 && (ca[j] - cb[j]) * et >= 0)
                    {
                        change_letter(a, i, j);
                        ca[i]--; ca[j]++;
                        change_letter(b, j, i);
                        cb[i]++; cb[j]--;
                    }
                    if (Abs(ca[i] - cb[i]) <= 4) break;
                }
            et = ca[i] - cb[i];
            while (ca[i] - cb[i] > 4)
            {
                if (add_letter(et > 0 ? b : a, -1, -1, i, 10))
                    (et > 0 ? cb : ca)[i]++;
                else {
                    change_letter((et > 0 ? a : b), i, 0);
                    (et > 0 ? ca : cb)[i]--;
                }
            }
        }
}

bool do_step (Matr &a, Matr &b, step &cur)
{
    if (cur.i1 < 0 || cur.i1 >= a.n) return false;
    if (cur.j1 < 0 || cur.j1 >= a.m) return false;
    if (cur.i2 < 0 || cur.i2 >= a.n) return false;
    if (cur.j2 < 0 || cur.j2 >= a.m) return false;
    int pos1 = cur.i1 * a.m + cur.j1, pos2 = cur.i2 * b.m + cur.j2;
    if (cur.pos1 >= 0)
    {
        if (cur.pos2 >= b.a[pos2].length() || cur.pos2 < 0 || cur.pos1 >= a.a[pos1].length() 
            || b.a[pos2][cur.pos2] != a.a[pos1][cur.pos1])
            return false;
        cur.str = ""; cur.str += a.a[pos1][cur.pos1];
        a.a[pos1].erase(cur.pos1, 1);
        b.a[pos2].erase(cur.pos2, 1);
        return true;
    }
    if (!a.a[pos1].length()) return false;
    cur.str = a.a[pos1];
    if (a.a[pos1] != b.a[pos2]) return false;
    a.a[pos1] = b.a[pos2] = "";
    return true;
}

void out_step (step a)
{
    if (a.i2 == -1)
    {
        cout << "No penalty. No possible variants.\n";
        return;
    }
    cout << "Player ";
    if (a.pl == -1 && a.i1 != -1) cout << "can set ";
    else cout << a.pl+1 << " have setted ";
    if (a.i1 != -1){
        cout << "bijections between ";
        cout << "word(letter) A[" << a.i1 << "][" << a.j1 << "] = " << a.str;
        if (a.pos1 != -1) cout << " on position " << a.pos1;
        cout << " and word(letter) B[" << a.i2 << "][" << a.j2 << "]";
        if (a.pos2 != -1) cout << " on position " << a.pos2;
    } else {
        cout << "penalty for player " << 2 - a.pl;
        cout << "(letter " << a.str << " to word B[" << a.i2 << "][" << a.j2 << "]";
    }
    cout << "\n\n";
}

step machine (Matr& a, Matr &b)
{
    vector<step> r = all_variants(a, b);
    if (r.size()) return r[0];
    return step(-1, -1, -1, -1, -1, -1, -1, "finish");
}

step human (Matr &a, Matr &b)
{
    string s;
    cout << "Enter operation you would like to do or do your step.\n"
            "To do tour step enter coordinates of your word and word of your opponent.\n"
            "And, if length of your word is 1 you can enter positions of letters of yours and opponents word you would like to delete (all in one line!!!).\n"
            "To end game enter 'finish'. To watch all steps - 'showst'. Look for possible steps - 'showps'.\n";
    cin >> s;
    REP(i, s.length())
    {
        char q = s[i];
        if ((q >= 'A' && q <= 'Z') || (q >= 'a' && q <= 'z'))
            return step(-1, -1, -1, -1, -1, -1, -1, s);
    }
    step o;
    sscanf (s.c_str(), "%d", &o.i1);
    getline (cin, s);
    o.pos1 = o.pos2 = -1;
    if (sscanf(s.c_str(), "%d%d%d%d%d", &o.j1, &o.i2, &o.j2, &o.pos1, &o.pos2) != 5)
        o.pos1 = o.pos2 = -1;
    o.str = a.a[o.i1 * a.m + o.j1];
    return o;
}

vector<step> all_variants (Matr &a, Matr &b)
{
    vector<step> res;
    res.clear();
    REP(i1, a.n)
        REP(j1, a.m)
        {
            int pos1 = i1 * a.m + j1;
            if (!a.a[pos1].length()) continue;
            REP(i2, b.n)
                REP(j2, b.m)
                {
                    int pos2 = i2 * b.m + j2;
                    REP(i, a.a[pos1].length())
                        REP(j, b.a[pos2].length())
                            if (a.a[pos1][i] == b.a[pos2][j])
                            {
                                string g = ""; g += a.a[pos1][i];
                                res.push_back(step(i1, j1, i2, j2, i, j, -1, g));
                            }
                    if (a.a[pos1] == b.a[pos2])
                        res.push_back( step(i1, j1, i2, j2, -1, -1, -1, a.a[pos1]) );
                }
        }
    return res;
}

step human_penalty (Matr &a, Matr &b)
{
    string pos = "";
    FOR(i, 'a', 'z')
        if (find_letter(a, i) && !find_letter (b, i))
            pos += i;
    cout << "Possible letters for penalty: " << pos << endl;
    cout << "Enter position of letter in list of possible ones and position where add\n";
    step o;
    cin >> o.i1 >> o.i2 >> o.j2;
    o.str = "";
    if (o.i1 >= 0 && o.i1 < pos.length())
        o.str += pos[o.i1];
    o.i1 = o.j1 = o.pos1 = o.pos2 = o.pl = -1;
    return o;
}

step machine_penalty (Matr &a, Matr &b)
{
    FOR(i, 'a', 'z')
        if (find_letter(a, i) && !find_letter (b, i))
        {
            string s = ""; s += i;
            return step(-1, -1, rand() % b.n, rand() % b.m, -1, -1, -1, s);
        }
    return step(-1, -1, -1, -1, -1, -1, -1, "no");
}

bool do_penalty (Matr &a, step o)
{
    if (o.str == "") return false;
    if (o.str == "no") return true;
    if (o.i2 < 0 || o.i2 >= a.n) return false;
    if (o.j2 < 0 || o.j2 >= a.m) return false;
    a.a[o.i2 * a.m + o.j2] += o.str;
    return true;
}