#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>

using namespace std;

int people, trust, aux, cont;
unordered_map<string, int> trad;
vector<int> graph[1005];
vector<int> rGraph[1005];
bool visited[1005];
string line, from, to;
stack<int> topoOrder;

void topoSort(int u)
{
    visited[u] = true;

    for (int v : graph[u])
        if (!visited[v])
            topoSort(v);
    topoOrder.push(u);
}

void dfs(int u)
{
    visited[u] = true;

    for (int v : rGraph[u])
        if (!visited[v])
            dfs(v);
}

int main()
{
    while (cin >> people >> trust && (people != 0 || trust != 0))
    {
        cin.ignore();
        aux = 1;
        trad.clear();
        cont = 0;
        for (int i = 1; i <= people; i++)
            visited[i] = false, graph[i].clear(), rGraph[i].clear();
        for (int i = 0; i < people; i++)
        {
            getline(cin, line);
            trad[line] = aux++;
        }
        for (int i = 0; i < trust; i++)
        {
            getline(cin, from);
            getline(cin, to);
            graph[trad[from]].push_back(trad[to]);
            rGraph[trad[to]].push_back(trad[from]);
        }
        for (int i = 1; i <= people; i++)
            if (!visited[i])
                topoSort(i);
        for (int i = 1; i <= people; i++)
            visited[i] = false;
        int current;
        while (!topoOrder.empty())
        {
            current = topoOrder.top();
            topoOrder.pop();
            if (!visited[current])
                dfs(current), cont++;
        }
        cout << cont << endl;
    }
    return 0;
}