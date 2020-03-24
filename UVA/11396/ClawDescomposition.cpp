#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int vertex, a, b, flag;
vector<int> graph[305];
bool visited[305];
int bipartite[305];

bool bfs(int u)
{
    visited[u] = true;
    bipartite[u] = 1;
    queue<int> q;
    q.push(u);
    int current;
    while (!q.empty())
    {
        current = q.front();
        q.pop();

        for (int v : graph[current])
        {
            if (bipartite[v] == -1)
            {
                visited[v] = true;
                bipartite[v] = 1 - bipartite[current];
                q.push(v);
            }
            else if (bipartite[v] == bipartite[current])
                return false;
        }
    }
    return true;
}

int main()
{
    while (cin >> vertex && vertex != 0)
    {
        flag = 1;
        for (int i = 1; i <= vertex; i++)
            graph[i].clear(), visited[i] = false, bipartite[i] = -1;
        while (cin >> a >> b && (a != 0 || b != 0))
        {
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        for (int i = 1; i <= vertex; i++)
        {
            if (!visited[i])
                flag &= bfs(i);
            if (!flag)
                break;
        }
        if (flag)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}