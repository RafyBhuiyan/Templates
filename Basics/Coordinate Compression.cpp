#include <bits/stdc++.h>
using namespace std;

template<class T>
struct CoordinateCompression {
    vector<T> values;
    explicit CoordinateCompression(vector<T> v) : values(move(v)) {
        sort(values.begin(),values.end());
        values.erase(unique(values.begin(),values.end()),values.end());
    }
    int index(const T& x) const { return lower_bound(values.begin(),values.end(),x)-values.begin(); }
};
