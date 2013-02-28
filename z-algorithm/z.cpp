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


int main(int argc, char **argv)
{
    string s;
    cin >> s;
    size_t n = s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    for (size_t i = 0; i < n; ++i) {
        cout << z[i];
    }
    cout << "\n";
}
