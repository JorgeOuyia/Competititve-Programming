#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <map>

using namespace std;

int n, until;
vector<int> graph[30];
vector<int> rGraph[30];
int inDegree[30];
bool visited[30];
bool letters[30];
string line;
stack<int> topoOrder;
map<char, set<int>> res;
set<int> path;

void dfs(int u)
{
	visited[u] = true;
    path.insert(u);

	for (int v : rGraph[u])
		if (!visited[v])
			dfs(v);
}

void topoSort(int u)
{
	visited[u] = true;

	for (int v : graph[u])
		if (!visited[v])
			topoSort(v);
	topoOrder.push(u);
}

int main()
{
    cin >> n;
	while (n != 0)
	{
		until = -1;
		cin.ignore();
        res.clear();
        path.clear();
		for (int i = 0; i < 30; i++)
			visited[i] = false, graph[i].clear(), rGraph[i].clear(), inDegree[i] = 0, letters[i] = false;
		for (int i = 0; i < n; i++)
		{
			getline(cin, line);
			until = max(until, line[line.length() - 1] - 'A');
			int source = line[line.length() - 1] - 'A';
            letters[source] = true;
			for (int i = 0; i < line.length() - 1; i++)
			{
				if (line[i] != ' ')
				{
					graph[source].push_back(line[i] - 'A');
					rGraph[line[i] - 'A'].push_back(source);
					until = max(until, line[i] - 'A');
                    letters[line[i] - 'A'] = true;
				}
			}
		}
		for (int i = 0; i <= until; i++)
			if (!visited[i] && letters[i])
				topoSort(i);
		for (int i = 0; i < 30; i++)
			visited[i] = false;
		int cont = 1;
		while (!topoOrder.empty())
		{
			int i = topoOrder.top();
			topoOrder.pop();
            path.clear();
			if (!visited[i])
				dfs(i), res[*path.begin()] = path;
		}
		for (auto it = res.begin(); it != res.end(); ++it)
        {
            int first = true;
            for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
            {
                if (first)
                {
                    first = false;
                    cout << (char)(*jt + 'A');
                }
                else
                    cout << " " << (char)(*jt + 'A');
            }
            cout << endl;
        }
        cin >> n;
        if (n != 0)
            cout << endl;
	}
	return 0;
}