#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void topological_sort_dfs(bool **edges, int n, bool *used, int v, vector<int> *order)
{
    used[v] = true;
    for (int dest = 0; dest < n; ++dest) {
        if (!edges[v][dest] || used[dest])
            continue;
        topological_sort_dfs(edges, n, used, dest, order);
    }
    order->push_back(v);
}

vector<int> topological_sort(bool **edges, int n)
{
    bool *used = new bool[n]();
    vector<int> order;
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            topological_sort_dfs(edges, n, used, i, &order);
    }
    reverse(order.begin(), order.end());
    return order;
}

int main(int argc, char **argv)
{
    int n;
    cin >> n;
    bool **edges = new bool*[n];
    for (int i = 0; i < n; ++i) {
        edges[i] = new bool[n]();
    }
    while (true) {
        int i1, i2;
        cin >> i1 >> i2;
        if (cin.eof())
            break;
        edges[i1][i2] = true;
    }
    vector<int> order = topological_sort(edges, n);
    for (vector<int>::iterator it = order.begin(); it != order.end(); ++it) {
        cout << *it << "\n";
    }
}
