#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <climits>
using namespace std;

struct Edge
{
    int i1, i2, dist;

    Edge(int i1, int i2, int dist) : i1(i1), i2(i2), dist(dist) {}
    
    bool operator<(const Edge &e2) const
    {
        return dist < e2.dist;
    }
};

struct DSU
{
    int n;
    int *parents;

    DSU(int n) : n(n)
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


vector<pair<int, int> > kruskal(vector<Edge> edges, int n)
{
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    vector<pair<int, int> > mst;
    for (size_t i = 0; i < edges.size(); ++i) {
        Edge edge = edges[i];
        if (dsu.find(edge.i1) != dsu.find(edge.i2)) {
            mst.push_back(make_pair(edge.i1, edge.i2));
            dsu.merge(edge.i1, edge.i2);
        }
    }
    return mst;
}

int main(int argc, char **argv)
{
    int n;
    cin >> n;
    vector<Edge> edges;
    while (true) {
        int i1, i2, dist;
        cin >> i1 >> i2 >> dist;
        if (cin.eof())
            break;
        edges.push_back(Edge(i1, i2, dist));
    }
    
    vector<pair<int, int> > mst = kruskal(edges, n);
    for (vector<pair<int, int> >::iterator it = mst.begin(); it != mst.end(); ++it) {
        cout << it->first << " " << it->second << "\n";
    }
}
