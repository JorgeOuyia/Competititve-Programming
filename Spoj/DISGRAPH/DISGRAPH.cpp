#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <set>

using namespace std;

int cities, to, longestNode, maxDist;
unordered_set<int> graph[1405];
bool visited[1405];
int parents[1405];
string line;

void dfs(int u, int dist)
{
    visited[u] = true;
    if (dist > maxDist)
        longestNode = u, maxDist = dist;

    for (int v : graph[u])
    {
        if (!visited[v])
            dfs(v, dist + 1);
    }
}

bool bfs(int start, int end)
{
    for (int i = 0; i < cities; i++)
        visited[i] = false, parents[i] = i;
    visited[start] = true;
    queue<int> q;
    q.push(start);
    int current;
    while (!q.empty())
    {
        current = q.front();
        q.pop();

        for (int v : graph[current])
        {
            if (!visited[v])
            {
                parents[v] = current;
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return visited[end];
}

int maxFlow()
{
    int disjointPaths = 0;
    while (bfs(0, longestNode))
    {
        int v = longestNode;
        int u = parents[v];
        disjointPaths++;
        while (u != v)
        {
            graph[u].erase(v);
            graph[v].erase(u);
            v = u;
            u = parents[v];
        }
    }
    return disjointPaths;
}

int main()
{
    while (cin >> cities)
    {
        cin.ignore();
        maxDist = -1;
        for (int i = 0; i < cities; i++)
        {       
            visited[i] = false;  
            parents[i] = i;
            getline(cin, line);
            istringstream ss(line);
            while (ss >> to)
            {
                graph[i].insert(to);
            }
        }
        dfs(0, 0);
        cout << maxFlow() << endl;
    }
    return 0;
}