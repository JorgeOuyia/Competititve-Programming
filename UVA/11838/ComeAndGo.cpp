#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

int intersections, streets, a, b, c, strongComponents, vertex;
vector<int> graph[2005];
vector<int> transposeGraph[2005];
bool visited[2005];
bool transposeVisited[2005];
stack<int> topologicalOrder;

void topoSort(int v)
{
	if (visited[v])
		return;
	visited[v] = true;
	for (int u : graph[v])
		topoSort(u);
	topologicalOrder.push(v);
}

void dfs(int v)
{
	if (transposeVisited[v])
		return;
	transposeVisited[v] = true;
	for (int u : transposeGraph[v])
		dfs(u);
}

int main()
{
	while (cin >> intersections >> streets && (intersections != 0 || streets != 0))
	{
		for (int i = 1; i <= intersections; i++)
			graph[i].clear(), transposeGraph[i].clear(), visited[i] = false, transposeVisited[i] = false;
		while (!topologicalOrder.empty())
			topologicalOrder.pop();
		strongComponents = 0;
		for (int i = 0; i < streets; i++)
		{
			cin >> a >> b >> c;
			graph[a].push_back(b);
			transposeGraph[b].push_back(a);
			if (c == 2)
				graph[b].push_back(a), transposeGraph[a].push_back(b);
		}
		// Kosaraju Algorithm
		for (int i = 1; i <= intersections; i++)
			if (!visited[i])
				topoSort(i);
		while (!topologicalOrder.empty())
		{
			vertex = topologicalOrder.top();
			topologicalOrder.pop();
			if (!transposeVisited[vertex])
			{
				strongComponents++;
				dfs(vertex);
			}
		}
		if (strongComponents > 1)
			cout << 0 << endl;
		else
			cout << 1 << endl;
	}
	return 0;
}