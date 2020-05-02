#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Edge
{
    int from, to, cost;

    bool operator<(const Edge &other) const
    {
        return other.cost < cost;
    }
};

int locations, roads, airportCost, from, to, cost, mstSum;
int parents[10005];
int sz[10005];
priority_queue<Edge> graph;
unordered_set<int> sets;

int find(int x)
{
    if (parents[x] == x)
        return parents[x];
    return parents[x] = find(parents[x]);
}

void connect(int x, int y, int cost)
{
    x = find(x);
    y = find(y);

    if (x != y)
    {
        if (sz[x] >= sz[y])
            parents[y] = x, sz[x] += sz[y];
        else
            parents[x] = y, sz[y] += sz[x];
        mstSum += cost;
    }
}

int main()
{
    int scenario = 1;
    int t;
    cin >> t;
    while (t--)
    {
        cin >> locations >> roads >> airportCost;
        sets.clear();
        mstSum = 0;
        while (!graph.empty())
            graph.pop();
        for (int i = 0; i <= locations; i++)
            parents[i] = i, sz[i] = 1;
        for (int i = 0; i < roads; i++)
        {
            cin >> from >> to >> cost;
            graph.push({from, to, cost});
        }
        Edge current;
        while (!graph.empty() && graph.top().cost < airportCost)
        {
            current = graph.top(), graph.pop();
            int f = current.from, t = current.to, c = current.cost;
            connect(f, t, c);
        }
        for (int i = 1; i <= locations; i++)
            sets.insert(find(i));
        int airports = sets.size();
        int airportsPrice = airports * airportCost;
        int res = airportsPrice + mstSum;
        cout << "Case #" << scenario++ << ": " << res << " " << airports << endl;
    }
    return 0;
}