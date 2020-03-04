#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

int t, tiles, conections, a, b;
vector<int> graph[100005];
bool visited[100005];
bool transposeVisited[100005];
stack<int> topoOrder;

void topoSort(int n)
{
	if (visited[n]) return;
	visited[n] = true;
	for (int u : graph[n])
		topoSort(u);
	topoOrder.push(n);
}

void dfs(int v)
{
	if (transposeVisited[v])
		return;
	transposeVisited[v] = true;
	for (int u : graph[v])
		dfs(u);
}

int kosaraju()
{
	int vertex;
	int cont = 0;
	while (!topoOrder.empty())
	{
		vertex = topoOrder.top();
		topoOrder.pop();
		if (!transposeVisited[vertex])
		{
			cont++;
			dfs(vertex);
		}
	}
	return cont;
}

int main()
{
	cin >> t;
	while (t--)
	{
		cin >> tiles >> conections;
		for (int i = 1; i <= tiles; i++)
		{
			graph[i].clear();
			visited[i] = false;
			transposeVisited[i] = false;
		}
		while (!topoOrder.empty())
			topoOrder.pop();
		for (int i = 0; i < conections; i++)
		{
			cin >> a >> b;
			graph[a].push_back(b);
		}
		for (int i = 1; i <= tiles; i++)
			if (!visited[i])
				topoSort(i);
		cout << kosaraju() << endl;
	}
	return 0;
}