#include <iostream>
#include <climits>
#include <cstdio>
using namespace std;


int main(int argc, char **argv)
{
    int n;
    cin >> n;
    int **dist = new int*[n];
    for (int i = 0; i < n; ++i)
    {
        dist[i] = new int[n];
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
                dist[i][j] = -1;
            else
                dist[i][j] = 0;
        }
    }
    while (true)
    {
        int n1, n2, d;
        cin >> n1 >> n2 >> d;
        if (cin.eof())
            break;
        dist[n1][n2] = d;
    }

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dist[i][k] == -1 || dist[k][j] == -1)
                    continue;
                int temp = dist[i][k] + dist[k][j];
                if (temp < dist[i][j] || dist[i][j] == -1)
                    dist[i][j] = temp;
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("dist[%d][%d]: %d\n", i, j, dist[i][j]);
        }
    }
}
