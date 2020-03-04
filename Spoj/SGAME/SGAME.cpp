#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int t, node, a, b, flag;
 
vector<int> graph[305];
bool visited[305];
 
void dfs(int v)
{
	visited[v] = true;
	if (graph[v].size() == 0 || graph[v].size() % 2 != 0)
		flag = 0;
	for (int u : graph[v])
	{
		if (!visited[u])
			dfs(u);
	}
}
 
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> node;
		for (int i = 0; i < 302; i++)
			graph[i].clear(), visited[i] = false;
		flag = 1;
		while (cin >> a >> b && (a != -1 || b != -1))
		{
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		dfs(node);
		if (flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}