#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge
{
    int node, dist;

    bool operator<(const Edge& other) const
    {
        return other.dist < dist;
    }
};

int t, a, b;
int nodes, edges;
vector<int> graph[10005];
int distances[10005];

int dijkstra(int start, int end)
{
    distances[start] = 0;
    priority_queue<Edge> pq;
    pq.push({ start, 0 });
    while (!pq.empty())
    {
        Edge n = pq.top();
        pq.pop();

        if (distances[n.node] >= n.dist)
        {
            for (int D : graph[n.node])
            {
                int peso = n.dist + 1;
                if (distances[D] > peso)
                {
                    distances[D] = peso;
                    pq.push({ D, peso });
                }
            }
        }
    }
    return distances[end];
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> nodes >> edges;
        for (int i = 1; i <= nodes; i++)
            graph[i].clear(), distances[i] = 0x3f3f3f3f;
        for (int i = 0; i < edges; i++)
        {
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        cout << dijkstra(1, nodes) << endl;
    }
    return 0;
}