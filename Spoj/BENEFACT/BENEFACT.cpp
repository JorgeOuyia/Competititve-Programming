#include <iostream>
#include <string>
#include <vector>
#include <queue>
 
using namespace std;
 
struct Edge
{
	int node, dist;
};
 
vector<Edge> places[50005];
bool visited[50005];
int n, a, b, c, maxValue;
Edge selected;
 
void dfs(int start, int dist)
{
	if (dist > selected.dist)
		selected.node = start, selected.dist = dist;
	visited[start] = true;
	for (Edge e : places[start])
	{
		if (!visited[e.node])
		{
			dfs(e.node, dist + e.dist);
		}
	}
	visited[start] = false;
}
 
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n;
		selected.dist = 0;
		for (int i = 1; i <= n; i++)
		{
			places[i].clear();
			visited[i] = false;
		}
		for (int i = 1; i <= n - 1; i++)
		{
			cin >> a >> b >> c;
			places[a].push_back({ b, c });
			places[b].push_back({ a, c });
		}		
		dfs(1, 0);
		selected.dist = 0;
		dfs(selected.node, 0);
		cout << selected.dist << endl;
	}
	return 0;
}