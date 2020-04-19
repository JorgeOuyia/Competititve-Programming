#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

struct Edge
{
    int node, cost;

    bool operator<(const Edge& other) const
    {
        return other.cost < cost;
    }
};

int elevators, destiny;
int times[10], destinies[105];
int distances[105];
string line;
vector<Edge> graph[105];

int dijkstra()
{
    distances[0] = 0;
    priority_queue<Edge> pq;
    pq.push({ 0, 0 });
    Edge current;
    while (!pq.empty())
    {
        current = pq.top(), pq.pop();

        if (current.cost <= distances[current.node])
        {
            for (Edge to : graph[current.node])
            {
                if (distances[to.node] > distances[current.node] + to.cost + 60)
                {
                    distances[to.node] = distances[current.node] + to.cost + 60;
                    pq.push({ to.node, distances[to.node] });
                }
            }
        }
    }
    return distances[destiny];
}

int main()
{
    while (cin >> elevators >> destiny)
    {
        for (int i = 0; i < elevators; i++)
            cin >> times[i];
        memset(distances, 0x3f3f3f3f, sizeof(distances));
        for (int i = 0; i <= 100; i++)
            graph[i].clear();
        cin.ignore();
        for (int i = 0; i < elevators; i++)
        {
            getline(cin, line);
            istringstream ss(line);
            int index = 0;
            while (ss >> destinies[index])
                index++;
            for (int j = 0; j < index; j++)
            {
                for (int k = j + 1; k < index; k++)
                {
                    graph[destinies[j]].push_back({ destinies[k], (destinies[k] - destinies[j]) * times[i] });
                    graph[destinies[k]].push_back({ destinies[j], (destinies[k] - destinies[j]) * times[i] });
                }
            }
        }
        int res = dijkstra();
        if (res == 0x3f3f3f3f)
            cout << "IMPOSSIBLE" << endl;
        else
        {
            if (destiny != 0)
                res -= 60;
            cout << res << endl;
        }
    }
    return 0;
}