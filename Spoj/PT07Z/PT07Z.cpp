#include <iostream>
#include <string>
#include <vector>
 
using namespace std;
 
struct Edge
{
	int node, dist;
};
 
int n, a, b;
vector<Edge> graph[10005];
bool visited[10005];
Edge selected;
 
void dfs(int start, int dist)
{
	if (dist > selected.dist)
		selected.dist = dist, selected.node = start;
	visited[start] = true;
	for (Edge i : graph[start])
	{
		if (!visited[i.node])
			dfs(i.node, dist + i.dist);
	}
	visited[start] = false;
}
 
int main()
{
	while (cin >> n)
	{
		for (int i = 1; i <= n; i++)
			graph[i].clear(), visited[i] = false;
		selected.dist = 0;
		for (int i = 0; i < n - 1; i++)
		{
			cin >> a >> b;
			graph[a].push_back({ b, 1 });
			graph[b].push_back({ a, 1 });
		}
		dfs(1, 0);
		selected.dist = 0;
		dfs(selected.node, 0);
		cout << selected.dist << endl;
	}
	return 0;
} 