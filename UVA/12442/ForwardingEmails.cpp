#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int martians, u, v, maxDist, selected;
bool visited[50005];
vector<int> graph[50005];
int dp[50005];

int dfs(int u)
{
    visited[u] = true;
    int res = 0;
    for (int v : graph[u])
    {
        if (!visited[v])
            res += 1 + dfs(v);
    }
    visited[u] = false;
    return dp[u] = res;
}

int main()
{
    int t, scenario = 1;
    cin >> t;
    while (t--)
    {
        cin >> martians;
        maxDist = -1;
        selected = 1;
        for (int i = 1; i <= martians; i++)
        {
            visited[i] = false;
            graph[i].clear();
            dp[i] = -1;
        }
        for (int i = 0; i < martians; i++)
        {
            cin >> u >> v;
            graph[u].push_back(v);
        }
        for (int i = 1; i <= martians; i++)
        {
            if (dp[i] == -1)
                dfs(i);
            if (dp[i] > maxDist)
                selected = i, maxDist = dp[i];
        }
        cout << "Case " << scenario << ": " << selected << endl;
        scenario++;
    }
    return 0;
}