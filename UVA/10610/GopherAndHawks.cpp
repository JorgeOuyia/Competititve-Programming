#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <unordered_map>

#define INF 0x3f3f3f3f

using namespace std;

struct Coord
{
    double x, y;

    bool operator==(const Coord &other) const
    {
        return other.x == x && other.y == y;
    }
};

struct Coord_Hash
{
    size_t operator()(const Coord &coord) const
    {
        size_t h1 = hash<double>()(coord.x);
        size_t h2 = hash<double>()(coord.y);

        return h1 ^ h2;
    }
};

int id;
double speed, maxTime, x, y;
Coord source, destiny;
string line;
vector<Coord> allPoints;
unordered_map<Coord, int, Coord_Hash> hashMap;
vector<int> graph[1005];
int distances[1005];

double calculateDistance(Coord a, Coord b)
{
    double x = (b.x - a.x) * (b.x - a.x);
    double y = (b.y - a.y) * (b.y - a.y);

    return sqrt(x + y);
}

double calculateTime(Coord a, Coord b)
{
    return calculateDistance(a, b) / speed;
}

int bfs(int start, int target)
{
    for (int i = 0; i <= id; i++)
        distances[i] = INF;
    distances[start] = 0;
    queue<int> q;
    q.push(start);
    int current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current == target)
            return distances[current];

        for (int v : graph[current])
        {
            if (distances[v] > distances[current] + 1)
                distances[v] = distances[current] + 1, q.push(v);
        }
    }
    return -1;
}

int main()
{
    while (cin >> speed >> maxTime && (speed || maxTime))
    {
        allPoints.clear();
        hashMap.clear();
        id = 1;
        cin >> source.x >> source.y;
        allPoints.push_back(source);
        hashMap[source] = id++;
        cin >> destiny.x >> destiny.y;
        allPoints.push_back(destiny);
        hashMap[destiny] = id++;
        cin.ignore();
        while (getline(cin, line) && line != "")
        {
            istringstream ss(line);
            ss >> x >> y;
            hashMap[{x, y}] = id++;
            allPoints.push_back({x, y});
        }
        for (int i = 0; i <= id; i++)
            graph[i].clear();
        for (int i = 0; i < allPoints.size(); i++)
        {
            Coord from = allPoints[i];
            for (int j = i + 1; j < allPoints.size(); j++)
            {
                Coord to = allPoints[j];
                if (calculateTime(from, to) <= maxTime * 60)
                    graph[hashMap[from]].push_back(hashMap[to]), graph[hashMap[to]].push_back(hashMap[from]);
            }
        }
        int res = bfs(hashMap[source], hashMap[destiny]);
        if (res != -1)
            cout << "Yes, visiting " << res - 1 << " other holes." << endl;
        else
            cout << "No." << endl;
    }
    return 0;
}