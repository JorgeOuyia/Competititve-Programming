#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int edges, from, to, querys;
vector<int> graph[25];
int distances[25];

int bfs(int source, int destiny)
{
    for (int i = 1; i <= 20; i++)
        distances[i] = INF;
    distances[source] = 0;
    queue<int> q;
    q.push(source);
    int current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current == destiny)
            return distances[current];

        for (int v : graph[current])
        {
            if (distances[v] > distances[current] + 1)
                distances[v] = distances[current] + 1, q.push(v);
        }
    }
    return -1;
}

int main()
{
    int scenario = 1;
    while (cin >> edges)
    {
        for (int i = 0; i <= 20; i++)
            graph[i].clear();
        for (int i = 0; i < edges; i++)
            cin >> to, graph[1].push_back(to), graph[to].push_back(1);
        for (int i = 2; i <= 19; i++)
        {
            cin >> edges;
            while (edges--)
                cin >> to, graph[i].push_back(to), graph[to].push_back(i);
        }
        cin >> querys;
        cout << "Test Set #" << scenario++ << endl;
        while (querys--)
        {
            cin >> from >> to;
            if (from < 10)
                cout << " " << from << " to ";
            else
                cout << from << " to ";
            if (to < 10)
                cout << " " << to << ": ";
            else
                cout << to << ": ";
            cout << bfs(from, to) << endl;
        }
        if (cin)
            cout << endl;
    }
    return 0;
}