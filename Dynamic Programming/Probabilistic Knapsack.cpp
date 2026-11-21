#include <bits/stdc++.h>
using namespace std;

// Best survival probability for each exact total. Each item may be chosen once.
vector<double> survival_probabilities(const vector<int>& money, const vector<double>& risk, int target) {
    vector<double> dp(target+1);
    dp[0]=1;
    for(size_t i=0;i<money.size();++i)
        for(int sum=target;sum>=money[i];--sum)
            dp[sum]=max(dp[sum],dp[sum-money[i]]*(1-risk[i]));
    return dp;
}
