#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>

#include <unordered_set>

#define INF 5000

using namespace std;

int t, buildings, roads, u, v, dist, first, last;
int graph[105][105];

int main()
{
    cin >> t;
    int scenario = 1;
    while (t--)
    {
        cin >> buildings >> roads;
        for (int i = 0; i < buildings; i++)
        {
            for (int j = 0; j < buildings; j++)
            {
                graph[i][j] = INF;
                if (i == j)
                    graph[i][j] = 0;
            }
        }
        for (int i = 0; i < roads; i++)
        {
            cin >> u >> v;
            graph[u][v] = 1;
            graph[v][u] = 1;
        }
        cin >> first >> last;
        for (int k = 0; k < buildings; k++)
        {
            for (int i = 0; i < buildings; i++)
            {
                for (int j = 0; j < buildings; j++)
                {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
        dist = 0;
        for (int i = 0; i < buildings; i++)
        {
            if (graph[first][i] != INF && graph[i][last] != INF)
                dist = max(dist, graph[first][i] + graph[i][last]);
        }
        cout << "Case " << scenario << ": " << dist << endl;
        scenario++;
    }
    return 0;
}