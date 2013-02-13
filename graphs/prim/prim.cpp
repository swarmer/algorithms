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

struct Graph
{
    int V;
    vector<vector<pair<int, int> > > vertices;
};


set<pair<int, int> > prim(Graph &graph)
{
    vector<vector<pair<int, int> > > &vertices = graph.vertices;
    int V = graph.V;
    set<pair<int, int> > mst;
    int *min_edge = new int[V];
    int *prev_vertex = new int[V];
    for (int i = 0; i < V; ++i) {
        min_edge[i] = -1;
        prev_vertex[i] = -1;
    }
    min_edge[0] = 0;
    set<pair<int, int> > vertex_min;
    set<int> visited;
    vertex_min.insert(make_pair(0, 0));

    for (int i = 0; i < V; ++i) {
        if (vertex_min.empty()) {
            mst.clear();
            return mst;
        }
        int v_id = vertex_min.begin()->second;
        vertex_min.erase(vertex_min.begin());
        visited.insert(v_id);

        if (prev_vertex[v_id] != -1) {
            mst.insert(make_pair(prev_vertex[v_id], v_id));
        }

        for (int j = 0; j < vertices[v_id].size(); ++j) {
            int dest = vertices[v_id][j].first;
            int cost = vertices[v_id][j].second;
            if (visited.count(dest)) {
                continue;
            }
            if (cost < min_edge[dest] || min_edge[dest] == -1) {
                vertex_min.erase(make_pair(min_edge[dest], dest));
                min_edge[dest] = cost;
                prev_vertex[dest] = v_id;
                vertex_min.insert(make_pair(cost, dest));
            }
        }
    }
    return mst;
}

int main(int argc, char **argv)
{
    int n;
    cin >> n;
    Graph graph;
    graph.V = n;
    graph.vertices.resize(n);
    while (true) {
        int i1, i2, dist;
        cin >> i1 >> i2 >> dist;
        if (cin.eof())
            break;
        graph.vertices[i1].push_back(make_pair(i2, dist));
    }
    
    set<pair<int, int> > mst = prim(graph);
    for (set<pair<int, int> >::iterator it = mst.begin(); it != mst.end(); ++it) {
        cout << it->first << " " << it->second << "\n";
    }
}
