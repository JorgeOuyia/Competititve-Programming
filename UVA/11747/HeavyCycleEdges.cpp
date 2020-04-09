#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
    int from, to, dist;

    bool operator<(const Edge &other) const
    {
        return other.dist > dist;
    }
};

int nodes, edges, from, to, dist, components;
int parents[1005], sz[1005], valid[25005];
vector<Edge> graph;

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

int main()
{
    while (cin >> nodes >> edges && (nodes != 0 || edges != 0))
    {
        graph.clear();
        components = edges;
        for (int i = 0; i < nodes; i++)
            parents[i] = i, sz[i] = 1;
        for (int i = 0; i < edges; i++)
        {
            cin >> from >> to >> dist;
            graph.push_back({from, to, dist});
        }
        for (int i = 0; i <= edges; i++)
            valid[i] = true;
        sort(graph.begin(), graph.end());
        for (int i = 0; i < graph.size(); i++)
        {
            if (connect(graph[i].from, graph[i].to))
                components--, valid[i] = false;
        }
        if (!components)
            cout << "forest" << endl;
        else
        {
            int first = true;
            for (int i = 0; i < edges; i++)
            {
                if (valid[i])
                {
                    if (first)
                    {
                        first = false;
                        cout << graph[i].dist;
                    }
                    else
                        cout << " " << graph[i].dist;
                }
            }
            cout << endl;
        }
    }
    return 0;
}