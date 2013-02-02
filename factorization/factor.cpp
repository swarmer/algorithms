#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

typedef vector<int>::iterator ivit;


vector<int> primes(int max)
{
    bool *sieve = new bool[max + 1];
    for (int i = 2; i <= max; ++i)
    {
        sieve[i] = true;
    }
    int i_max = ceil(sqrt(max));
    for (int i = 2; i <= i_max; ++i)
    {
        if (sieve[i])
        {
            for (int j = i * i; j <= max; j += i)
            {
                sieve[j] = false;
            }
        }
    }

    vector<int> result;
    for (int i = 2; i <= max; ++i)
    {
        if (sieve[i])
        {
            result.push_back(i);
        }
    }
    delete[] sieve;
    return result;
}

vector<int> factorize(int n)
{
    vector<int> divs;
    if (n == 1)
    {
        divs.push_back(1);
        return divs;
    }

    vector<int> ps = primes(ceil(sqrt(n)));
    for (ivit it = ps.begin(); it != ps.end(); ++it)
    {
        int p = *it;
        if (p * p > n)
            break;
        while (n % p == 0)
        {
            divs.push_back(p);
            n /= p;
        }
    }
    if (n > 1)
        divs.push_back(n);

    return divs;
}

int main(int argc, char *argv[])
{
    int n;
    sscanf(argv[1], "%d", &n);
    vector<int> divs = factorize(n);
    for (vector<int>::iterator it = divs.begin(); it != divs.end(); ++it)
    {
        cout << *it << '\n';
    }
}