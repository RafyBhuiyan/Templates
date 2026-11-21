#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9, B = 440;

struct query {
  int l, r, id;
  bool operator < (const query &x) const {
    if(l / B == x.l / B) return ((l / B) & 1) ? r > x.r : r < x.r;
    return l / B < x.l / B;
  }
} Q[N];
int cnt[N], a[N];
long long sum;
inline void add_left(int i) {
  int x = a[i];
  sum += 1LL * (cnt[x] + cnt[x] + 1) * x;
  ++cnt[x];
}
inline void add_right(int i) {
  int x = a[i];
  sum += 1LL * (cnt[x] + cnt[x] + 1) * x;
  ++cnt[x];
}
inline void rem_left(int i) {
  int x = a[i];
  sum -= 1LL * (cnt[x] + cnt[x] - 1) * x;
  --cnt[x];
}
inline void rem_right(int i) {
  int x = a[i];
  sum -= 1LL * (cnt[x] + cnt[x] - 1) * x;
  --cnt[x];
}
long long ans[N];
// Inclusive endpoints. first_index is 0 or 1 depending on the input array.
template<class Iter,class AddL,class AddR,class DelL,class DelR,class Save>
void process_queries(Iter first, Iter last,int first_index,AddL add_l,AddR add_r,DelL del_l,DelR del_r,Save save) {
  sort(first,last);
  int l=first_index,r=l-1;
  for(auto it=first;it!=last;++it) {
    while(l>it->l) add_l(--l);
    while(r<it->r) add_r(++r);
    while(l<it->l) del_l(l++);
    while(r>it->r) del_r(r--);
    save(it->id);
  }
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, q;
  cin >> n >> q;
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 1; i <= q; i++) {
    cin >> Q[i].l >> Q[i].r;
    Q[i].id = i;
  }
  process_queries(Q+1,Q+q+1,1,add_left,add_right,rem_left,rem_right,
                  [](int id) { ans[id]=sum; });
  for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
  return 0;
}
