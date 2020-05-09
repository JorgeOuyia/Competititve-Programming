#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
    int node, dist;
};

vector<Edge> graph[10005];
int distances[10005];
unordered_map<int, int> freq;
int stations, lines, from, to, minTime, mostImportant;

int bfs(int start)
{
    for (int i = 1; i <= stations; i++)
        distances[i] = INF;
    distances[start] = 0;
    queue<Edge> q;
    q.push({start, 0});
    Edge current;
    int dist = 0;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (Edge v : graph[current.node])
        {
            if (distances[v.node] == INF)
            {
                distances[v.node] = current.dist + 1;
                q.push({v.node, current.dist + 1});
            }
        }
    }
    for (int i = 1; i <= stations; i++)
    {
        if (freq[i] >= 2)
            dist += distances[i];
    }
    return dist;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> stations >> lines;
        minTime = INF;
        freq.clear();
        for (int i = 1; i <= stations; i++)
        {
            graph[i].clear();
            distances[i] = INF;
        }
        for (int i = 0; i < lines; i++)
        {
            cin >> from;
            freq[from]++;
            while (cin >> to && to != 0)
            {
                graph[from].push_back({to, 1});
                graph[to].push_back({from, 1});
                freq[to]++;
                from = to;
            }
        }
        for (int i = 1; i <= stations; i++)
        {
            if (freq[i] >= 2)
            {
                if (bfs(i) < minTime)
                    minTime = bfs(i), mostImportant = i;
            }
        }
        cout << "Krochanska is in: " << mostImportant << endl;
    }
    return 0;
}