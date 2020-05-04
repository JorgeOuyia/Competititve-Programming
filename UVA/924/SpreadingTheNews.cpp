#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Boom
{
    int maxDailyBoomSize, firstBoomDay;
};

int employees, edges, id, querys, source;
vector<int> graph[2505];
bool visited[2505];

Boom bfs(int start)
{
    for (int i = 0; i < employees; i++)
        visited[i] = false;
    int day = 1, selectedDay = -1;
    int sz = 0, maxSz = -1;
    visited[start] = true;
    queue<int> q;
    q.push(start);
    int current;
    while (!q.empty())
    {
        int cont = q.size();
        sz = 0;
        while (cont--)
        {
            current = q.front(), q.pop();

            for (int v : graph[current])
            {
                if (!visited[v])
                    q.push(v), visited[v] = true, sz++;
            }
        }
        if (sz > maxSz)
            maxSz = sz, selectedDay = day;
        day++;
    }
    return {maxSz, selectedDay};
}

int main()
{
    while (cin >> employees)
    {
        for (int i = 0; i < employees; i++)
            graph[i].clear();
        for (int i = 0; i < employees; i++)
        {
            cin >> edges;
            while (edges--)
            {
                cin >> id;
                graph[i].push_back(id);
            }
        }
        cin >> querys;
        while (querys--)
        {
            cin >> source;
            if (!graph[source].size())
                cout << 0 << endl;
            else
            {
                Boom result = bfs(source);
                cout << result.maxDailyBoomSize << " " << result.firstBoomDay << endl;
            }
        }
    }
    return 0;
}