#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
	int node, dist;

	Edge(int no, int di)
	{
		node = no;
		dist = di;
	}
};

int n, m, a, b, dist, maxDist, node1;
char trash;
vector<Edge> graph[40005];
bool visited[40005];

void dfs(int v, int dist)
{
	visited[v] = true;
	if (dist > maxDist)
		maxDist = dist, node1 = v;
	for (int u = 0; u < graph[v].size(); u++)
	{
		if (!visited[graph[v][u].node])
		{
			dfs(graph[v][u].node, dist + graph[v][u].dist);
		}
	}
	visited[v] = false;
}

int main()
{
	cin >> n >> m;
	maxDist = -1;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> dist >> trash;
		graph[a].push_back(Edge(b, dist));
		graph[b].push_back(Edge(a, dist));
	}
	dfs(1, 0);
	dfs(node1, 0);
	cout << maxDist << endl;
	return 0;
}