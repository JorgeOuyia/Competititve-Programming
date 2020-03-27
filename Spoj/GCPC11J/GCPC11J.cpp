#include <iostream>
#include <vector>

using namespace std;

int t, computer, longestNode, maxDist, a, b;
vector<int> graph[100005];
bool visited[100005];

void dfs(int u, int dist)
{
    visited[u] = true;
    if (dist > maxDist)
        maxDist = dist, longestNode = u;
    for (int v : graph[u])
    {
        if (!visited[v])
            dfs(v, dist + 1);
    }
    visited[u] = false;
}

int main()
{
    cin >> t;
    while (t--)
    {
        maxDist = -1;
        cin >> computer;
        for (int i = 0; i < computer; i++)
            visited[i] = false, graph[i].clear();
        for (int i = 1; i < computer; i++)
        {
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        dfs(0, 0);
        dfs(longestNode, 0);
        if (maxDist % 2 == 1)
            cout << maxDist / 2 + 1 << endl;
        else
            cout << maxDist / 2 << endl;
    }
    return 0;
}