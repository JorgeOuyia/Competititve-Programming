#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sticks, edges, from, to;
queue<int> topoOrder;
int inDegree[1000005];
vector<int> graph[1000005];

bool kahnTopoSort()
{
    bool posible = false;
    queue<int> q;
    for (int i = 1; i <= sticks; i++)
        if (!inDegree[i])
            q.push(i), posible = true;
    if (!posible)
        return false;
    int current;
    while (!q.empty())
    {
        current = q.front(), q.pop();
        topoOrder.push(current);

        for (int v : graph[current])
        {
            inDegree[v]--;

            if (!inDegree[v])
                q.push(v);
        }
    }
    return true;
}

int main()
{
    while (cin >> sticks >> edges && (sticks != 0 || edges != 0))
    {
        for (int i = 1; i <= sticks; i++)
            graph[i].clear(), inDegree[i] = 0;
        for (int i = 0; i < edges; i++)
        {
            cin >> from >> to;
            graph[from].push_back(to);
            inDegree[to]++;
        }
        if (!kahnTopoSort())
            cout << "IMPOSSIBLE" << endl;
        else
        {
            while (!topoOrder.empty())
            {
                cout << topoOrder.front() << endl;
                topoOrder.pop();
            }
        }
    }
    return 0;
}