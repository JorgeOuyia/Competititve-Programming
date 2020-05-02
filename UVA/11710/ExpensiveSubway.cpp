#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Edge
{
    int from, to, cost;

    bool operator<(const Edge &other) const
    {
        return other.cost < cost;
    }
};

int stations, connections, cost, mstSum;
string name, from, to, start;
priority_queue<Edge> graph;
int parents[405];
int sz[405];
unordered_map<string, int> hashMap;

int find(int x)
{
    if (parents[x] == x)
        return x;
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
    while (cin >> stations >> connections && (stations || connections))
    {
        hashMap.clear();
        mstSum = 0;
        for (int i = 1; i <= stations; i++)
            parents[i] = i, sz[i] = 1;
        int id = 1;
        for (int i = 0; i < stations; i++)
        {
            cin >> name;
            hashMap[name] = id++;
        }
        for (int i = 0; i < connections; i++)
        {
            cin >> from >> to >> cost;
            graph.push({hashMap[from], hashMap[to], cost});
            graph.push({hashMap[to], hashMap[from], cost});
        }
        cin >> start;
        Edge current;
        while (!graph.empty())
        {
            current = graph.top(), graph.pop();
            int from = current.from;
            int to = current.to;
            int c = current.cost;
            connect(from, to, c);
        }
        unordered_set<int> differentParents;
        for (int i = 1; i <= stations; i++)
            differentParents.insert(find(i));
        if (differentParents.size() != 1)
            cout << "Impossible" << endl;
        else
            cout << mstSum << endl;
    }
    return 0;
}