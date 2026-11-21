#include <bits/stdc++.h>
using namespace std;

int lcis(const vector<int>& a,const vector<int>& b) {
    vector<int> dp(b.size());
    for (int x : a) {
        int best=0;
        for (size_t j=0;j<b.size();++j) {
            if (b[j]<x) best=max(best,dp[j]);
            if (b[j]==x) dp[j]=max(dp[j],best+1);
        }
    }
    return dp.empty()?0:*max_element(dp.begin(),dp.end());
}
