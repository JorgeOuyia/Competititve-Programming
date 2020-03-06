#include <iostream>
#include <vector>

using namespace std;

int cities, roads, cc, a, b;
vector<int> graph[800005];
bool visited[800005];

void dfs(int v)
{
    visited[v] = true;
    for (int u : graph[v])
    {
        if (!visited[u])
            dfs(u);
    }
}

int main()
{
    while (cin >> cities >> roads)
    {
        for (int i = 0; i < cities; i++)
            graph[i].clear(), visited[i] = false;
        cc = 0;
        for (int i = 0; i < roads; i++)
        {
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        for (int i = 0; i < cities; i++)
        {
            if (!visited[i])
            {
                cc++;
                dfs(i);
            }
        }
        cout << cc - 1 << endl;
    }
    return 0;
}