#include <bits/stdc++.h>
using namespace std;

// Zero-based inclusive ranges. update assigns, add increments, query returns the sum.
using T = long long;
struct Node
{
    T sum, maximum;
    Node()
    {
        sum = 0;
        maximum = numeric_limits<T>::lowest();
    }
    Node(T _sum)
    {
        maximum = sum = _sum;
    }
};
struct SegTree
{
    vector<Node> st;
    vector<T> lazy, added;
    vector<bool> assigned;
    int n;

    void init(int _n)
    {

        n = _n;
        st.assign(4*n+4, Node(0));
        lazy.assign(st.size(), 0);
        added.assign(st.size(), 0);
        assigned.assign(st.size(), false);
    }
    SegTree(int _n = 0)
    {
        init(_n);
    }
    Node merge(Node a, Node b)
    {
        Node result(a.sum+b.sum);
        result.maximum=max(a.maximum,b.maximum);
        return result;
    }
    void update(int l, int r, T v)
    {
        if(!n || l > r) return;
        update(1, 0, n - 1,l,r,v);
    }
    void update(int p, Node v)
    {
        update(p,p,v.sum);
    }
    Node query(int l, int r)
    {
        if(!n || l > r) return Node();
        return query(1, 0, n - 1, l, r);
    }

    void build(int x, int l, int r, vector<Node> &v)
    {
        if(l == r)
        {
            st[x] = v[l];
            return;
        }
        int m = l + r >> 1;
        build(x << 1, l, m, v);
        build(x << 1 | 1, m + 1, r, v);
        st[x] = merge(st[x << 1], st[x << 1 | 1]);
    }
    void build(vector<Node> &v)
    {
        init(v.size());
        if(n) build(1, 0, n - 1, v);
    }
    void apply(int x, int l, int r, T v, bool assign) {
        if (assign) {
            st[x].sum = (r-l+1)*v;
            st[x].maximum = v;
            lazy[x] = v; assigned[x] = true; added[x] = 0;
        } else {
            st[x].sum += (r-l+1)*v;
            st[x].maximum += v;
            added[x] += v;
        }
    }
    void push(int x, int l,int r) {
        if(l==r) return;
        int m=(l+r)/2;
        if(assigned[x]) {
            apply(x*2,l,m,lazy[x],true); apply(x*2+1,m+1,r,lazy[x],true);
            assigned[x]=false;
        }
        if(added[x]) {
            apply(x*2,l,m,added[x],false); apply(x*2+1,m+1,r,added[x],false);
            added[x]=0;
        }
    }
    void add(int l,int r,T v) {
        if(n && l<=r) update(1,0,n-1,l,r,v,false);
    }
    Node query(int x, int sl, int sr, int l, int r)
    {
        push(x,sl,sr);
        if(sr < l || sl > r) return Node();
        if(sl >= l && sr <= r) return st[x];
        int m = sl + sr >> 1;
        return merge(query(x << 1, sl, m, l, r), query(x << 1 | 1, m + 1, sr, l, r));
    }

    void update(int x,int l,int r,int i,int j,T v,bool assign=true) {
        if(j<l || r<i) return;
        if(i<=l && r<=j) { apply(x,l,r,v,assign); return; }
        push(x,l,r);
        int m=(l+r)/2;
        update(2*x,l,m,i,j,v,assign);
        update(2*x+1,m+1,r,i,j,v,assign);
        st[x]=merge(st[2*x],st[2*x+1]);
    }
};

// Personal one-based point-update example. The free functions use the same tree.
vector<int> ara(200001);
SegTree basic_tree;
void build(int, int b,int e) {
    vector<Node> values;
    for (int i=b;i<=e;++i) values.emplace_back(ara[i]);
    basic_tree.build(values);
}
T query(int,int b,int,int i,int j) { return basic_tree.query(i-b,j-b).sum; }
T query_max(int,int b,int,int i,int j) { return basic_tree.query(i-b,j-b).maximum; }
void update(int,int b,int,int i,int value) { basic_tree.update(i-b,Node(value)); }
int main()
{
    int n, q, test, k, x, y;
    cin >> n >> q;
    ara.resize(n+1);
    // Input The Array
    for (int i = 1; i <= n; i++)
    {
        cin >> ara[i];
    }

    // Build The Segment Tree -> O(n)
    build(1, 1, n);
    while (q--)
    {
        cin >> k >> x >> y;
        // if k = 1 then update else query (O(log n))
        if (k == 1)
            update(1, 1, n, x, y);
        else
            cout << query(1, 1, n, x, y) << endl;
    }
}

// Sparse range-add/range-sum variant for a large, initially zero coordinate domain.
struct SparseRangeSum {
    struct Branch {
        long long sum=0, add=0;
        unique_ptr<Branch> left, right;
    };
    Branch root;
    long long low, high;
    SparseRangeSum(long long l,long long r) : low(l), high(r) { assert(l<=r); }
    static void add_to(Branch& node,long long l,long long r,long long a,long long b,long long v) {
        if(b<l || r<a) return;
        node.sum += (min(r,b)-max(l,a)+1)*v;
        if(a<=l && r<=b) { node.add+=v; return; }
        long long m=l+(r-l)/2;
        if(a<=m) {
            if(!node.left) node.left=make_unique<Branch>();
            add_to(*node.left,l,m,a,b,v);
        }
        if(b>m) {
            if(!node.right) node.right=make_unique<Branch>();
            add_to(*node.right,m+1,r,a,b,v);
        }
    }
    static long long sum_of(const Branch* node,long long l,long long r,long long a,long long b) {
        if(!node || b<l || r<a) return 0;
        if(a<=l && r<=b) return node->sum;
        long long m=l+(r-l)/2;
        return (min(r,b)-max(l,a)+1)*node->add + sum_of(node->left.get(),l,m,a,b)
               + sum_of(node->right.get(),m+1,r,a,b);
    }
    void add(long long a,long long b,long long v) { if(a<=b) add_to(root,low,high,a,b,v); }
    long long query(long long a,long long b) const { return a<=b ? sum_of(&root,low,high,a,b) : 0; }
};
