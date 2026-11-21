#include <bits/stdc++.h>
using namespace std;

// Length of a strictly increasing subsequence in O(n log n).
int lis(vector<int> const& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}
