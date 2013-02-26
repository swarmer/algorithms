#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <iomanip>
#include <cfloat>
using namespace std;


int gcdex(int a, int b, int &x, int &y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int d = gcdex(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

int main(int argc, char **argv)
{
    int a, b;
    cin >> a >> b;
    int d, x, y;
    d = gcdex(a, b, x, y);
    printf("gcd(%d, %d) = %d = %d * %d + %d * %d\n", a, b, d, x, a, y, b);
}
