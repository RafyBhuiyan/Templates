#include <bits/stdc++.h>
using namespace std;

// Start with d[i][i]=0, the best direct edge for each pair, and inf for missing edges.
void floyd_warshall(vector<vector<long long>>& d,long long inf) {
    int n=d.size();
    for(int k=0;k<n;++k) for(int i=0;i<n;++i) if(d[i][k]!=inf)
        for(int j=0;j<n;++j) if(d[k][j]!=inf)
            d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
