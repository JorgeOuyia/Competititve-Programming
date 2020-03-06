#include <iostream>

using namespace std;

int n, val, total, res, scenario;
int matrix[1005];

int main()
{
    scenario = 1;
    while (cin >> n && n != 0)
    {
        for (int i = 0; i < n; i++)
            matrix[i] = 0;
        total = 0, res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> val;
                total += val;
                matrix[i] += val;
                matrix[j] -= val;
            }
        }
        for (int i = 0; i < n; i++)
            if (matrix[i] >= 0)
                res += matrix[i];
        cout << scenario << ". " << total << " " << res << endl;
        scenario++;
    }
    return 0;
}