#include <bits/stdc++.h>
using namespace std;

// Legendre's formula; p must be prime. For n! in base ten, use p=5.
long long factorial_exponent(long long n, long long p) {
    assert(n>=0 && p>=2);
    long long count=0;
    while(n) { n/=p; count+=n; }
    return count;
}
vector<pair<long long,long long>> factor_factorial(long long n,const vector<int>& primes) {
    vector<pair<long long,long long>> factors;
    for(int p:primes) {
        if(p>n) break;
        factors.emplace_back(p,factorial_exponent(n,p));
    }
    return factors;
}
