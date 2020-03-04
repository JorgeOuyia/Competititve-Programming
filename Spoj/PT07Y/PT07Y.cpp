#include <iostream>
#include <string>
#include <vector>
 
using namespace std;
 
int nodes, edges, a, b, flag;
vector<int> graph[10005];
bool visited[10005];
 
void dfs(int start)
{
	visited[start] = true;
	int c = 0;
	for (int i : graph[start])
	{
		if (visited[i])
			c++;
	}
	if (c > 1)
		flag = 0;
	for (int i : graph[start])
	{
		if (!visited[i])
		{
			dfs(i);
		}
	}
}
 
int main()
{
	while (cin >> nodes >> edges)
	{
		flag = 1;
		for (int i = 1; i <= nodes; i++)
		{
			graph[i].clear();
			visited[i] = false;
		}
		for (int i = 0; i < edges; i++)
		{
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		if (nodes == edges + 1)
		{
			dfs(1);
			for (int i = 1; i <= nodes; i++)
			{
				if (!visited[i])
					flag = false;
			}
			if (flag)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
		else cout << "NO" << endl;
	}
	return 0;
}