#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int a, b, c, d, n, total;
int graph[105][105];

int main()
{
    int scenario = 1;
    while (cin >> a >> b && (a != 0 || b != 0))
    {
        n = 0;
        total = 0;
        for (int i = 1; i <= 100; i++)
            for (int j = 1; j <= 100; j++)
                graph[i][j] = 0x3f3f3f3f;
        graph[a][b] = 1;
        while (cin >> c >> d && (c != 0 || d != 0))
        {
            graph[c][d] = 1;
        }
        for (int k = 1; k <= 100; k++)
        {
            for (int i = 1; i <= 100; i++)
            {
                for (int j = 1; j <= 100; j++)
                {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
        for (int i = 1; i <= 100; i++)
        {
            for (int j = 1; j <= 100; j++)
            {
                if (i != j && graph[i][j] != 0x3f3f3f3f)
                    total += graph[i][j], n++;
            }
        }
        cout << "Case " << scenario << ": average length between pages = ";
        cout << fixed << setprecision(3) << (double)total / (double)n << " clicks" << endl;
        scenario++;
    }
    return 0;
}