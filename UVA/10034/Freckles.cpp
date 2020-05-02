#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <iomanip>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Point2D
{
    double x, y;

    bool operator==(const Point2D &other) const
    {
        return other.x == x && other.y == y;
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

struct Point2D_Hash
{
    size_t operator()(const Point2D &point) const
    {
        size_t h1 = hash<double>()(point.x);
        size_t h2 = hash<double>()(point.y);

        return h1 ^ h2;
    }
};

int points;
double x, y, mstSum;
unordered_map<Point2D, int, Point2D_Hash> hashMap;
priority_queue<Edge> graph;
vector<Point2D> allPoints;
int parents[105];
int sz[105];

double calculateDistance(Point2D a, Point2D b)
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

void connect(int x, int y, double cost)
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
    int t;
    cin >> t;
    while (t--)
    {
        cin >> points;
        hashMap.clear();
        mstSum = 0.0;
        allPoints.clear();
        for (int i = 0; i <= points; i++)
            parents[i] = i, sz[i] = 1;
        int id = 1;
        for (int i = 0; i < points; i++)
        {
            cin >> x >> y;
            hashMap[{x, y}] = id++;
            allPoints.push_back({x, y});
        }
        for (int i = 0; i < allPoints.size(); i++)
        {
            int from = hashMap[allPoints[i]];
            for (int j = i + 1; j < allPoints.size(); j++)
            {
                int to = hashMap[allPoints[j]];
                double dist = calculateDistance(allPoints[i], allPoints[j]);
                graph.push({from, to, dist});
                graph.push({to, from, dist});
            }
        }
        Edge current;
        while (!graph.empty())
        {
            current = graph.top(), graph.pop();
            int from = current.from, to = current.to;
            double cost = current.dist;
            connect(from, to, cost);
        }
        cout << fixed << setprecision(2) << mstSum << endl;
        if (t != 0)
            cout << endl;
    }
    return 0;
}