#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge
{
    long long int from, to, cost;

    bool operator<(const Edge& other) const
    {
        return other.cost < cost;
    }
};

long long int junctions, roads, from, to, cost, mstSum, total;
long long int parents[200005];
long long int sz[200005];
priority_queue<Edge> pq;

int find(int x)
{
    if (x == parents[x])
        return x;
    return parents[x] = find(parents[x]);
}

void connect(int x, int y, int cost)
{
    x = find(x), y = find(y);

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
    while (cin >> junctions >> roads && (junctions != 0 || roads != 0))
    {
        mstSum = 0;
        total = 0;
        for (int i = 0; i < junctions; i++)
            parents[i] = i, sz[i] = 1;
        for (int i = 0; i < roads; i++)
        {
            cin >> from >> to >> cost;
            total += cost;
            pq.push({ from, to, cost });
        }
        Edge current;
        while (!pq.empty())
        {
            current = pq.top(), pq.pop();
            connect(current.from, current.to, current.cost);
        }
        cout << total - mstSum << endl;
    }
    return 0;
}