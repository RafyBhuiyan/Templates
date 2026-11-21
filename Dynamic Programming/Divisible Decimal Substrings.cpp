#include <bits/stdc++.h>
using namespace std;

long long divisible_substrings(const string& s, int d, bool allow_leading_zero=true) {
    assert(d>0);
    vector<long long> dp(d), next(d);
    long long ans=0;
    for(char c:s) {
        int x=c-'0';
        fill(next.begin(),next.end(),0);
        ++next[x%d];
        for(int r=0;r<d;++r) next[(10LL*r+x)%d]+=dp[r];
        ans+=next[0];
        if (!allow_leading_zero && !x) --next[0];
        dp.swap(next);
    }
    return ans;
}
