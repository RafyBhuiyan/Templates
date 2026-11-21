#include<bits/stdc++.h>
using namespace std;

// Offline, 1-based inclusive rectangles. Apply all updates, then build once before querying.
struct PrefixSum2D {
    int rows, cols;
    vector<vector<long long>> grid;
    PrefixSum2D(int n,int m) : rows(n),cols(m),grid(n+2,vector<long long>(m+2)) {}
    void add(int x1,int y1,int x2,int y2,long long delta) {
        grid[x1][y1]+=delta; grid[x2+1][y1]-=delta;
        grid[x1][y2+1]-=delta; grid[x2+1][y2+1]+=delta;
    }
    void build() {
        // First integrate the differences into cells, then integrate cells into sums.
        for (int pass=0;pass<2;++pass)
            for (int i=1;i<=rows;++i) for (int j=1;j<=cols;++j)
                grid[i][j]+=grid[i-1][j]+grid[i][j-1]-grid[i-1][j-1];
    }
    long long query(int x1,int y1,int x2,int y2) const {
        return grid[x2][y2]-grid[x1-1][y2]-grid[x2][y1-1]+grid[x1-1][y1-1];
    }
};
int main() {
    int n,m; cin >> n >> m;
    PrefixSum2D sums(n,m);
    for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
        int x; cin>>x; sums.add(i,j,i,j,x);
    }
    sums.build();
    int q; cin>>q;
    while(q--) {
        int a,b,c,d; cin>>a>>b>>c>>d;
        cout<<sums.query(a,b,c,d)<<'\n';
    }
}
