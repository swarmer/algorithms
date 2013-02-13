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

struct Kuhn
{
    int n, k;
    vector<vector<int> > &edges;
    vector<int> pairs;
    vector<bool> used;

    Kuhn(int n, int k, vector<vector<int> > &edges)
        : n(n), k(k), edges(edges), pairs(k), used(n)
    {
        pairs.assign(k, -1);
    }

    bool kuhn_dfs(int v)
    {
        if (used[v])
            return false;
        used[v] = true;
        for (size_t i = 0; i < edges[v].size(); ++i) {
            int to = edges[v][i];
            if (pairs[to] == -1 || kuhn_dfs(pairs[to])) {
                pairs[to] = v;
                return true;
            }
        }
        return false;
    }

    vector<pair<int, int> > get_matching()
    {
        for (int v = 0; v < n; ++v) {
            used.assign(n, false);
            kuhn_dfs(v);
        }

        vector<pair<int, int> > matching;
        for (int i = 0; i < k; ++i) {
            if (pairs[i] != -1) {
                matching.push_back(make_pair(pairs[i], i));
            }
        }
        return matching;
    }
};


int main(int argc, char **argv)
{
    int n, k;
    cin >> n >> k;
    vector<vector<int> > edges(n);
    while (true) {
        int i1, i2;
        cin >> i1 >> i2;
        if (cin.eof())
            break;
        edges[i1].push_back(i2);
    }

    Kuhn kuhn(n, k, edges);
    vector<pair<int, int> > matching = kuhn.get_matching();
    for (size_t i = 0; i < matching.size(); ++i) {
        cout << matching[i].first << " " << matching[i].second << "\n";
    }
}
