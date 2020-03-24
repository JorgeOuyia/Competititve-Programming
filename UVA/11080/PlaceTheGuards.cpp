#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int t, junctions, streets, a, b, flag, numUnos, numCeros;
vector<int> graph[305];
int bipartite[305];

void bfs(int u)
{
    queue<int> q;
    q.push(u);
    int current;
    bipartite[u] = 1;
    numCeros = 0;
    numUnos = 1;
    while (!q.empty())
    {
        current = q.front();
        q.pop();

        for (int v : graph[current])
        {
            if (bipartite[v] == -1)
            {
                if (bipartite[current] == 1)
                    numCeros++;
                else
                    numUnos++;
                q.push(v);
                bipartite[v] = 1 - bipartite[current];
            }
            else if (bipartite[v] == bipartite[current])
            {
                flag = 0;
            }
        }
    }
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> junctions >> streets;
        numUnos = 0;
        numCeros = 0;
        flag = 1;
        for (int i = 0; i < junctions; i++)
        {
            graph[i].clear();
            bipartite[i] = -1;
        }
        for (int i = 0; i < streets; i++)
        {
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        int res = 0;
        for (int i = 0; i < junctions && flag; i++)
        {
            if (bipartite[i] == -1)
            {
                bfs(i);
                if (numCeros == 0)
                    res += 1;
                else
                    res += min(numUnos, numCeros);
            }
        }
        if (!flag)
            cout << -1 << endl;
        else
            cout << res << endl;
    }
    return 0;
}