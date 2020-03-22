#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int cities, roads, soldiers, from, to, flag, area, strength;
vector<int> graph[1000005];
unordered_map<int, unordered_set<int>> guarded;
bool visited[1000005];

void dfs(int soldier, int u, int strength)
{
    visited[u] = true;
    guarded[u].insert(soldier);
    if (strength > 0)
    {
        for (int v : graph[u])
        {
            if (!visited[v])
                dfs(soldier, v, strength - 1);
        }
    }
    visited[u] = false;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> cities >> roads >> soldiers;
        guarded.clear();
        flag = 1;
        for (int i = 1; i <= cities; i++)
            graph[i].clear(), visited[i] = false;
        for (int i = 0; i < roads; i++)
        {
            cin >> from >> to;
            graph[from].push_back(to);
            graph[to].push_back(from);
        }
        for (int i = 0; i < soldiers; i++)
        {
            cin >> area >> strength;
            dfs(i + 1, area, strength);
        }
        for (auto it = guarded.begin(); it != guarded.end(); ++it)
        {
            if (it->second.size() > 1)
                flag = 0;
            visited[it->first] = true;
        }
        for (int i = 1; i <= cities; i++)
            if (!visited[i])
                flag = 0;
        if (flag)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}