#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

int t, n, cont;

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        cont = 0;
        while (n > 1)
        {
            if (n % 3 == 0)
                n /= 3, cont++;
            else
                n--, cont++;
        }
        cout << cont << endl;
    }
    return 0;
}