#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


struct Item
{
    int weight, value;

    bool operator<(const Item &that) const
    {
        return weight < that.weight;
    }
};


int main(int argc, char *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N, W;
    in >> N >> W;
    vector<Item> items(N);
    for (int i = 0; i < N; ++i)
    {
        Item item;
        in >> item.weight;
        in >> item.value;
        items[i] = item;
    }
    sort(items.begin(), items.end());

    int *m = new int[W + 1];
    for (int w = 0; w <= W; ++w)
    {
        int max = 0;
        for (int i = 0; (items[i].weight <= w) && (i < N); ++i)
        {
            int val = items[i].value + m[w - items[i].weight];
            if (val > max)
                max = val;
        }
        m[w] = max;
    }

    out << m[W];
}
