#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string find_ribs(string bents) {
    string res;
    //each bent doubles number of edges, 2^n edges in the end and 2^n-1 ribs
    res.resize((1 << bents.size()) - 1, ' ');
    int pos = 0;
    for (int i = bents.size() - 1; i >= 0; --i) {
        char cur = bents[i] == 'F' ? 'K' : 'O';
        //will go with step 2, 4, 8, ... for i = n - 1, n - 2, ...
        for (int j = pos; j < res.size(); j += (1 << (bents.size() - i))) {
            res[j] = cur;
            cur = cur == 'K' ? 'O' : 'K';
        }
        //move initial position (0, 1, 3, 7, ...)
        pos += (1 << (bents.size() - i - 1));
    }
    return res;
}

string find_bents(string ribs) {
    string res = "";
    while ((1 << res.size()) < ribs.size())
        res += ' ';
    int pos = 0;
    //restore each bent from last to first
    for (int i = res.size() - 1; i >= 0; --i) {
        res[i] = ribs[pos] == 'K' ? 'F' : 'B';
        char cur = ribs[pos];
        //go with steps 2, 4, 8 for i = n-1, n-2, ...
        for (int j = pos; j < ribs.size(); j += (1 << (res.size() - i))) {
            //should be eaqual to pattern (as in previous function)
            if (ribs[j] != cur)
                return "Impossible";
            cur = cur == 'K' ? 'O' : 'K';
        }
        //move init position (will be 0, 1, 3, ...)
        pos += (1 << (res.size() - i - 1));
    }
    return res;
}

int main () {
    freopen("output.txt", "w", stdout);
    cout << find_ribs("FBF") << endl;
    cout << find_bents("KOOKKKO") << endl;
    return 0;
}