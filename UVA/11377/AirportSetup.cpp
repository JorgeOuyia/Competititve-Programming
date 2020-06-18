#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
    int node;
    int dist;

    bool operator<(const Edge &other) const
    {
        return other.dist < dist;
    }
};

int nCities, nRoutes, nAirports;
int haveAirport[2005];
int distances[2005];
vector<Edge> graph[2005];

bool dijkstra(int start, int end)
{
    for (int i = 1; i <= nCities; i++)
        distances[i] = INF;
    distances[start] = haveAirport[start] ? 0 : 1;
    priority_queue<Edge> pq;
    pq.push({start, 0});
    Edge current;
    while (!pq.empty())
    {
        current = pq.top(), pq.pop();

        if (current.dist <= distances[current.node])
        {
            for (Edge v : graph[current.node])
            {
                int w = current.dist + v.dist;
                if (distances[v.node] > w)
                {
                    distances[v.node] = w;
                    pq.push({v.node, w});
                }
            }
        }
    }
    return distances[end] != INF;
}

int main()
{
    int t, scenario = 1;
    cin >> t;
    while (t--)
    {
        cin >> nCities >> nRoutes >> nAirports;
        for (int i = 1; i <= nCities; i++)
            haveAirport[i] = 0, graph[i].clear();
        for (int i = 0; i < nAirports; i++)
        {
            int n;
            cin >> n;
            haveAirport[n] = 1;
        }
        for (int i = 0; i < nRoutes; i++)
        {
            int from, to;
            cin >> from >> to;
            graph[from].push_back({to, haveAirport[to] ? 0 : 1});
            graph[to].push_back({from, haveAirport[from] ? 0 : 1});
        }
        int querys;
        cin >> querys;
        cout << "Case " << scenario++ << ":" << endl;
        while (querys--)
        {
            int from, to;
            cin >> from >> to;
            if (!dijkstra(from, to))
                cout << -1 << endl;
            else
            {
                if (from != to)
                    cout << distances[to] + distances[from] << endl;
                else
                    cout << 0 << endl;
            }
        }
        cout << endl;
    }
    return 0;
}