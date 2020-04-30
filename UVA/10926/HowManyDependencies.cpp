#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Pair
{
    int id, freq;

    bool operator<(const Pair& other) const
    {
        if (freq == other.freq)
            return id < other.id;
        return freq > other.freq;
    }
};

int tasks, n, task, freq, selected, maxFreq;
vector<int> graph[105];
bool visited[105];

void dfs(int u)
{
    visited[u] = true;

    freq++;

    for (int v : graph[u])
    {
        if (!visited[v])
            dfs(v);
    }
}

int main()
{
    while (cin >> tasks && tasks != 0)
    {
        for (int i = 0; i <= tasks; i++)
            graph[i].clear(), visited[i] = false;
        maxFreq = -1;
        selected = 1;
        for (int i = 0; i < tasks; i++)
        {
            cin >> n;
            while (n--)
            {
                cin >> task;
                graph[i + 1].push_back(task);
            }
        }
        for (int i = 1; i <= tasks; i++)
        {
            for (int j = 1; j <= tasks; j++)
                visited[j] = false;
            freq = -1;
            dfs(i);
            if (freq > maxFreq)
                maxFreq = freq, selected = i;
        }
        cout << selected << endl;
    }
    return 0;
}