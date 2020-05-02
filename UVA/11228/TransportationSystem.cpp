#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
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

struct Point2D_Hash
{
    size_t operator()(const Point2D &point) const
    {
        size_t h1 = hash<int>()(point.x);
        size_t h2 = hash<int>()(point.y);

        return h1 ^ h2;
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

int cities, threshold, x, y, differentStates;
double mstSumSameState, mstSumDifferentState;
unordered_map<Point2D, int, Point2D_Hash> hashMap;
vector<Point2D> allPoints;
priority_queue<Edge> graph;
priority_queue<Edge> otherGraph;
int parents[1005];
int sz[1005];

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

void connectSameState(int x, int y, double cost)
{
    x = find(x);
    y = find(y);

    if (x != y && cost <= threshold)
    {
        if (sz[x] >= sz[y])
            parents[y] = x, sz[x] += sz[y];
        else
            parents[x] = y, sz[y] += sz[x];
        mstSumSameState += cost;
    }
}

void connectDifferentState(int x, int y, double cost)
{
    x = find(x);
    y = find(y);

    if (x != y && cost > threshold)
    {
        if (sz[x] >= sz[y])
            parents[y] = x, sz[x] += sz[y];
        else
            parents[x] = y, sz[y] += sz[x];
        mstSumDifferentState += cost;
    }
}

int main()
{
    int scenario = 1;
    int t;
    cin >> t;
    while (t--)
    {
        cin >> cities >> threshold;
        hashMap.clear();
        allPoints.clear();
        mstSumDifferentState = 0;
        mstSumSameState = 0;
        differentStates = 0;
        for (int i = 0; i <= cities; i++)
            parents[i] = i, sz[i] = 1;
        int id = 1;
        for (int i = 0; i < cities; i++)
        {
            cin >> x >> y;
            allPoints.push_back({x, y});
            hashMap[{x, y}] = id++;
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
            otherGraph.push(current);
            int from = current.from;
            int to = current.to;
            double cost = current.dist;
            connectSameState(from, to, cost);
        }
        unordered_set<int> differentParents;
        for (int i = 1; i <= cities; i++)
            differentParents.insert(find(i));
        differentStates = differentParents.size();
        while (!otherGraph.empty())
        {
            current = otherGraph.top(), otherGraph.pop();
            int from = current.from;
            int to = current.to;
            double cost = current.dist;
            connectDifferentState(from, to, cost);
        }
        cout << "Case #" << scenario++ << ": " << differentStates << " " << (int)round(mstSumSameState) << " " << (int)round(mstSumDifferentState) << endl;
    }
    return 0;
}