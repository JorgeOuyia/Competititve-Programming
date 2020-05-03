#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
    int node, dist;
};

int warehouses, legs, querys, sz;
unordered_map<string, int> hashMap;
string warehouse, from, to;
vector<int> graph[35];
int distances[35];

int bfs(int source, int destiny)
{
    for (int i = 1; i <= warehouses; i++)
        distances[i] = INF;
    distances[source] = 0;
    queue<Edge> q;
    q.push({source, 0});
    Edge current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current.node == destiny)
            return distances[current.node];

        for (int v : graph[current.node])
        {
            if (distances[v] > distances[current.node] + 1)
            {
                distances[v] = distances[current.node] + 1;
                q.push({v, distances[v]});
            }
        }
    }
    return -1;
}

int main()
{
    int scenario = 1;
    int t;
    cin >> t;
    cout << "SHIPPING ROUTES OUTPUT" << endl;
    cout << endl;
    while (t--)
    {
        cin >> warehouses >> legs >> querys;
        hashMap.clear();
        for (int i = 0; i < warehouses; i++)
        {
            cin >> warehouse;
            hashMap[warehouse] = i + 1;
            graph[i + 1].clear();
        }
        for (int i = 0; i < legs; i++)
        {
            cin >> from >> to;
            graph[hashMap[from]].push_back(hashMap[to]);
            graph[hashMap[to]].push_back(hashMap[from]);
        }
        cout << "DATA SET  " << scenario++ << endl;
        cout << endl;
        for (int i = 0; i < querys; i++)
        {
            cin >> sz >> from >> to;
            int cost = bfs(hashMap[from], hashMap[to]) * sz * 100;
            if (cost < 0)
                cout << "NO SHIPMENT POSSIBLE" << endl;
            else
                cout << "$" << cost << endl;
        }
        cout << endl;
        if (!t)
            cout << "END OF OUTPUT" << endl;
    }
    return 0;
}