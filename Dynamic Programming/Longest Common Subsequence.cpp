#include <bits/stdc++.h>
using namespace std;

string lcs(const string& a,const string& b) {
    int n=a.size(),m=b.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1));
    for(int i=1;i<=n;++i) for(int j=1;j<=m;++j)
        dp[i][j] = a[i-1]==b[j-1] ? 1+dp[i-1][j-1] : max(dp[i-1][j],dp[i][j-1]);
    string result;
    while(n && m) {
        if(a[n-1]==b[m-1]) { result+=a[--n]; --m; }
        else if(dp[n-1][m]>=dp[n][m-1]) --n;
        else --m;
    }
    reverse(result.begin(),result.end());
    return result;
}
