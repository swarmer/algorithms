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
typedef vector<vector<int> > vector2d;

vector2d precalc;

struct DSF
{
    int n;
    int *parents;

    DSF(int n) : n(n)
    {
        parents = new int[n];
        for (int i = 0; i < n; ++i) {
            parents[i] = i;
        }
    }

    int find(int v)
    {
        if (v == parents[v])
            return v;
        int prev = find(parents[v]);
        parents[v] = prev;
        return prev;
    }

    void merge(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
            parents[b] = a;
    }
};

struct LCA
{
    int N;
    vector2d &tree;
    vector2d precalc;
    DSF dsf;
    vector<int> ancestor;
    vector<char> color;

    LCA(int N, vector2d &tree) : N(N), tree(tree), dsf(N), precalc(N), ancestor(N)
    {
        for (int i = 0; i < N; ++i)
            precalc[i].assign(N, -1);
        color.assign(N, 'W');
    }

    void run(int u)
    {
        ancestor[dsf.find(u)] = u;
        for (size_t i = 0; i < tree[u].size(); ++i) {
            int v = tree[u][i];
            run(v);
            dsf.merge(u, v);
            ancestor[dsf.find(u)] = u;
        }
        color[u] = 'B';
        for (int v = 0; v < N; ++v) {
            if (color[v] == 'B') {
                precalc[u][v] = ancestor[dsf.find(v)];
                precalc[v][u] = precalc[u][v];
            }
        }
    }

    int get(int i1, int i2)
    {
        return precalc[i1][i2];
    }
};


int main(int argc, char **argv)
{
    int N;
    cin >> N;
    vector<vector<int> > tree(N);
    for (int i = 0; i < N - 1; ++i) {
        int i1, i2;
        cin >> i1 >> i2;
        tree[i1].push_back(i2);
    }
    string delim;
    cin >> delim;

    LCA lca(N, tree);
    lca.run(0);

    while (cin) {
        int a, b;
        cin >> a >> b;
        if (!cin)
            break;
        cout << lca.get(a, b) << "\n";
    }
}
