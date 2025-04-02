#include <iostream>
#include <string>

using namespace std;

int main()
{
    string X = "abab";
    string Y = "abababab";

    int n = X.length(), m = Y.length();
    int *N = new int[n];
    int *M = new int[m];
    int Len, i = 0;
    N[0] = -1;

    while (i < n)
    {
        Len = N[i];
        while ((X[Len + 1] != X[i + 1]) && (Len >= 0))
        {
            Len = N[Len];
        }
        if (X[Len + 1] == X[i + 1])
        {
            N[i + 1] = Len + 1;
        }
        else
        {
            N[i + 1] = -1;
        }
        i++;
    }


    i = 0;
    Len = -1;
    while (i < m)
    {
        while (X[Len + 1] != Y[i] && Len >= 0)
        {
            Len = N[Len];
        }
        if (X[Len + 1] == Y[i])
        {
            Len++;
        }
        else
        {
            Len = -1;
        }
        if (Len == n - 1)
        {
            cout << "bilo na " << i - n + 2 << endl;
            i = i - n + 1;
        }
        i++;
    }

    return 0;
}