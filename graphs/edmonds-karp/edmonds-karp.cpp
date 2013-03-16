#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <iomanip>
#include <cfloat>
#include <queue>
#include <memory>
using namespace std;
typedef long long ll;

struct Edge
{
    int i1, i2, capacity, flow;

    Edge(int i1, int i2, int capacity) : i1(i1), i2(i2), capacity(capacity), flow(0) {}
    Edge() : i1(-1), i2(-1), capacity(-1), flow(-1) {}

    int res()
    {
        return capacity - flow;
    }
};

struct Network
{
    int V, S, T;
    vector<map<int, Edge> > edges;

    int flow;

    Network() : flow(0) {}

    bool bfs()
    {
        queue<int> q;
        vector<bool> visited;
        vector<int> prev, minc;
        visited.assign(V, false);
        prev.assign(V, -1);
        minc.assign(V, INT_MAX);
        q.push(S);

        while (!q.empty()) {
            int c = q.front();
            q.pop();
            visited[c] = true;

            if (c == T) {
                int df = minc[T];
                flow += df;
                int p = T;
                while (prev[p] != -1) {
                    int u = prev[p], v = p;
                    edges[u][v].flow += df;
                    edges[v][u].flow = -edges[u][v].flow;
                    p = prev[p];
                }
                return true;
            }

            map<int, Edge> &es = edges[c];
            map<int, Edge>::iterator it;
            for (it = es.begin(); it != es.end(); ++it) {
                Edge &e = it->second;
                if (!visited[e.i2] && e.res() > 0) {
                    q.push(e.i2);
                    prev[e.i2] = e.i1;
                    minc[e.i2] = min(minc[e.i1], e.res());
                }
            }
        }
        return false;
    }

    int maxflow()
    {
        while (bfs()) {}
        return flow;
    }
};


int main(int argc, char **argv)
{
    Network n;
    cin >> n.V >> n.S >> n.T;
    n.edges.resize(n.V);
    while (!cin.eof()) {
        int i1, i2, c;
        cin >> i1 >> i2 >> c;
        if (cin.eof())
            break;
        n.edges[i1][i2] = Edge(i1, i2, c);
        n.edges[i2][i1] = Edge(i2, i1, c);
    }
    cout << n.maxflow() << "\n";
}
