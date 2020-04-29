#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

char character;
string line;
vector<int> graph[30];
bool visited[30];

int bfs(int start)
{
    visited[start] = true;
    queue<int> q;
    q.push(start);
    int current;
    while (!q.empty())
    {
        current = q.front(), q.pop();
        for (int v : graph[current])
            if (!visited[v])
                visited[v] = true, q.push(v);
    }
    return 1;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> character;
        int nodes = character - 'A' + 1;
        for (int i = 0; i < nodes; i++)
            graph[i].clear(), visited[i] = false;
        cin.ignore();
        while (getline(cin, line) && line != "")
        {
            graph[line[0] - 'A'].push_back(line[1] - 'A');
            graph[line[1] - 'A'].push_back(line[0] - 'A');
        }
        int res = 0;
        for (int i = 0; i < nodes; i++)
            if (!visited[i])
                res += bfs(i);
        cout << res << endl;
        if (t)
            cout << endl;
    }
    return 0;
}