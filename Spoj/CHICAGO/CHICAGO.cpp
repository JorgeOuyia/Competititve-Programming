#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>

using namespace std;

struct Edge
{
    int node;
    double percent;

    bool operator<(const Edge& other) const
    {
        return other.percent > percent;
    }
};

int intersections, streets, from, to;
double percent, minPercent;
vector<Edge> graph[105];
double probabilities[105];

double dijkstra(int start, int end)
{
    probabilities[start] = 1;
    priority_queue<Edge> pq;
    pq.push({start, 1});
    Edge current;
    while (!pq.empty())
    {
        current = pq.top(), pq.pop();

        if (probabilities[current.node] <= current.percent)
        {
            for (Edge to : graph[current.node])
            {
                double percent = current.percent * to.percent;
                if (probabilities[to.node] < percent)
                {
                    probabilities[to.node] = percent;
                    pq.push({to.node, percent});
                }
            }
        }
    }
    return probabilities[end];
}

int main()
{
    while (cin >> intersections && intersections != 0)
    {
        cin >> streets;
        minPercent = -1;
        for (int i = 1; i <= intersections; i++)
            graph[i].clear(), probabilities[i] = 0;
        for (int i = 0; i < streets; i++)
        {
            cin >> from >> to >> percent;
            graph[from].push_back({to, percent / 100});
            graph[to].push_back({from, percent / 100});
        }
        cout << fixed << setprecision(6);
        cout << dijkstra(1, intersections) * 100 << " percent" << endl;
    }
    return 0;
}