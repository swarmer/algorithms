#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <map>
#include <climits>
using namespace std;

struct Edge
{
    int i1, i2, dist;

    Edge(int i1 = -1, int i2 = -1, int dist = -1) : i1(i1), i2(i2), dist(dist) {}
};

const int INF = 2000000000;

struct Bellman_Ford
{
    int V, E, source;
    vector<int> prev, dist;
    vector<Edge> &edges;

    Bellman_Ford(int V, int E, int source, vector<Edge> &edges)
        : V(V), E(E), source(source), edges(edges)
    {
        prev.assign(V, -1);
        dist.assign(V, INF);
        dist[source] = 0;
    }

    bool run()
    {
        for (int i = 0; i < V - 1; ++i) {
            for (int j = 0; j < E; ++j) {
                Edge &edge = edges[j];
                if (dist[edge.i1] == INF)
                    continue;
                int new_dist = dist[edge.i1] + edge.dist;
                if (dist[edge.i2] > new_dist) {
                    dist[edge.i2] = new_dist;
                    prev[edge.i2] = edge.i1;
                }
            }
        }
        for (int i = 0; i < E; ++i) {
            Edge &edge = edges[i];
            if (dist[edge.i2] > (dist[edge.i1] + edge.dist))
                return false;
        }
        return true;
    }
};


int main(int argc, char *argv[])
{
    int V, E, source, target;
    cin >> V >> E >> source >> target;
    vector<Edge> graph(E);
    int i1, i2, dist;
    for (int i = 0; i < E; ++i) {
        cin >> i1 >> i2 >> dist;
        graph[i] = Edge(i1, i2, dist);
    }
    Bellman_Ford bf(V, E, source, graph);
    bool ok = bf.run();
    if (!ok) {
        cout << "Negative cycle detected!\n";
        return 0;
    } else {
        int total = bf.dist[target];
        vector<int> path;
        int v = target;
        while (v != -1) {
            path.push_back(v);
            v = bf.prev[v];
        }
        reverse(path.begin(), path.end());
        printf("Total distance: %d\n", total);
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << ((i == path.size() - 1) ? "\n" : " -> ");
        }
    }
}
