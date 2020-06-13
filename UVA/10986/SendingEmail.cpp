#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
    int server, latency;

    bool operator<(const Edge& other) const
    {
        return other.latency < latency;
    }
};

int nServers, nCables, source, destiny;
vector<Edge> graph[20005];
int latencies[20005];

int dijkstra(int start, int end)
{
    for (int i = 0; i < nServers; i++)
        latencies[i] = INF;
    latencies[start] = 0;
    priority_queue<Edge> pq;
    pq.push({start, 0});
    Edge current;
    while (!pq.empty())
    {
        current = pq.top(), pq.pop();

        if (current.latency <= latencies[current.server])
        {
            for (Edge v : graph[current.server])
            {
                int w = v.latency + current.latency;
                if (w < latencies[v.server])
                {
                    latencies[v.server] = w;
                    pq.push({v.server, w});
                }
            }
        }
    }
    return latencies[end];
}

int main()
{
    int t, scenario = 1;
    cin >> t;
    while (t--)
    {
        cin >> nServers >> nCables >> source >> destiny;
        for (int i = 0; i < nServers; i++)
            graph[i].clear();
        for (int i = 0; i < nCables; i++)
        {
            int from, to, latency;
            cin >> from >> to >> latency;
            graph[from].push_back({to, latency});
            graph[to].push_back({from, latency});
        }
        cout << "Case #" << scenario++ << ": ";
        int latency = dijkstra(source, destiny);
        if (latency != INF)
            cout << latency << endl;
        else
            cout << "unreachable" << endl;
    }
    return 0;
}