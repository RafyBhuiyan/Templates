#include<bits/stdc++.h>
#define ll long long int
#define For(i,n) for(int i=0;i<n;i++)
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
void io()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}

struct SuffixArray
{
    int *sa, *ra, *cnt, *pos, *lcp, *lg;
    int **st;
    int n, A;
    string s;

    void srt(int mx, int k)
    {
        for(int i = 0; i < mx; i++)cnt[i] = 0;
        for(int i = 0; i < n; i++)cnt[(i + k >= n ? 0 : ra[i + k])]++;
        for(int i = 1; i < mx; i++)cnt[i] += cnt[i - 1];
        for(int i = mx - 1; i > 0; i--)cnt[i] = cnt[i - 1];
        cnt[0] = 0;
        for(int i = 0; i < n; i++)pos[cnt[(sa[i] + k >= n ? 0 : ra[sa[i] + k])]++] = sa[i];
        for(int i = 0; i < n; i++)sa[i] = pos[i];
    }
    void create_sa()
    {
        cnt = (int*)malloc(max(A, n + 5) * sizeof(int));
        pos = (int*)malloc((n + 5) * sizeof(int));

        int mx = A;

        for(int k = 1; k < n; k <<= 1)
        {
            srt(mx, k);
            srt(mx, 0);

            int r = 1;
            pos[sa[0]] = r;
            for(int i = 1; i < n; i++)
            {
                pos[sa[i]] = (ra[sa[i]] == ra[sa[i - 1]] && (sa[i - 1] + k >= n ? 1 : ra[sa[i - 1] + k] == (sa[i] + k >= n ? 1 : ra[sa[i] + k])) ? r : ++r);
            }
            for(int i = 0; i < n; i++)ra[i] = pos[i];
            mx = r + 1;
        }
    }

    SuffixArray(string &str, char garb = '$', int a = 128)
    {
        sa = ra = cnt = pos = lcp = lg = NULL;
        st = NULL;
        s = str;
        s.push_back(garb);
        n = s.size();
        A = a;
        sa = (int*)malloc(n * sizeof(int));
        ra = (int*)malloc(n * (sizeof(int)));
        for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
        create_sa();
    }
    vector<int> get_Suffixarr()
    {
        vector<int>arr;
        for(int i=0;i<s.size();i++)
        {
            arr.push_back(sa[i]);
        }
        return arr;
    }
    //lcp[i] = lcp of sa[i] and sa[i-1]
    void compute_lcp()
    {
        pos[sa[0]] = -1;
        lcp = (int*)malloc((n + 5) * sizeof(int));
        for(int i = 1; i < s.size(); i++)pos[sa[i]] = sa[i - 1];
        for(int i = 0, l = 0; i < s.size(); i++)
        {
            if(pos[i] == -1)
            {
                //lcp of sa[0] = 0
                ra[i] = 0;
                continue;
            }
            while(s[l + i] == s[pos[i] + l])l++;
            ra[i] = l--;
            if(l < 0)l = 0;
        }
        for(int i = 0; i < s.size(); i++)lcp[i] = ra[sa[i]];
    }

    //sparse table for lcp
    //call compute_lcp before it
    void create_sparse()
    {
        const int K = ceil(log2(n)) + 2;
        st = (int**)malloc(sizeof(int*) * (n + 5));
        lg = (int*)malloc(sizeof(int) * (n + 5));
        for(int i = 0; i < n; i++)
        {
            st[i] = (int*)malloc(K * sizeof(int));
            st[i][0] = lcp[i];
        }
        lg[1] = 0;
        for(int i = 2; i <= n; i++)lg[i] = lg[i >> 1] + 1;
        for(int i = 1; i < K; i++)
        {
            for(int j=0; j+(1<<i)<=n; j++)
                st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }

    //lcp of sa[l] and sa[r]
    int query(int l, int r)
    {
        if(l > r)swap(l, r);
        if(l == r)return n - sa[l] - 1;
        l++;
        int x = lg[r - l + 1];
        return min(st[l][x], st[r - (1 << x) + 1][x]);
    }
    ~SuffixArray()
    {
        if(sa != NULL)free(sa);
        if(ra != NULL)free(ra);
        if(cnt != NULL)free(cnt);
        if(pos != NULL)free(pos);
        if(lcp != NULL)free(lcp);
        if(lg != NULL)free(lg);
        if(st != NULL)
        {
            for(int i = 0; i < n; i++)free(st[i]);
            free(st);
        }
    }
};
int main()
{
    string ra;
    cin>>ra;
    SuffixArray sf(ra);
    vector<int> sa = sf.get_Suffixarr();
    
    return 0;
}
