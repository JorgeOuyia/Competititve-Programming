#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int persons, dancing, a, b;
vector<int> graph[1005];
int distances[1005];

void bfs(int start)
{
    distances[start] = 0;
    queue<int> q;
    q.push(start);
    int current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (int v : graph[current])
        {
            if (distances[v] > distances[current] + 1)
                distances[v] = distances[current] + 1, q.push(v);
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> persons >> dancing;
        for (int i = 0; i < persons; i++)
            graph[i].clear(), distances[i] = INF;
        while (dancing--)
        {
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        bfs(0);
        for (int i = 1; i < persons; i++)
            cout << distances[i] << endl;
        if (t)
            cout << endl;
    }
    return 0;
}