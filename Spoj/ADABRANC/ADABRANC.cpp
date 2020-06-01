#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Edge
{
    int type, query, from, to, weight;

    bool operator<(const Edge &other) const
    {
        if (weight != other.weight)
            return weight > other.weight;
        return type < other.type;
    }
};

int fruits, edges, querys, from, to, weight, start;
int parents[100005], sz[100005];
vector<Edge> graph;

int find(int x)
{
    if (parents[x] == x)
        return x;
    return parents[x] = find(parents[x]);
}

void connect(int x, int y)
{
    x = find(x);
    y = find(y);

    if (x != y)
    {
        if (sz[x] >= sz[y])
            parents[y] = x, sz[x] += sz[y], sz[y] = 0;
        else
            parents[x] = y, sz[y] += sz[x], sz[x] = 0;
    }
}

int main()
{
    while (cin >> fruits >> edges >> querys)
    {
        graph.clear();
        int *res = new int[querys];
        for (int i = 0; i < fruits; i++)
            parents[i] = i, sz[i] = 1;
        for (int i = 0; i < edges; i++)
        {
            cin >> from >> to >> weight;
            graph.push_back({0, -1, from, to, weight});
        }
        for (int i = 0; i < querys; i++)
        {
            cin >> start >> weight;
            graph.push_back({1, i, start, -1, weight});
        }
        sort(graph.begin(), graph.end());
        for (int i = 0; i < graph.size(); i++)
        {
            if (!graph[i].type)
                connect(graph[i].from, graph[i].to);
            else
                res[graph[i].query] = sz[find(graph[i].from)];
        }
        for (int i = 0; i < querys; i++)
            cout << res[i] << endl;
    }
    return 0;
}