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
typedef long long ll;


int phi(int x)
{
    int result = x;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            while (x % d == 0)
                x /= d;
            result -= result / d;
        }
    }
    if (x > 1)
        result -= result / x;
    return result;
}

int main(int argc, char **argv)
{
    int x;
    cin >> x;
    cout << phi(x) << "\n";
}
