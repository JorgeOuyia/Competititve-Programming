#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>

using namespace std;

int events, n, destiny;
vector<int> graph[15005];
int inDegree[15005];
int death[15005];
int dp[15005];
stack<int> topoOrder;

void topoSort()
{
    queue<int> q;
    for (int i = 0; i < events; i++)
        if (!inDegree[i])
            q.push(i);
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
}

int countAllPaths(int start)
{
    for (int i = 0; i < events; i++)
    {
        if (death[i])
            dp[i] = 1;
    }

    int u;
    while (!topoOrder.empty())
    {
        u = topoOrder.top(), topoOrder.pop();

        for (int v : graph[u])
            dp[u] += dp[v];
    }
    return dp[start];
}

int main()
{
    cin >> events;
    while (true)
    {
        for (int i = 0; i < events; i++)
            graph[i].clear(), dp[i] = 0, inDegree[i] = 0, death[i] = 0;
        cin.ignore();
        for (int i = 0; i < events; i++)
        {
            cin >> n;
            if (n == 0)
                death[i] = 1;
            for (int j = 0; j < n; j++)
            {
                cin >> destiny;
                graph[i].push_back(destiny);
                inDegree[destiny]++;
            }
        }
        topoSort();
        cout << countAllPaths(0) << endl;
        cin >> events;
        if (cin)
            cout << endl;
        else
            break;
    }
    return 0;
}