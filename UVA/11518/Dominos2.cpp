#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

int pieces, edges, down, from, to, piece;
vector<int> graph[10005];
bool visited[10005];

void dfs(int u)
{
    visited[u] = true;

    for (int v : graph[u])
    {
        if (!visited[v])
            dfs(v);
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> pieces >> edges >> down;

        for (int i = 1; i <= pieces; i++)
            graph[i].clear(), visited[i] = false;

        for (int i = 0; i < edges; i++)
        {
            cin >> from >> to;
            graph[from].push_back(to);
        }
        int res = 0;
        while (down--)
        {
            cin >> piece;
            dfs(piece);
        }
        for (int i = 0; i <= pieces; i++)
            res += visited[i];
        cout << res << endl;
    }
    return 0;
}