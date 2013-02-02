#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    char *s1 = argv[1];
    char *s2 = argv[2];

    int max_begin, max_end, max_length = 0;
    for (int i = 0; s1[i] != 0; ++i)
    {
        for (int j = 0; s2[j] != 0; ++j)
        {
            for (int k = 0; k < i && k < j; ++k)
            {
                if (s1[i - k] != s2[j - k])
                    break;
                if (k + 1 > max_length)
                {
                    max_length = k + 1;
                    max_begin = i - k;
                    max_end = i;
                }
            }
        }
    }

    for (int i = max_begin; i <= max_end; ++i)
    {
        cout << s1[i];
    }
    cout << "\n";
}
