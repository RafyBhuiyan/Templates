struct SegTree
{
    using T = long long int;
    struct Node
    {
        T seg,sum,suff,pref;
        Node()
        {
            seg = sum = pref = suff = 0;
        }
        Node(T _seg,T _a,T _b,T _c)
        {
            seg = _seg;
            sum = _a;
            pref = _b;
            suff = _c;
        }
    };
    Node merge(Node a, Node b)
    {
        return Node(max({a.seg,b.seg,a.suff+b.pref}),a.sum+b.sum,max(a.pref,a.sum+b.pref),max(b.suff,b.sum+a.suff));
    }
    vector<Node> st;
    int n;
    void init(int _n)
    {
        if(_n <= 0)return;
        n = _n;
        int m = ceil(log2(n)) + 1;
        st.resize((1 << m) + 5);
    }
    SegTree(int _n = 0)
    {
        init(_n);
    }
    void build(int x, int l, int r, vector<T> &v)
    {
        if(l == r)
        {
            if(v[l]>0)
            {
                st[x] = Node(v[l],v[l],v[l],v[l]);
            }
            else
                st[x] = Node(0ll,v[l],0ll,0ll);
            return;
        }
        int m = l + r >> 1;
        build(x << 1, l, m, v);
        build(x << 1 | 1, m + 1, r, v);
        st[x] = merge(st[x << 1], st[x << 1 | 1]);
    }
    void build(vector<T> &v)
    {
        build(1, 0, n - 1, v);
    }
    void build(T x)
    {
        vector<T> v(n, x);
        build(1, 0, n - 1, v);
    }
    void update(int x, int l, int r, int p, T v)
    {
        if(l == r)
        {
            if(v>0)
            {
                st[x] = Node(v,v,v,v);
            }
            else
                st[x] =  Node(0ll,v,0ll,0ll);
            return;
        }
        int m = l + r >> 1;
        if(p <= m) update(x << 1, l, m, p, v);
        else update(x << 1 | 1, m + 1, r, p, v);
        st[x] = merge(st[x << 1], st[x << 1 | 1]);
    }
    void update(int p, T v)
    {
        update(1, 0, n - 1, p, v);
    }
    Node query(int x, int sl, int sr, int l, int r)
    {
        if(sr < l || sl > r) return Node();
        if(sl >= l && sr <= r) return st[x];
        int m = sl + sr >> 1;
        return merge(query(x << 1, sl, m, l, r), query(x << 1 | 1, m + 1, sr, l, r));
    }
    Node query(int l, int r)
    {
        if(l > r) return Node();
        return query(1, 0, n - 1, l, r);
    }
};
void solve()
{
    int n,m;
    cin>>n>>m;
    vector<ll>ra(n);
    For(i,n) cin>>ra[i];
    SegTree sg = SegTree(n);
    sg.build(ra);
    int l,r;
    cout<<sg.query(0,n-1).seg<<endl;
    For(i,m)
    {
        cin>>l>>r;
        sg.update(l,r);
        cout<<sg.query(0,n-1).seg<<endl;
    }
}
