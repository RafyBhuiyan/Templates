#include<bits/stdc++.h>
using namespace std;

// An element Z[i] of Z array stores length of the longest substring
// starting from str[i] which is also a prefix of str[0..n-1].
// The first entry of Z array is meaning less as complete string is always prefix of itself.
// Here Z[0]=0.
template<class Sequence>
vector<int> z_function(const Sequence& s) {
  int n = (int) s.size();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}
int32_t main() {
  string s;
  cin >> s;
  vector<int>  ans = z_function(s);
  for(auto x : ans) cout << x << ' ';
  return 0;
}

// Pattern occurrences, including overlaps. Encode the separator outside the byte alphabet.
vector<int> z_matches(const string& text,const string& pattern) {
    if(pattern.empty()) {
        vector<int> all(text.size()+1); iota(all.begin(),all.end(),0); return all;
    }
    vector<int> seq;
    for(unsigned char c:pattern) seq.push_back(c);
    seq.push_back(-1);
    for(unsigned char c:text) seq.push_back(c);
    auto z=z_function(seq);
    vector<int> positions;
    for(int i=pattern.size()+1;i<(int)z.size();++i)
        if(z[i]>=(int)pattern.size()) positions.push_back(i-pattern.size()-1);
    return positions;
}
