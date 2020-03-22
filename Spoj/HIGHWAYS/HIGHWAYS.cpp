#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
    int node, dist;

    bool operator<(const Edge& other) const
    {
        return other.dist < dist;
    }
};

int cities, roads, first, last, u, v, d;
vector<Edge> graph[1000005];
int distances[1000005];

int dijkstra(int start, int end)
{
    if (distances[end] != INF)
        return distances[end];
    distances[start] = 0;
    priority_queue<Edge> pq;
    pq.push({start, 0});
    Edge current;
    while (!pq.empty())
    {
        current = pq.top(), pq.pop();

        if (distances[current.node] >= current.dist)
        {
            for (Edge to : graph[current.node])
            {
                int dist = current.dist + to.dist;
                if (dist < distances[to.node])
                {
                    distances[to.node] = dist;
                    pq.push({to.node, dist});
                }
            }
        }
    }
    return distances[end];
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> cities >> roads >> first >> last;
        for (int i = 1; i <= cities; i++)
            graph[i].clear(), distances[i] = INF;
        for (int i = 0; i < roads; i++)
        {
            cin >> u >> v >> d;
            graph[u].push_back({v, d});
            graph[v].push_back({u, d});
        }
        cout << (dijkstra(first, last) != INF ? to_string(dijkstra(first, last)) : "NONE") << endl;
    }
    return 0;
}