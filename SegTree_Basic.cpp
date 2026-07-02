#include<bits/stdc++.h>
using namespace std;
#define N 200000
vector<int>ara(N), tree(4 * N);
void build(int node, int b, int e)
{
    if (b == e)
    {
        tree[node] = ara[b]; // Leaf node
        return;
    }
    int left = node * 2;
    int right = node * 2 + 1;
    int mid = (b + e) / 2;
    build(left, b, mid); // Left child build
    build(right, mid + 1, e); // Right child build
    tree[node] = tree[right] + tree[left];
}
int query(int node, int b, int e, int i, int j)
{
    if (i > e || j < b)
        return 0; // Outside of the Range of the current node
    if (b >= i && e <= j)
        return tree[node]; // current node is fully in the range
    int left = node * 2;
    int right = node * 2 + 1;
    int mid = (b + e) / 2;
    return query(left, b, mid, i, j) + query(right, mid + 1, e, i, j);
}
void update(int node, int b, int e, int i, int value)
{
    if (i > e || i < b)
        return;
    if (b >= i && e <= i)
    {
        tree[node] = value;
        return;
    }
    int left = node * 2;
    int right = node * 2 + 1;
    int mid = (b + e) / 2;
    update(left, b, mid, i, value);
    update(right, mid + 1, e, i, value);
    tree[node] = tree[left] + tree[right];
}
int main()
{
    int n, q, test, k, x, y;
    cin >> n >> q;
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
