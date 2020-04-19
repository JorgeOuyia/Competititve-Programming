#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

struct Edge
{
    int node, dist;
};

vector<Edge> graph[10005];
bool visited[10005];
string line;
int from, to, dist, maxNode, maxDist, longestNode;

void dfs(int u, int dist)
{
    visited[u] = true;
    if (dist > maxDist)
        maxDist = dist, longestNode = u;
    for (Edge v : graph[u])
    {
        if (!visited[v.node])
            dfs(v.node, dist + v.dist);
    }
}

int main()
{
    longestNode = maxDist = maxNode = -1;
    while (getline(cin, line))
    {
        if (!line.empty())
        {
            istringstream ss(line);
            ss >> from >> to >> dist;
            graph[from].push_back({ to, dist });
            graph[to].push_back({ from, dist });
            maxNode = max(max(from, to), maxNode);
        }
        else
        {
            for (int i = 1; i <= maxNode; i++)
                visited[i] = false;
            dfs(1, 0);
            for (int i = 1; i <= maxNode; i++)
                visited[i] = false;
            dfs(longestNode, 0);
            cout << maxDist << endl;
            for (int i = 1; i <= maxNode; i++)
                graph[i].clear();
            longestNode = maxDist = maxNode = -1;
        }
    }
    for (int i = 1; i <= maxNode; i++)
        visited[i] = false;
    dfs(1, 0);
    for (int i = 1; i <= maxNode; i++)
        visited[i] = false;
    dfs(longestNode, 0);
    cout << maxDist << endl;
    for (int i = 1; i <= maxNode; i++)
        graph[i].clear();
    longestNode = maxDist = maxNode = -1;
    return 0;
}