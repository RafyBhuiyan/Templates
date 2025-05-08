using T = long long int;
struct Node
{
    T sum;
    Node()
    {
        sum = 0;
    }
    Node(T _sum)
    {
        sum = _sum;
    }
};
struct SegTree
{
    vector<Node> st;
    vector<T>lazy;
    int n;

    void init(int _n)
    {
        if(_n <= 0)return;
        n = _n;
        int m = ceil(log2(n)) + 1;
        st.resize((1 << m) + 5);
        lazy.assign((1 << m) + 5,-1);
    }
    SegTree(int _n = 0)
    {
        init(_n);
    }
    Node merge(Node a, Node b)
    {
        return Node(a.sum+b.sum);
    }
    void update(int l, int r, T v)
    {
        if(l > r) return;
        update(1, 0, n - 1,l,r,v);
    }
    void update(int p, Node v)
    {
        update(1, 0, n - 1, p, v);
    }
    Node query(int l, int r)
    {
        if(l > r) return Node();
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
        build(1, 0, n - 1, v);
    }
    void push(int node, int b,int e)
    {
        if(lazy[node]!=-1)
        {
            st[node].sum = (e-b+1)*lazy[node];
            if(b!=e)
            {
                lazy[node*2] = lazy[node];
                lazy[node*2 + 1] = lazy[node];
            }
            lazy[node] = -1;
        }
    }
    Node query(int x, int sl, int sr, int l, int r)
    {
        push(x,sl,sr);
        if(sr < l || sl > r) return Node();
        if(sl >= l && sr <= r) return st[x];
        int m = sl + sr >> 1;
        return merge(query(x << 1, sl, m, l, r), query(x << 1 | 1, m + 1, sr, l, r));
    }

    void update(int x, int l, int r, int p, Node v)
    {
        if(l == r)
        {
            st[x] = v;
            return;
        }
        int m = l + r >> 1;
        if(p <= m) update(x << 1, l, m, p, v);
        else update(x << 1 | 1, m + 1, r, p, v);
        st[x] = merge(st[x << 1], st[x << 1 | 1]);
    }
    void update(int x, int l, int r, int i,int j, T v)
    {
        push(x,l,r);
        if(l>j || r<i) return;
        if(l>=i && r<=j)
        {
            lazy[x]=v;
            push(x,l,r);
            return;
        }
        int m = l + r >> 1;
        update(x << 1, l, m, i, j, v);
        update(x << 1 | 1, m + 1, r, i, j, v);
        st[x] = merge(st[x << 1], st[x << 1 | 1]);
    }
};
