#include "head.h"
#include "game.h"

#define DEBUG

void greet ()
{
    ifstream f ("greet.txt");
    while (!f.eof())
    {
        string s;
        getline (f, s);
        cout << s << endl;
    }
    f.close();
}

void sleep (double dt)
{
    dt *= 1000;
    clock_t st = clock();
    while (double(clock() - st) < dt) ;
}

typedef step (*pfunc) (Matr&, Matr&);
typedef pair<string, int> psi;

Matr A[2], B[2];
pfunc player[2];
int score[2];
vector<step> steps, possible;
string names[2];
pfunc penalty[2];
int curpl;
bool started, finished = true;
vector<psi> stands;
fstream f;
string sx, alph;

bool cmp (psi a, psi b)
{
    if (a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

void out_matrs (Matr a, Matr b)
{
    cout << "Players matrix\n";
    out_matrix(a);
    cout << "Opponent matrix\n";
    out_matrix(b);
}

void showst()
{
    int dt;
    cout << "Enter interval if you would like automatic watch or -1 if step by step\n";
    cout << "If you choose step by step every time press 'Enter'\n";
    cin >> dt;
    bool fl = 0;
    cout << "If you want watch changes with matrixes enter 1, else 0.\n";
    cin >> fl;
    if (dt < 0) getline (cin, sx);
    Matr C[2]; C[0] = B[0]; C[1] = B[1];
    out_matrs(C[0], C[1]);
    for (int i = 0; i < steps.size();)
    {
        out_step(steps[i]);
        if (fl && steps[i].i1 != -1)
        {
            do_step(C[steps[i].pl], C[1-steps[i].pl], steps[i]);
            out_matrs(C[steps[i].pl], C[1-steps[i].pl]);
        }
        if (dt >= 0)
        {
            sleep(dt); i++;
        } else {
            getline(cin, sx);
            i++;
        }
    }
    sleep(3);
}

int main ()
{
    greet ();
    int n;
    f.open("standings.txt", fstream::in);
    f >> n;
    stands.resize(n);
    REP(i, n)
        f >> stands[i].first >> stands[i].second;
    f.close();

    string s;
    for (cin >> s; s != "exit"; cin >> s)
    {
        if (s == "start")
        {
            string mode;
            cout << "Enter mode of game, two symbols. For first and second players respectively. 1 - human, 2 - machine\n";
            cin >> mode;
            REP(i, 2)
            {
                player[i] = (mode[i] == '1' ? human : machine);
                penalty[i] = (mode[i] == '1' ? human_penalty : machine_penalty);
            }
            
            cout << "Enter width and height of tables.\n";
            cin >> A[0].n >> A[0].m;
            A[1].n = A[0].n; A[1].m = A[0].m;
            
            cout << "Enter alphabet.\n";
            cin >> alph;

            //generate matrixes
            /*
            srand (time (NULL));
            gen_matrix (A[0], alph);
            gen_matrix (A[1], alph);
            refresh (A[0], A[1]);
            */
            gen_matrs(A[0], A[1], alph, 4);
            B[0] = A[0]; B[1] = A[1];
            //start game
            curpl = 0; started = true; finished = false;
            steps.clear(); CLR(score, 0);
            //f = gen_matrix;
        } else 
        if (s == "showst")
        {
            if (steps.size()) showst();
        } else
        if (s == "stands")
        {
            REP(i, stands.size())
                cout << stands[i].first << "\t " << stands[i].second << "\t\n"; 
        }
        while (true)
        {
            if (!possible.size())
                possible = all_variants(A[curpl], A[1 - curpl]);
            if (!possible.size())
                finished = true;

            cout << "History of steps:\n";
            if (steps.size() > 1) out_step(steps[steps.size() - 2]);
            if (steps.size()) out_step(steps.back());

            cout << "Your matrix player " << curpl+1 << ":\n";
            out_matrix(A[curpl]);
            cout << "Matrix of your opponent:\n";
            out_matrix(A[1 - curpl]);
            if (finished) break;
            
            if (steps.size() > 2)
                if (steps.back().str == steps[steps.size() - 2].str)
                {
                    step ao;
                    do {
                        ao = penalty[curpl](A[curpl], A[1-curpl]);
                    } while (!do_penalty (A[1-curpl], ao));
                    steps.push_back(ao);
                    possible.clear();
                    continue;
                }

            step cc = player[curpl](A[curpl], A[1 - curpl]);
            cc.pl = curpl;
            if (cc.str == "finish")
            {
                finished = true;
            } else 
            if (cc.str == "showps")
            {                
                out_step(possible[rand() % possible.size()]);
                sleep(3);
            } else
            if (cc.str == "showst")
            {
                showst();
            } else {
                if (!do_step(A[curpl], A[1 - curpl], cc))
                    cout << "Wrong step!!\n";
                else {
                    steps.push_back(cc);
                    score[curpl] += cc.str.length();
                    curpl = 1 - curpl;
                    possible.clear();
                }
            }
        }
        if (finished && started)
        {
            cout << "Results:\n";
            cout << "Player 1: " << score[0] << endl;
            cout << "Player 2: " << score[1] << endl;
            if (score[0] == score[1])
                cout << "Draw.\n";
            else
                cout << "Player " << (score[0] > score[1] ? 1 : 2) << ", you won!!!!! Congratulations.\n";
            cout << "Enter your names, player 1 and 2 respectively\n";
            cin >> names[0] >> names[1];
            REP(i, 2)
                stands.push_back(mp(names[i], score[i]));
            finished = started = false;
            cout << "FINISHED\n";
        }
    }

    sort (stands.begin(), stands.end(), &cmp);
    f.open("standings.txt", fstream::out);
    f << stands.size() << endl;
    REP(i, stands.size())
        f << stands[i].first << " " << stands[i].second << endl;
    f.close();
    return 0;
}