#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int n, m, a, b, id;
vector<int> graph[10005];
bool visited[10005];
int low[10005], tin[10005];
map<int, int> childrens;
map<int, vector<int>> res;

void articulationPoints(int v, int p = -1)
{
	visited[v] = true;
	tin[v] = low[v] = id++;
	int children = 0;
	for (int D : graph[v])
	{
		if (D == p)
			continue;
		if (visited[D])
			low[v] = min(low[v], tin[D]);
		else
		{
			articulationPoints(D, v);
			low[v] = min(low[v], low[D]);
			if (low[D] >= tin[v] && p != -1)
				children++;
		}
	}
	childrens[v] = max(childrens[v], children + 1);
	if (p == -1 && children > 1)
		childrens[v] = max(childrens[v], children);
}

int main()
{
	while (cin >> n >> m && (n != 0 || m != 0))
	{
		id = 0;
		childrens.clear();
		res.clear();
		for (int i = 0; i <= n; i++)
			graph[i].clear(), visited[i] = false, low[i] = -1, tin[i] = -1;
		while (cin >> a >> b && (a != -1 || b != -1))
		{
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		for (int i = 0; i < n; i++)
			if (!visited[i])
				articulationPoints(i);
		for (auto it = childrens.begin(); it != childrens.end(); ++it)
		{
			res[it->second].push_back(it->first);
		}
		int cont = 0;
		for (auto it = res.rbegin(); it != res.rend() && cont < m; ++it)
		{
			for (int num : res[it->first])
			{
				if (cont < m)
				{
					cout << num << " " << it->first << endl;
					cont++;
				}
			}
		}
		cout << endl;
	}
	return 0;
}