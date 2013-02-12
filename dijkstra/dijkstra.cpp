#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <set>
#include <utility>
#include <map>
using namespace std;


struct Graph
{
    int V;
    vector<vector<pair<int, int> > > vertices;
};

struct VertexComparator
{
    int *dist;

    VertexComparator(int *dist) : dist(dist) {}

    bool operator()(int v1, int v2) const
    {
        int d1 = dist[v1];
        int d2 = dist[v2];
        if (d1 == d2)
            return v1 < v2;
        else
            return d1 < d2;
    }
};


vector<int> dijkstra(Graph graph, int source, int target)
{
    vector<vector<pair<int, int> > > &vertices = graph.vertices;
    int V = graph.V;
    int *prev = new int[V];
    int *dist = new int[V];
    for (int i = 0; i < V; ++i) {
        prev[i] = -1;
        dist[i] = -1;
    }
    dist[source] = 0;
    VertexComparator cmp(dist);
    set<int, VertexComparator> vqueue(cmp);
    vqueue.insert(source);

    while (!vqueue.empty()) {
        int node = *(vqueue.begin());
        vqueue.erase(node);
        if (node == target)
            break;

        for (int i = 0; i < vertices[node].size(); ++i) {
            int dest = vertices[node][i].first;
            int len = vertices[node][i].second;
            int alt = dist[node] + len;
            if (dist[dest] == -1 || alt < dist[dest]) {
                vqueue.erase(dest);
                dist[dest] = alt;
                prev[dest] = node;
                vqueue.insert(dest);
            }
        }
    }

    vector<int> path;
    int link = target;
    while (prev[link] != -1) {
        path.insert(path.begin(), link);
        link = prev[link];
    }
    return path;
}

int main(int argc, char *argv[])
{
    int V, source, target;
    cin >> V >> source >> target;
    Graph graph;
    graph.V = V;
    graph.vertices.resize(V);
    int i1, i2, dist;
    while (true) {
        cin >> i1 >> i2 >> dist;
        if (cin.eof())
            break;
        graph.vertices[i1].push_back(make_pair(i2, dist));
    }

    vector<int> path = dijkstra(graph, source, target);
    for (vector<int>::iterator it = path.begin(); it != path.end(); ++it) {
        cout << *it << endl;
    }
}
