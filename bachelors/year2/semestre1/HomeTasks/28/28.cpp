#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits.h>
#include <algorithm>
#include <iterator>

using namespace std;

void bucket_sort(vector<int>& arr) {
    if (arr.size() < 30) {
        sort(arr.begin(), arr.end());
        return;
    }
    vector<vector<int>> buckets;
    buckets.resize(arr.size() + 1);
    int minn = arr[0], maxx = arr[0];
    //find min and max values - interval bounds
    for (int i : arr) {
        minn = min(minn, i);
        maxx = max(maxx, i);
    }
    //get length of one interval
    int delta = max(1, static_cast<int>((maxx - minn) / arr.size()));
    //add each element to corresponding bucket
    while (!arr.empty()) {
        buckets[(arr.back() - minn) / delta].push_back(arr.back());
        arr.pop_back();
    }
    //sort each bucket and add to resulting array
    for (auto &i : buckets) {
        bucket_sort(i);
        //sort(i.begin(), i.end());
        arr.insert(arr.end(), i.begin(), i.end());
        i.clear();
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<int> a(100);
    generate(a.begin(), a.end(), rand);
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, " ")); cout << endl;
    bucket_sort(a);
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, " ")); cout << endl;
    return 0;
}
