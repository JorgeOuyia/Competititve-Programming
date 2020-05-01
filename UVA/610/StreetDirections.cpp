#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

int intersections, roads, from, to, discoveryTime;
unordered_set<int> graph[1005];
int low[1005], tin[1005];
bool visited[1005];

void bridges(int v, int p)
{
    visited[v] = true;
    tin[v] = low[v] = discoveryTime++;
    for (int to : graph[v])
    {
        if (to == p)
            continue;
        if (!visited[to])
        {
            bridges(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] <= tin[v])
                graph[to].erase(v);
        }
        else if (to != p)
        {
            low[v] = min(low[v], tin[to]);
            graph[to].erase(v);
        }
    }
}

int main()
{
    int scenario = 1;
    while (cin >> intersections >> roads && (intersections || roads))
    {
        for (int i = 1; i <= intersections; i++)
            low[i] = -1, tin[i] = -1, visited[i] = false, graph[i].clear();
        discoveryTime = 0;

        for (int i = 0; i < roads; i++)
        {
            cin >> from >> to;
            graph[from].insert(to);
            graph[to].insert(from);
        }
        for (int i = 1; i <= intersections; i++)
            if (!visited[i])
                bridges(i, i);
        cout << scenario++ << endl;
        cout << endl;
        for (int i = 1; i <= intersections; i++)
        {
            for (int j : graph[i])
            {
                cout << i << " " << j << endl;
            }
        }
        cout << "#" << endl;
    }
    return 0;
}