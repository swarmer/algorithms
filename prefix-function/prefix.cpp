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


int main(int argc, char **argv)
{
    string s;
    cin >> s;
    size_t n = s.size();
    vector<int> p(n);
    for (int i = 1; i < n; ++i) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j])
            j = p[j - 1];
        if (s[i] == s[j])
            ++j;
        p[i] = j;
    }
    for (size_t i = 0; i < p.size(); ++i) {
        cout << p[i];
    }
    cout << "\n";
}
