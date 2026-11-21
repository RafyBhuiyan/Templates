#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// sum of digit till value
ll dp[20][1000][2],sz;
string v;
// take the value in string v. to_string(value) and size to sz
ll digitsum(ll curr,ll val,bool lagse)
{
    if(curr == sz) return val;
    if(dp[curr][val][lagse]!=-1) return dp[curr][val][lagse];
    ll sum = 0;
    if(lagse)
    {
        for(ll i = 0;i<v[curr] - '0';i++)
        {
            sum+=digitsum(curr+1,i+val,false);
        }
        ll x = v[curr] - '0';
        sum+=digitsum(curr+1,x + val,1);
    }
    else
    {
        for(ll i = 0;i<=9;i++)
        {
            sum +=digitsum(curr+1,i+val,lagse);
        }
    }
    return dp[curr][val][lagse] = sum;
}

// Count numbers in [0, bound] with exactly k nonzero decimal digits.
ll count_nonzero_digits(ll bound, int k) {
    if (bound < 0 || k < 0 || k > 19) return 0;
    string digits = to_string(bound);
    vector<array<ll, 2>> dp(k + 1);
    dp[0][1] = 1;
    for (char c : digits) {
        vector<array<ll, 2>> next(k + 1);
        for (int used = 0; used <= k; ++used) for (int tight : {0, 1}) {
            int limit = tight ? c - '0' : 9;
            for (int d = 0; d <= limit; ++d) {
                int count = used + (d != 0);
                if (count <= k) next[count][tight && d == limit] += dp[used][tight];
            }
        }
        dp.swap(next);
    }
    return dp[k][0] + dp[k][1];
}

// Digit-mask and remainder DP for the divisibility statistic. Call prepare() once before solve().
namespace digit_divisibility {
constexpr int mod = 1000000007;
int pw[20][20], b[1 << 10][3000], cnt[1 << 10];
vector<int32_t> memo;

vector<int> v;
int yo(int i, int mask, int rem, int f) {
  if(i == -1) return pw[b[mask][rem]][cnt[mask]];
  auto &ret = memo[(i * 1024 + mask) * 2520 + rem];
  if(ret != -1 && !f) return ret;
  int m = f ? v[i] : 9;
  int ans = 0;
  for(int k = 0; k <= m; k++) {
    ans += yo(i - 1, mask | (1 << k), (rem * 10 + k) % 2520, k == m ? f : 0);
    if(ans >= mod) ans -= mod;
  }
  if(!f) ret = ans;
  return ans;
}
int solve(ll n) {
  if(n <= 0) return 0;
  v.clear();
  while(n) {
    v.emplace_back(n % 10);
    n /= 10;
  }
  return yo(v.size() - 1, 0, 0, 1);
}
void prepare() {
  memset(b, 0, sizeof b);
  memo.assign(19 * 1024 * 2520, -1);
  for(int i = 1; i < 20; i++) {
    pw[i][0] = 1;
    for(int k = 1; k < 20; k++) pw[i][k] = pw[i][k - 1] * 1LL * i % mod;
  }
  for(int mask = 1; mask < (1 << 10); mask++) cnt[mask] = __builtin_popcount(mask) - (mask & 1);
  for(int mask = 1; mask < (1 << 10); mask++) {
    for(int rem = 0; rem < 2530; rem++) {
      for(int i = 1; i < 10; i++) if(mask >> i & 1) b[mask][rem] += rem % i == 0;
    }
  }
}

}
