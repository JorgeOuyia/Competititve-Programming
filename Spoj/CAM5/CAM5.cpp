#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
 
using namespace std;
 
int t, v, e, a, b, res;
 
vector<int> graph[100004];
bool visited[100004];
 
void dfs(int u)
{
	stack<int> s;
	visited[u] = true;
	s.push(u);
	int vert;
	while (!s.empty())
	{
		vert = s.top();
		s.pop();
		for (int v : graph[vert])
		{
			if (!visited[v])
			{
				visited[v] = true;
				s.push(v);
			}
		}
	}
}
 
int main()
{
	cin >> t;
	while (t--)
	{
		res = 0;
		cin >> v >> e;
		for (int i = 0; i < v; i++)
			graph[i].clear(), visited[i] = false;
		for (int i = 0; i < e; i++)
		{
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		if (e == 0)
		{
			cout << v << endl;
			continue;
		}
		for (int i = 0; i < v; i++)
		{
			if (!visited[i])
			{
				dfs(i);
				res++;
			}
		}
		cout << res << endl;
	}
	return 0;
} 