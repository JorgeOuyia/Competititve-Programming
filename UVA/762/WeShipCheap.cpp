#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

#define INF 0x3f3f3f3f

using namespace std;

int links;
string from, to, source, destiny;
vector<int> graph[20000];
int distances[20000];
int parents[20000];
unordered_map<string, int> hashMap;
unordered_map<int, string> reverseHashMap;

int bfs(int source, int destiny)
{
    distances[source] = 0;
    queue<int> q;
    q.push(source);
    int current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current == destiny)
            return distances[current];

        for (int v : graph[current])
        {
            if (distances[v] > distances[current] + 1)
                distances[v] = distances[current] + 1, parents[v] = current, q.push(v);
        }
    }
    return -1;
}

int main()
{
    int first = true;
    while (cin >> links)
    {
        if (first)
            first = false;
        else
            cout << endl;
        for (int i = 1; i <= links + 1; i++)
            distances[i] = INF, parents[i] = i, graph[i].clear();
        hashMap.clear();
        reverseHashMap.clear();
        int id = 1;
        for (int i = 0; i < links; i++)
        {
            cin >> from >> to;
            if (hashMap.find(from) == hashMap.end())
                hashMap[from] = id, reverseHashMap[id++] = from;
            if (hashMap.find(to) == hashMap.end())
                hashMap[to] = id, reverseHashMap[id++] = to;
            graph[hashMap[from]].push_back(hashMap[to]);
            graph[hashMap[to]].push_back(hashMap[from]);
        }
        cin >> source >> destiny;
        if (hashMap.find(source) == hashMap.end() || hashMap.find(destiny) == hashMap.end())
            cout << "No route" << endl;
        else
        {
            int dist = bfs(hashMap[source], hashMap[destiny]);
            if (dist == -1)
                cout << "No route" << endl;
            else
            {
                vector<string> res;
                int u = hashMap[destiny];
                while (u != parents[u])
                {
                    res.push_back(reverseHashMap[u]);
                    u = parents[u];
                }
                res.push_back(source);
                reverse(res.begin(), res.end());
                for (int i = 1; i < res.size(); i++)
                {
                    cout << res[i - 1] << " " << res[i] << endl;
                }
            }
        }
    }
    return 0;
}