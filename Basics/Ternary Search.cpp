#include <bits/stdc++.h>
using namespace std;

// Argmax of a unimodal real-valued function on [l,r].
template<class F> long double ternary_search(long double l,long double r,F fun) {
    for(int i=0;i<160;++i) {
        long double a=l+(r-l)/3,b=r-(r-l)/3;
        if(fun(a)<fun(b)) l=a; else r=b;
    }
    return (l+r)/2;
}
