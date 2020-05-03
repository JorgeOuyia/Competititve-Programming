#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <set>
#include <sstream>
#include <stack>

#define INF 0x3f3f3f3f

using namespace std;

int routers, querys, from, to;
string line;
set<int> graph[305];
int distances[305];
int parents[305];

int bfs(int source, int destiny)
{
    for (int i = 1; i <= routers; i++)
        distances[i] = INF, parents[i] = i;
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
                distances[v] = distances[current] + 1, parents[v] = current, q.push(v);
        }
    }
    return -1;
}

int main()
{
    while (cin >> routers)
    {
        for (int i = 1; i <= routers; i++)
            graph[i].clear();
        for (int i = 0; i < routers; i++)
        {
            cin >> line;
            istringstream ss(line);
            int source;
            ss >> source;
            int destiny;
            char trash;
            ss >> trash;
            while (ss >> destiny)
                graph[source].insert(destiny), ss >> trash;
        }
        cout << "-----" << endl;
        cin >> querys;
        while (querys--)
        {
            cin >> from >> to;
            int dist = bfs(from, to);
            if (dist < 0)
                cout << "connection impossible" << endl;
            else
            {
                int first = true;
                int u = to;
                stack<int> res;
                while (u != parents[u])
                {
                    res.push(u);
                    u = parents[u];
                }
                res.push(from);
                while (!res.empty())
                {
                    if (first)
                    {
                        first = false;
                        cout << res.top();
                    }
                    else
                    {
                        cout << " " << res.top();
                    }
                    res.pop();
                }
                cout << endl;
            }
        }
    }
    return 0;
}