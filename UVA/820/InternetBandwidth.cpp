#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

int nodes, source, sink, connections;
int flows[105][105];
int visited[105];
int parents[105];
vector<int> graph[105];

bool bfs(int start, int end)
{
    for (int i = 1; i <= nodes; i++)
        visited[i] = false, parents[i] = i;
    visited[start] = true;
    queue<int> q;
    q.push(start);
    int current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (int v : graph[current])
        {
            if (!visited[v] && flows[current][v] > 0)
                visited[v] = true, q.push(v), parents[v] = current;
        }
    }
    return visited[end];
}

int fordFulkerson()
{
    int maxBandwidth = 0;
    while (bfs(source, sink))
    {
        int minFlow = INF;
        int u = sink;
        while (u != parents[u])
            minFlow = min(minFlow, flows[parents[u]][u]), u = parents[u];
        u = sink;
        while (u != parents[u])
        {
            flows[parents[u]][u] -= minFlow;
            flows[u][parents[u]] += minFlow;
            u = parents[u];
        }
        maxBandwidth += minFlow;
    }
    return maxBandwidth;
}

int main()
{
    int scenario = 1;
    while (cin >> nodes && nodes)
    {
        for (int i = 1; i <= nodes; i++)
            for (int j = 1; j <= nodes; j++)
                flows[i][j] = 0;
        for (int i = 1; i <= nodes; i++)
            graph[i].clear();

        cin >> source >> sink >> connections;
        while (connections--)
        {
            int from, to, bandwidth;
            cin >> from >> to >> bandwidth;
            graph[from].push_back(to);
            graph[to].push_back(from);
            flows[from][to] += bandwidth;
            flows[to][from] += bandwidth;
        }
        cout << "Network " << scenario++ << endl;
        cout << "The bandwidth is " << fordFulkerson() << "." << endl;
        cout << endl;
    }
    return 0;
}