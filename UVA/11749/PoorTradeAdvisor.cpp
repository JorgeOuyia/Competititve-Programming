#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define INF -2147483648

using namespace std;

struct Edge
{
    int node, PPA;
};

int cities, roads, maxPPA, from, to, PPA;
vector<Edge> graph[505];
bool visited[505];

int dfs(int u)
{
    int res = 1;

    for (Edge v : graph[u])
    {
        if (visited[v.node] || v.PPA != maxPPA)
            continue;
        visited[v.node] = true;
        res += dfs(v.node);
    }
    return res;
}

int main()
{
    while (cin >> cities >> roads && (cities != 0 || roads != 0))
    {
        for (int i = 1; i <= cities; i++)
            visited[i] = false, graph[i].clear();
        maxPPA = INF;

        for (int i = 0; i < roads; i++)
        {
            cin >> from >> to >> PPA;
            graph[from].push_back({ to, PPA });
            graph[to].push_back({ from, PPA });
            maxPPA = max(maxPPA, PPA);
        }
        int res = 0;
        for (int i = 1; i <= cities; i++)
        {
            if (!visited[i])
                visited[i] = true, res = max(res, dfs(i));
        }
        cout << res << endl;
    }
    return 0;
}