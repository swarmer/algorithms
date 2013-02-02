#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;


struct Edge
{
    int i1, i2, dist;
};


int closest_node(const set<int> &unvisited, map<int, int> &dist)
{
    int min_node = *(unvisited.begin());
    int min_dist = dist.count(min_node) ? dist[min_node] : -1;
    for (set<int>::iterator it = unvisited.begin(); it != unvisited.end(); ++it) {
        int node = *it;
        if (!dist.count(node))
            continue;
        int d = dist[node];
        if (d < min_dist || min_dist == -1) {
            min_dist = d;
            min_node = node;
        }
    }
    return min_node;
}

vector<int> neighbors(vector<Edge> edges, set<int> unvisited, int node)
{
    vector<int> ns;
    for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
        Edge e = *it;
        if (e.i1 == node && unvisited.count(e.i2))
            ns.push_back(e.i2);
    }
    return ns;
}

int basic_dist(vector<Edge> edges, int i1, int i2)
{
    for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
        Edge e = *it;
        if (e.i1 == i1 && e.i2 == i2)
            return e.dist;
    }
    return -1;
}

vector<int> dijkstra(vector<Edge> edges, int source, int target)
{
    set<int> unvisited;
    for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
        unvisited.insert(it->i1);
        unvisited.insert(it->i2);
    }

    map<int, int> prev, dist;
    dist[source] = 0;

    while (!unvisited.empty()) {
        int node = closest_node(unvisited, dist);
        unvisited.erase(node);
        if (node == target || !dist.count(node))
            break;

        vector<int> ns = neighbors(edges, unvisited, node);
        for (vector<int>::iterator it = ns.begin(); it != ns.end(); ++it) {
            int n = *it;
            int alt = dist[node] + basic_dist(edges, node, n);
            if (!dist.count(n) || alt < dist[n]) {
                dist[n] = alt;
                prev[n] = node;
            }
        }
    }

    vector<int> path;
    int link = target;
    while (prev.count(link)) {
        path.insert(path.begin(), link);
        link = prev[link];
    }
    return path;
}

int main(int argc, char *argv[])
{
    ifstream graph(argv[1]);
    vector<Edge> edges;
    int i1, i2, dist;
    while (true) {
        graph >> i1 >> i2 >> dist;
        if (graph.eof())
            break;
        Edge edge;
        edge.i1 = i1;
        edge.i2 = i2;
        edge.dist = dist;
        edges.push_back(edge);
    }
    int source, target;
    sscanf(argv[2], "%d", &source);
    sscanf(argv[3], "%d", &target);

    vector<int> path = dijkstra(edges, source, target);
    for (vector<int>::iterator it = path.begin(); it != path.end(); ++it) {
        cout << *it << endl;
    }
}
