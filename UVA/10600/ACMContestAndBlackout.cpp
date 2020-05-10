#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Edge
{
    int from, to, cost;

    bool operator<(const Edge &other) const
    {
        return cost < other.cost;
    }

    bool operator==(const Edge &other) const
    {
        return from == other.from && to == other.to && cost == other.cost;
    }

    bool operator!=(const Edge &other) const
    {
        return other.from != from || other.to != to || other.cost != cost;
    }
};

struct Edge_Hash
{
    size_t operator()(const Edge &edge) const
    {
        return hash<int>()(edge.from) ^ hash<int>()(edge.to) ^ hash<int>()(edge.cost);
    }
};

int schools, connections, from, to, cost, mstSum;
int parents[105];
int sz[105];
vector<Edge> graph;
unordered_set<Edge, Edge_Hash> used;

int find(int x)
{
    if (parents[x] == x)
        return x;
    return parents[x] = find(parents[x]);
}

bool connect(int x, int y, int cost)
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
        return true;
    }
    return false;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> schools >> connections;
        graph.clear();
        used.clear();
        for (int i = 1; i <= schools; i++)
            parents[i] = i, sz[i] = i;
        while (connections--)
        {
            cin >> from >> to >> cost;
            graph.push_back({from, to, cost});
        }
        sort(graph.begin(), graph.end());
        mstSum = 0;
        int firstMin = 0x3f3f3f3f;
        for (int i = 0; i < graph.size(); i++)
        {
            int f = graph[i].from;
            int t = graph[i].to;
            int c = graph[i].cost;
            if (connect(f, t, c))
                used.insert({f, t, c});
        }
        firstMin = mstSum;
        cout << firstMin << " ";
        for (int i = 1; i <= schools; i++)
            parents[i] = i, sz[i] = i;
        mstSum = 0;
        int secondMin = 0x3f3f3f3f;
        auto it = used.begin();
        for (int i = 0; i < graph.size(); i++)
        {
            int edgesConnected = 0;
            mstSum = 0;
            for (int i = 1; i <= schools; i++)
                parents[i] = i, sz[i] = 1;
            for (int j = 0; j < graph.size(); j++)
            {
                if (graph[j] != *it)
                {
                    int f = graph[j].from;
                    int t = graph[j].to;
                    int c = graph[j].cost;
                    if (connect(f, t, c))
                        edgesConnected++;
                }
            }
            if (edgesConnected == schools - 1)
                secondMin = min(secondMin, mstSum);
            ++it;
            if (it == used.end())
                break;
        }
        if (secondMin != 0x3f3f3f3f)
            cout << secondMin << endl;
        else
            cout << firstMin << endl;
    }
    return 0;
}