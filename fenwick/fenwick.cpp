#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <climits>
using namespace std;

struct Fenwick
{
    int N;
    int *array;

    Fenwick(int N, int *data) : N(N)
    {
        array = new int[N]();
        for (int i = 0; i < N; ++i) {
            update(i, data[i]);
        }
    }

    int total(int r)
    {
        int result = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) {
            result += array[r];
        }
        return result;
    }

    int range_sum(int l, int r)
    {
        return total(r) - total(l - 1);
    }

    void update(int i, int delta)
    {
        for (int j = i; j < N; j = (j | (j + 1))) {
            array[j] += delta;
        }
    }
};


int main(int argc, char **argv)
{
    int N;
    cin >> N;
    int *numbers = new int[N];
    for (int i = 0; i < N; ++i) {
        cin >> numbers[i];
    }
    Fenwick fenwick(N, numbers);

    while (true) {
        string type;
        cin >> type;
        if (cin.eof())
            break;
        if (type == "set") {
            int i, v;
            cin >> i >> v;
            fenwick.update(i, v - numbers[i]);
            numbers[i] = v;
        }
        else if (type == "sum") {
            int i1, i2;
            cin >> i1 >> i2;
            cout << fenwick.range_sum(i1, i2) << "\n";
        }
    }
}
