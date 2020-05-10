#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point
{
    double x, y;

    bool operator==(const Point &other) const
    {
        return other.x == x && other.y == y;
    }
};

struct Point_Hash
{
    size_t operator()(const Point &point) const
    {
        return hash<double>()(point.x) ^ hash<double>()(point.y);
    }
};

struct Edge
{
    int from, to;
    double dist;

    bool operator<(const Edge &other) const
    {
        return other.dist < dist;
    }
};

int buildings, connections, from, to;
int parents[10005];
int sz[10005];
double x, y, mstSum;
vector<Point> allPoints;
unordered_map<int, Point> hashMap;
unordered_map<Point, int, Point_Hash> reverseHashMap;
priority_queue<Edge> graph;

double calculateDistance(Point a, Point b)
{
    double x = (b.x - a.x) * (b.x - a.x);
    double y = (b.y - a.y) * (b.y - a.y);

    return sqrt(x + y);
}

int find(int x)
{
    if (parents[x] == x)
        return x;
    return parents[x] = find(parents[x]);
}

void connect(int x, int y, double length, bool sum)
{
    x = find(x);
    y = find(y);

    if (x != y)
    {
        if (sz[x] >= sz[y])
            parents[y] = x, sz[x] += sz[y];
        else
            parents[x] = y, sz[y] += sz[x];
        if (sum)
            mstSum += length;
    }
}

int main()
{
    while (cin >> buildings)
    {
        hashMap.clear();
        reverseHashMap.clear();
        allPoints.clear();
        mstSum = 0;
        for (int i = 1; i <= buildings; i++)
            parents[i] = i, sz[i] = 1;
        for (int i = 1; i <= buildings; i++)
        {
            cin >> x >> y;
            hashMap[i] = {x, y};
            reverseHashMap[{x, y}] = i;
            allPoints.push_back({x, y});
        }
        for (int i = 0; i < allPoints.size(); i++)
        {
            Point from = allPoints[i];
            for (int j = i + 1; j < allPoints.size(); j++)
            {
                Point to = allPoints[j];
                double dist = calculateDistance(from, to);
                graph.push({reverseHashMap[from], reverseHashMap[to], dist});
                graph.push({reverseHashMap[to], reverseHashMap[from], dist});
            }
        }
        cin >> connections;
        while (connections--)
        {
            cin >> from >> to;
            Point f = hashMap[from];
            Point t = hashMap[to];
            int d = calculateDistance(f, t);
            connect(from, to, d, false);
        }
        while (!graph.empty())
        {
            int f = graph.top().from;
            int t = graph.top().to;
            double d = graph.top().dist;
            graph.pop();
            connect(f, t, d, true);
        }
        cout << fixed << setprecision(2) << mstSum << endl;
    }
    return 0;
}