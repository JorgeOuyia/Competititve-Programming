#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>

using namespace std;

int serversNumber, server, numConections, conect;
char trash;
vector<int> graph[105];
bool visited[105];
int tin[105], low[105];
set<pair<int, int>> bridges;
int id;

void dfs(int v, int p = -1)
{
	visited[v] = true;
	tin[v] = low[v] = id++;
	for (int to : graph[v])
	{
		if (to == p)
			continue;
		if (visited[to])
			low[v] = min(low[v], tin[to]);
		else
		{
			dfs(to, v);
			low[v] = min(low[v], low[to]);
			if (low[to] > tin[v])
			{
				if (v < to)
					bridges.insert({ v, to });
				else
					bridges.insert({ to, v });
			}
		}
	}
}

void findBridges()
{
	id = 0;
	bridges.clear();
	for (int i = 0; i < serversNumber; i++)
		visited[i] = false, tin[i] = -1, low[i] = -1;
	for (int i = 0; i < serversNumber; i++)
		if (!visited[i])
			dfs(i);
}

int main()
{
	while (cin >> serversNumber)
	{
		for (int i = 0; i < serversNumber; i++)
		{
			graph[i].clear();
		}
		for (int i = 0; i < serversNumber; i++)
		{
			cin >> server >> trash >> numConections >> trash;
			for (int j = 0; j < numConections; j++)
			{
				cin >> conect;
				graph[server].push_back(conect);
			}
		}
		findBridges();
		cout << bridges.size() << " critical links" << endl;
		for (set<pair<int, int>>::iterator it = bridges.begin(); it != bridges.end(); ++it)
		{
			cout << (*it).first << " - " << (*it).second << endl;
		}
		cout << endl;
	}
	return 0;
}