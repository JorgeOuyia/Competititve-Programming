#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Point2D
{
    int x, y;

    bool operator==(const Point2D &other) const
    {
        return other.x == x && other.y == y;
    }
};

struct Edge
{
    int from, to;
    double cost;

    bool operator<(const Edge &other) const
    {
        return other.cost < cost;
    }
};

struct Point2D_Hash
{
    size_t operator()(const Point2D &point) const
    {
        size_t h1 = hash<int>()(point.x);
        size_t h2 = hash<int>()(point.y);

        return h1 ^ h2;
    }
};

int towns, x, y, connections, a, b;
Point2D hashMap[755];
unordered_map<Point2D, int, Point2D_Hash> reverseHashMap;
int parents[755];
int sz[755];
vector<Point2D> allPoints;
priority_queue<Edge> graph;

double calculateDistance(Point2D a, Point2D b)
{
    int x = (b.x - a.x) * (b.x - a.x);
    int y = (b.y - a.y) * (b.y - a.y);

    return sqrt(x + y);
}

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
    int t;
    cin >> t;
    while (t--)
    {
        cin >> towns;
        allPoints.clear();
        reverseHashMap.clear();
        for (int i = 1; i <= towns; i++)
            parents[i] = i, sz[i] = 1;
        for (int i = 0; i < towns; i++)
        {
            cin >> x >> y;
            hashMap[i + 1] = {x, y};
            reverseHashMap[{x, y}] = i + 1;
            allPoints.push_back({x, y});
        }
        for (int i = 0; i < allPoints.size(); i++)
        {
            int from = reverseHashMap[allPoints[i]];
            for (int j = i + 1; j < allPoints.size(); j++)
            {
                int to = reverseHashMap[allPoints[j]];
                double cost = calculateDistance(allPoints[i], allPoints[j]);
                graph.push({from, to, cost});
            }
        }
        cin >> connections;
        while (connections--)
        {
            cin >> a >> b;
            connect(a, b);
        }
        Edge current;
        vector<Point2D> res;
        while (!graph.empty())
        {
            current = graph.top(), graph.pop();
            int f = current.from, t = current.to;
            if (connect(f, t))
            {
                res.push_back({f, t});
            }
        }
        if (!res.size())
            cout << "No new highways need" << endl;
        else
            for (Point2D p : res)
                cout << p.x << " " << p.y << endl;
        if (t)
            cout << endl;
    }
    return 0;
}