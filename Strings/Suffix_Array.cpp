#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    string a; int N, m;
    vector<int> SA, LCP, x, y, w, c, temp;
    SuffixArray(string _a, int m) : a(" " + _a), N(a.length()), m(max(m,257)),
        SA(N), LCP(N), x(N), y(N), w(max({257, m, N})), c(N) {
        a[0] = 0;
        DA();
        kasaiLCP();
#define REF(X) { rotate(X.begin(), X.begin()+1, X.end()); X.pop_back();}
        REF(SA); REF(LCP);
        a = a.substr(1, a.size());
        for (int i = 0; i < (int) SA.size(); ++i) --SA[i];
#undef REF
    }
    // Half-open range of suffix-array ranks starting with pattern.
    pair<int,int> equal_range(const string& pattern) const {
        auto boundary = [&](bool upper) {
            int l = 0, r = SA.size();
            while (l < r) {
                int mid = l + (r-l)/2;
                int cmp = a.compare(SA[mid], pattern.size(), pattern);
                if (cmp < 0 || (upper && cmp == 0)) l = mid+1;
                else r = mid;
            }
            return l;
        };
        return {boundary(false), boundary(true)};
    }
    bool contains(const string& pattern) const {
        auto range = equal_range(pattern);
        return pattern.empty() || range.first < range.second;
    }
    vector<vector<int>> rmq;
    // Optional O(n log n) preprocessing for O(1) LCP between suffixes.
    void prepare_lcp_queries() {
        rmq = {LCP};
        for (int span=2; span <= (int)SA.size(); span*=2) {
            const auto& prev = rmq.back();
            vector<int> row(SA.size()-span+1);
            for (int i=0;i<(int)row.size();++i) row[i]=min(prev[i],prev[i+span/2]);
            rmq.push_back(move(row));
        }
    }
    int get_lcp(int i, int j) const {
        assert(0 <= i && i < (int)a.size() && 0 <= j && j < (int)a.size());
        if (i == j) return a.size()-i;
        assert(!rmq.empty());
        int l=c[i+1]-1, r=c[j+1]-1;
        if (l>r) swap(l,r);
        int k=31-__builtin_clz(r-l);
        return min(rmq[k][l+1],rmq[k][r-(1<<k)+1]);
    }
    // Inclusive occurrence interval for a substring starting at pos.
    pair<int,int> find_occurrence(int pos,int length) const {
        auto [first,last] = equal_range(a.substr(pos,length));
        return {first,last-1};
    }
    inline bool cmp (const int a, const int b, const int l) {
        return (y[a] == y[b] && (a+l < N ? y[a+l] : -1) == (b+l < N ? y[b+l] : -1));
    }
    void Sort() {
        for (int i = 0; i < m; ++i) w[i] = 0;
        for (int i = 0; i < N; ++i) ++w[x[y[i]]];
        for (int i = 0; i < m - 1; ++i) w[i + 1] += w[i];
        for (int i = N - 1; i >= 0; --i) SA[--w[x[y[i]]]] = y[i];
    }
    void DA() {
        for (int i = 0; i < N; ++i) x[i] = i ? 1+(unsigned char)a[i] : 0, y[i] = i;
        Sort();
        for (int i, j = 1, p = 1; p < N; j <<= 1, m = p) {
            for (p = 0, i = N - j; i < N; i++) y[p++] = i;
            for (int k = 0; k < N; ++k) if (SA[k] >= j) y[p
                            ++] = SA[k] - j;
            Sort();
            for (swap(x, y), p = 1, x[SA[0]] = 0, i = 1; i < N; ++i)
                x[SA[i]] = cmp(SA[i - 1], SA[i], j) ? p - 1 : p++;
        }
    }
    void kasaiLCP() {
        for (int i = 0; i < N; i++) c[SA[i]] = i;
        int k=0;
        for (int i=0;i<N;++i) {
            int rank=c[i];
            if(rank<=1) { LCP[rank]=0; k=0; continue; }
            int j=SA[rank-1];
            if(k) --k;
            while(i+k<N && j+k<N && a[i+k]==a[j+k]) ++k;
            LCP[rank]=k;
        }
    }
};

const int N = 6e5 + 5;
int table[N][20], lg[N];
void buildSparseTable(vector<int> &arr) {
    int n = arr.size() - 1;
    for (int i = 1; i <= n; i++)
        table[i][0] = arr[i];
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i / 2] + 1;
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int query(int l, int r) {
    if (l > r) return 0;
    int len = r - l + 1;
    int k = lg[len];
    return min(table[l][k], table[r - (1 << k) + 1][k]);
}
// SuffixArray suff = SuffixArray(st, 128); // 128 is the Ascii bound of the characters

namespace induced_sorting {
void induced_sort(const vector<int> &vec, int val_range, vector<int> &SA, const vector<bool> &sl, const vector<int> &lms_idx) {
  vector<int> l(val_range, 0), r(val_range, 0);
  for (int c : vec) {
    if (c + 1 < val_range) ++l[c + 1];
    ++r[c];
  }
  partial_sum(l.begin(), l.end(), l.begin());
  partial_sum(r.begin(), r.end(), r.begin());
  fill(SA.begin(), SA.end(), -1);
  for (int i = lms_idx.size() - 1; i >= 0; --i)
    SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
  for (int i : SA)
    if (i >= 1 && sl[i - 1]) {
      SA[l[vec[i - 1]]++] = i - 1;
    }
  fill(r.begin(), r.end(), 0);
  for (int c : vec)
    ++r[c];
  partial_sum(r.begin(), r.end(), r.begin());
  for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k])
    if (i >= 1 && !sl[i - 1]) {
      SA[--r[vec[i - 1]]] = i - 1;
    }
}

vector<int> SA_IS(const vector<int> &vec, int val_range) {
  const int n = vec.size();
  vector<int> SA(n), lms_idx;
  vector<bool> sl(n);
  sl[n - 1] = false;
  for (int i = n - 2; i >= 0; --i) {
    sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
    if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
  }
  reverse(lms_idx.begin(), lms_idx.end());
  induced_sort(vec, val_range, SA, sl, lms_idx);
  vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
  for (int i = 0, k = 0; i < n; ++i)
    if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
      new_lms_idx[k++] = SA[i];
    }
  int cur = 0;
  SA[n - 1] = cur;
  for (size_t k = 1; k < new_lms_idx.size(); ++k) {
    int i = new_lms_idx[k - 1], j = new_lms_idx[k];
    if (vec[i] != vec[j]) {
      SA[j] = ++cur;
      continue;
    }
    bool flag = false;
    for (int a = i + 1, b = j + 1;; ++a, ++b) {
      if (vec[a] != vec[b]) {
        flag = true;
        break;
      }
      if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
        flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
        break;
      }
    }
    SA[j] = (flag ? ++cur : cur);
  }
  for (size_t i = 0; i < lms_idx.size(); ++i)
    lms_vec[i] = SA[lms_idx[i]];
  if (cur + 1 < (int)lms_idx.size()) {
    auto lms_SA = SA_IS(lms_vec, cur + 1);
    for (size_t i = 0; i < lms_idx.size(); ++i) {
      new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
  }
  induced_sort(vec, val_range, SA, sl, new_lms_idx);
  return SA;
}
// Linear-time alternative. Reserve 0 for a unique terminal.
vector<int> suffix_array(const string& s) {
    if (s.empty()) return {};
    vector<int> symbols(s.size()+1);
    for (size_t i=0;i<s.size();++i) symbols[i]=(unsigned char)s[i]+1;
    auto sa=SA_IS(symbols,257);
    sa.erase(sa.begin());
    return sa;
}
}
