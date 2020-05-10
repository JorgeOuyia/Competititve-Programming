#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge
{
    int from, to, flow;

    bool operator<(const Edge &other) const
    {
        return other.flow > flow;
    }
};

int intersections, roads, from, to, flow;
int parents[105];
int sz[105];
priority_queue<Edge> graph;

int find(int x)
{
    if (parents[x] == x)
        return x;
    return parents[x] = find(parents[x]);
}

bool connect(int x, int y)
{
    x = find(x);
    y = find(y);

    if (x != y)
    {
        if (sz[x] >= sz[y])
            parents[y] = x, sz[x] += sz[y];
        else
            parents[x] = y, sz[y] += sz[x];
        return true;
    }
    return false;
}

int minimumCapacity()
{
    int minimum = 0x3f3f3f3f;
    Edge current;
    while (!graph.empty())
    {
        current = graph.top(), graph.pop();
        int fr = current.from;
        int t = current.to;
        int fl = current.flow;
        if (connect(fr, t))
            minimum = min(minimum, fl);
    }
    return minimum;
}

int main()
{
    int scenario = 1;
    int t;
    cin >> t;
    while (t--)
    {
        cin >> intersections >> roads;
        for (int i = 0; i < intersections; i++)
            parents[i] = i, sz[i] = 1;
        while (roads--)
        {
            cin >> from >> to >> flow;
            graph.push({from, to, flow});
            graph.push({to, from, flow});
        }
        cout << "Case #" << scenario++ << ": " << minimumCapacity() << endl;
    }
    return 0;
}