#include <bits/stdc++.h>
using namespace std;

// Matrix i has dimensions p[i] x p[i+1]. split[i][j] reconstructs the optimal brackets.
long long matrix_chain(const vector<int>& p, vector<vector<int>>& split) {
    int n = max(0,(int)p.size()-1);
    vector<vector<long long>> cost(n,vector<long long>(n));
    split.assign(n,vector<int>(n,-1));
    for(int len=2;len<=n;++len) for(int l=0;l+len<=n;++l) {
        int r=l+len-1;
        cost[l][r]=LLONG_MAX;
        for(int k=l;k<r;++k) {
            long long v=cost[l][k]+cost[k+1][r]+1LL*p[l]*p[k+1]*p[r+1];
            if(v<cost[l][r]) { cost[l][r]=v; split[l][r]=k; }
        }
    }
    return n ? cost[0][n-1] : 0;
}
