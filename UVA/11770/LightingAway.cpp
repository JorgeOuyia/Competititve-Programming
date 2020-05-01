#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

int lights, edges, from, to;
vector<int> graph[10005];
bool visited[10005];

void dfs(int u)
{
    visited[u] = true;

    for (int v : graph[u])
        if (!visited[v])
            dfs(v);
}

int stronglyConnectedComponents()
{
    int scc = 0;

    stack<int> components;
    for (int i = 1; i <= lights; i++)
        if (!visited[i])
            dfs(i), components.push(i);
    for (int i = 1; i <= lights; i++)
        visited[i] = false;
    int current;
    while (!components.empty())
    {
        current = components.top(), components.pop();
        if (!visited[current])
            dfs(current), scc++;
    }
    return scc;
}

int main()
{
    int scenario = 1;
    int t;
    cin >> t;
    while (t--)
    {
        cin >> lights >> edges;
        for (int i = 1; i <= lights; i++)
            graph[i].clear(), visited[i] = false;

        for (int i = 0; i < edges; i++)
        {
            cin >> from >> to;
            graph[from].push_back(to);
        }

        cout << "Case " << scenario++ << ": " << stronglyConnectedComponents() << endl;
    }
    return 0;
}