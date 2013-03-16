#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <iomanip>
#include <cfloat>
using namespace std;
typedef long long ll;

struct SegmentTree
{
    int N;
    vector<int> data;

    SegmentTree(int N, vector<int> &orig) : N(N), data(N * 4)
    {
        build(orig, 1, 0, N - 1);
    }

    inline int cleft(int i) { return i * 2; }
    inline int cright(int i) { return i * 2 + 1; }

    void build(vector<int> &orig, int v, int tl, int tr)
    {
        if (tl == tr) {
            data[v] = orig[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(orig, cleft(v), tl, tm);
        build(orig, cright(v), tm + 1, tr);
        data[v] = data[cleft(v)] + data[cright(v)];
    }
    
    int _sum(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return data[v];
        int tm = (tl + tr) / 2;
        return _sum(cleft(v), tl, tm, l, min(r, tm)) +
               _sum(cright(v), tm + 1, tr, max(l, tm + 1), r);
    }

    int sum(int l, int r)
    {
        return _sum(1, 0, N - 1, l, r);
    }

    void _update(int v, int tl, int tr, int i, int val)
    {
        if (tl == tr) {
            data[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (i <= tm)
            _update(cleft(v), tl, tm, i, val);
        else
            _update(cright(v), tm + 1, tr, i, val);
        data[v] = data[cleft(v)] + data[cright(v)];
    }

    void update(int i, int val)
    {
        _update(1, 0, N - 1, i, val);
    }
};


int main(int argc, char **argv)
{
    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i)
        cin >> arr[i];
    SegmentTree st(N, arr);
    while (!cin.eof()) {
        string t;
        int a, b;
        cin >> t >> a >> b;
        if (cin.eof())
            break;
        if (t == "sum")
            cout << st.sum(a, b) << "\n";
        else if (t == "set")
            st.update(a, b);
    }
}
