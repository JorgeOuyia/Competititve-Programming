#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
    int node, time;

    bool operator<(const Edge &other) const
    {
        return other.time < time;
    }
};

int intersections, n, to, delay, first, last;
vector<Edge> graph[15];
vector<int> path;
int times[15], parents[15];

void dijkstra(int start)
{
    times[start] = 0;
    priority_queue<Edge> pq;
    pq.push({start, 0});
    Edge current;
    while (!pq.empty())
    {
        current = pq.top();
        pq.pop();

        if (times[current.node] >= current.time)
        {
            for (Edge to : graph[current.node])
            {
                int time = current.time + to.time;
                if (times[to.node] > time)
                {
                    times[to.node] = time;
                    pq.push({to.node, time});
                    parents[to.node] = current.node;
                }
            }
        }
    }
}

int main()
{
    int scenario = 1;
    while (cin >> intersections && intersections != 0)
    {
        path.clear();
        for (int i = 1; i <= intersections; i++)
            times[i] = INF, graph[i].clear(), parents[i] = i;
        for (int i = 1; i <= intersections; i++)
        {
            cin >> n;
            for (int j = 0; j < n; j++)
            {
                cin >> to >> delay;
                graph[i].push_back({to, delay});
            }
        }
        cin >> first >> last;
        dijkstra(first);
        int u = last;
        path.push_back(u);
        while (u != parents[u])
        {
            path.push_back(parents[u]);
            u = parents[u];
        }
        reverse(path.begin(), path.end());
        cout << "Case " << scenario << ": Path =";
        for (int v : path)
            cout << " " << v;
        cout << "; " << times[last] << " second delay" << endl;
        scenario++;
    }
    return 0;
}