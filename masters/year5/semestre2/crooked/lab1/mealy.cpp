#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <memory.h>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <queue>
#include <stack>
#include <complex>
#include <limits.h>

#define Cpp11
#ifdef Cpp11
#include <cassert>
#include <chrono>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <valarray>
using namespace std::chrono;
#endif
using namespace std;

typedef double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

//const int mx[4] = { 1, 0, -1, 0 };
//const int my[4] = { 0, 1, 0, -1 };

const int Inf = 1000000000;
const int Mi = 1000000007;
const int N = 105;
const int M = 100005;
//const int K = 20;
const ld eps = 10e-7;
const ld PI = 2 * acos(0.0);
const ll InfLL = ll(Inf) * ll(Inf);

unsigned rand16() { return rand() % (1 << 16); }
unsigned rand32() { return (rand16() << 16) + rand16(); }
ull rand64() { return (((ull)rand32()) << 32) + rand32(); }
int rand(int L, int R)
{
    if (L > R)
        return R;
    return rand32() % (R - L + 1) + L;
}
ld random(ld L, ld R) { return rand(ceil((L - eps) * 100), floor((R + eps) * 100)) / 100.0; }

ll Abs(ll a) { return a < 0 ? -a : a; }
ll sqr(ll a) { return a * a; }
ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }

string toStr(int n)
{
    char s[100];
    sprintf(s, "%d", n);
    return string(s);
}

class Minimiser;

class Mealy
{
    int n, st, ot;
    unordered_map<int, map<string, pair<int, string>>> table;
    unordered_set<string> inputs, outputs;
    vector<int> states;

public:
    void read();
    void output();
    bool exists(int i, string st, bool everything = false)
    {
        return table.count(i) > 0 && table[i].count(st) > 0 &&
               (!everything || table[i][st].first != -1 && table[i][st].second != "-");
    }
    void spead_indeter();
    void remove_unreachable();
    void remove_state(int i);
    void remove_without_output();

    friend class Minimiser;
};

void Mealy::read()
{
    cin >> n >> st >> ot;
    for (int i = 0; i < n; ++i)
        states.push_back(i);
    for (int i = 0; i < st + ot; ++i)
    {
        string s;
        cin >> s;
        (i < st ? inputs : outputs).insert(s);
    }
    for (int i = 0; i < st; ++i)
    {
        vector<int> nxt(n);
        vector<string> out(n);
        string s;
        cin >> s;
        for (auto &j : nxt)
            cin >> j;
        for (auto &j : out)
            cin >> j;
        for (int j = 0; j < n; ++j)
        {
            if (nxt[j] != -1 || out[j] != "-")
            {
                table[j][s] = make_pair(nxt[j], out[j]);
            }
        }
    }
}

void Mealy::output()
{
    cout << n << " " << st << " " << ot << endl;
    for (auto &i : inputs)
        cout << i << " ";
    cout << endl;
    for (auto &i : outputs)
        cout << i << " ";
    cout << endl;
    for (auto &st : inputs)
    {
        cout << st << endl;
        for (int i : states)
            cout << (exists(i, st) ? table[i][st].first : -1) << " ";
        cout << endl;
        for (int i : states)
            cout << (exists(i, st) ? table[i][st].second : "-") << " ";
        cout << endl;
    }
    cout << "states:" << endl;
    for (int i : states)
        cout << i << " ";
    cout << endl
         << endl;
}

void Mealy::remove_state(int i)
{
    auto it = find(states.begin(), states.end(), i);
    if (it == states.end())
        return;
    states.erase(it);
    --n;
    table.erase(i);
    for (string x : inputs)
    {
        for (int j : states)
        {
            if (exists(j, x) && table[j][x].first == i)
            {
                table[j].erase(x);
            }
        }
    }
}

void Mealy::spead_indeter()
{
    for (auto i : table)
    {
        for (auto &j : i.second)
        {
            if (j.second.second == "-")
            {
                j.second.first = -1;
            }
        }
    }
}

void Mealy::remove_unreachable()
{
    vector<bool> used(n, false);
    queue<int> q;
    q.push(states[0]);
    used[states[0]] = true;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (string x : inputs)
        {
            if (exists(v, x, true) && !used[table[v][x].first])
            {
                q.push(table[v][x].first);
                used[table[v][x].first] = true;
            }
        }
    }
    for (int i = used.size() - 1; i >= 0; --i)
    {
        if (!used[i])
        {
            remove_state(i);
        }
    }
}

void Mealy::remove_without_output()
{
    for (int i : vector<int>(states))
    {
        if (table.count(i) == 0 || table[i].size() == 0)
        {
            remove_state(i);
        }
    }
}

class Minimiser
{
    typedef unordered_set<int> cls_type;

    Mealy machine;
    unordered_map<int, vector<string>> reactions;
    vector<cls_type> classes;

    bool compatible(vector<string> r1, vector<string> r2);
    void calcReactions();
    void calcInitClasses();
    bool splitClasses();
    bool shouldSplitClass(cls_type cls, string s);
    vector<cls_type> splitClass(cls_type cls, string s);
    void moveInitClsToFront();
    decltype(machine.table) calc_result_table();

public:
    Mealy minimise(Mealy machine);
};

bool Minimiser::compatible(vector<string> r1, vector<string> r2)
{
    for (int i = 0; i < r1.size(); ++i)
    {
        if (r1[i] != "-" && r2[i] != "-" && r1[i] != r2[i])
        {
            return false;
        }
    }
    return true;
}

void Minimiser::calcReactions()
{
    for (int i : machine.states)
    {
        reactions[i] = {};
        for (string x : machine.inputs)
        {
            reactions[i].push_back(machine.exists(i, x) ? machine.table[i][x].second : "-");
        }
    }
}

void Minimiser::calcInitClasses()
{
    for (int i : machine.states)
    {
        bool ofClass = false;
        auto reaction = reactions[i];
        for (auto &cls : classes)
        {
            if (all_of(cls.begin(), cls.end(), [this, &reaction](int st) {
                    return this->compatible(this->reactions[st], reaction);
                }))
            {
                cls.insert(i);
                ofClass = true;
            }
        }
        if (!ofClass)
        {
            cls_type cls = {i};
            for (int j : machine.states)
            {
                if (j == i)
                    break;
                if (compatible(reactions[j], reaction))
                {
                    cls.insert(j);
                }
            }
            classes.emplace_back(cls);
        }
    }
}

bool Minimiser::shouldSplitClass(cls_type cls, string s)
{
    vector<int> nxtStates;
    for_each(cls.begin(), cls.end(), [&](int st) {
        if (this->machine.exists(st, s, true))
        {
            nxtStates.push_back(this->machine.table[st][s].first);
        }
    });
    return !nxtStates.empty() && all_of(classes.begin(), classes.end(), [&](cls_type cls) {
        for (int i : nxtStates)
        {
            if (find(cls.begin(), cls.end(), i) == cls.end())
            {
                return true;
            }
        }
        return false;
    });
}

vector<Minimiser::cls_type> Minimiser::splitClass(cls_type cls, string s)
{
    cls_type nextClasses;
    unordered_map<int, cls_type> prevStateNxtClass;
    for (int prevState : cls)
    {
        int nxtState = machine.exists(prevState, s) ? machine.table[prevState][s].first : -1;
        cls_type nxt;
        for (int i = 0; i < classes.size(); ++i)
        {
            if (nxtState == -1 || find(classes[i].begin(), classes[i].end(), nxtState) != classes[i].end())
            {
                nextClasses.insert(i);
                nxt.insert(i);
            }
        }
        prevStateNxtClass[prevState] = nxt;
    }
    vector<cls_type> result;
    for (int nxtCls : nextClasses)
    {
        cls_type triggerStates;
        for_each(prevStateNxtClass.begin(), prevStateNxtClass.end(), [&](pair<int, cls_type> pr) {
            if (find(pr.second.begin(), pr.second.end(), nxtCls) != pr.second.end())
            {
                triggerStates.insert(pr.first);
            }
        });
        result.push_back(triggerStates);
    }
    return result;
}

bool Minimiser::splitClasses()
{
    bool changed = false;
    vector<cls_type> new_classes;

    for (auto &cls : classes)
    {
        vector<cls_type> replace;
        for (string st : machine.inputs)
        {
            if (shouldSplitClass(cls, st))
            {
                changed = true;
                auto cur = splitClass(cls, st);
                replace.insert(replace.end(), cur.begin(), cur.end());
            }
        }
        if (replace.size())
        {
            new_classes.insert(new_classes.end(), replace.begin(), replace.end());
        }
        else
        {
            new_classes.emplace_back(cls);
        }
    }

    classes = new_classes;

    return changed;
}

void Minimiser::moveInitClsToFront()
{
    for (auto &cls : classes)
    {
        if (find(cls.begin(), cls.end(), 0) != cls.end())
        {
            swap(cls, classes[0]);
        }
    }
}

auto Minimiser::calc_result_table() -> decltype(machine.table)
{
    decltype(machine.table) new_table;
    for (string x : machine.inputs)
    {
        for (int i = 0; i < classes.size(); ++i)
        {
            vector<int> nxtStates;
            for (int j : classes[i])
            {
                if (machine.exists(j, x, true))
                {
                    nxtStates.push_back(machine.table[j][x].first);
                }
            }
            new_table[i][x] = make_pair(-1, "-");
            if (!nxtStates.empty())
            {
                int clsRes = -1;
                for (int j = 0; j < classes.size(); ++j)
                {
                    bool containsAll = true;
                    for_each(nxtStates.begin(), nxtStates.end(), [&](int st) {
                        containsAll &= find(classes[j].begin(), classes[j].end(), st) != classes[j].end();
                    });
                    if (containsAll && (new_table[i][x].first == -1 || classes[new_table[i][x].first].size() < classes[j].size()))
                    {
                        new_table[i][x].first = j;
                    }
                }
            }
            auto st = find_if(classes[i].begin(), classes[i].end(), [&](int st_id) {
                return machine.exists(st_id, x) && machine.table[st_id][x].second != "-";
            });
            if (st != classes[i].end())
            {
                new_table[i][x].second = machine.table[*st][x].second;
            }
        }
    }
    return new_table;
}

Mealy Minimiser::minimise(Mealy machine)
{
    this->machine = machine;
    calcReactions();
    calcInitClasses();
    while (splitClasses())
    {
        auto new_classes = classes;
        classes.clear();
        for (auto cls : new_classes)
        {
            if (find_if(classes.begin(), classes.end(), [cls](cls_type i) {
                    for (auto x : cls)
                    {
                        if (i.count(x) == 0)
                        {
                            return false;
                        }
                    }
                    return cls.size() == i.size();
                }) == classes.end())
            {
                classes.push_back(cls);
            }
        }
    }
    moveInitClsToFront();
    Mealy result;
    result.inputs = machine.inputs;
    result.outputs = machine.outputs;
    result.ot = machine.ot;
    result.st = machine.st;
    result.table = calc_result_table();
    result.n = result.table.size();
    for (int i = 0; i < result.n; ++i)
        result.states.push_back(i);
    return result;
}

//#define ONLINE_JUDGE
int main()
{
    std::ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Mealy machine;
    machine.read();
    // heuristics
    machine.spead_indeter();
    machine.remove_unreachable();
    machine.remove_without_output();
    cout << "After heuristic:" << endl;
    machine.output();
    // algo
    machine = Minimiser().minimise(machine);
    machine.remove_unreachable();
    cout << "Resulting:" << endl;
    machine.output();
    return 0;
}
