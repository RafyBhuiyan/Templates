#include <bits/stdc++.h>
using namespace std;

// Sum of sigma(i) for i=1..n by grouping equal floor quotients.
__int128 summatory_sigma(long long n) {
    __int128 ans=0;
    for(long long l=1; l<=n;) {
        long long q=n/l, r=n/q;
        ans+=(__int128(l)+r)*(r-l+1)/2*q;
        if(r==n) break;
        l=r+1;
    }
    return ans;
}
