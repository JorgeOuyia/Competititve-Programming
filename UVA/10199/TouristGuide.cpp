#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int locations, cont, routes, scenario;
map<string, int> traducciones;
map<int, string> reverseTraducciones;
string line, a, b;
vector<int> graph[105];
bool visited[105];
int tin[105], low[105];
int timer;
vector<int> res;

void articulationPoints(int v, int p = -1)
{
	visited[v] = true;
	tin[v] = low[v] = timer++;
	int children = 0;
	for (int to : graph[v])
	{
		if (to == p)
			continue;
		if (visited[to])
			low[v] = min(low[v], tin[to]);
		else
		{
			articulationPoints(to, v);
			low[v] = min(low[v], low[to]);
			if (low[to] >= tin[v] && p != -1)
			{
				if (find(res.begin(), res.end(), v) == res.end())
					res.push_back(v);
			}
			++children;
		}
	}
	if (p == -1 && children > 1)
		res.push_back(v);
}

void findCutPoints()
{
	timer = 0;
	for (int i = 0; i < cont; i++)
		visited[i] = false, tin[i] = -1, low[i] = -1;
	for (int i = 0; i < cont; i++)
	{
		if (!visited[i])
			articulationPoints(i);
	}
}

int main()
{
	scenario = 1;
	cin >> locations;
	while (locations != 0)
	{
		traducciones.clear();
		reverseTraducciones.clear();
		cont = 0;
		timer = 0;
		res.clear();
		for (int i = 0; i < locations; i++)
		{
			cin >> line;
			traducciones[line] = cont;
			reverseTraducciones[cont] = line;
			cont++;
		}
		for (int i = 0; i < cont; i++)
		{
			visited[i] = false;
			tin[i] = -1;
			low[i] = -1;
			graph[i].clear();
		}
		cin >> routes;
		for (int i = 0; i < routes; i++)
		{
			cin >> a >> b;
			graph[traducciones[a]].push_back(traducciones[b]);
			graph[traducciones[b]].push_back(traducciones[a]);
		}
		findCutPoints();
		vector<string> finalRes;
		for (int i = 0; i < res.size(); i++)
		{
			finalRes.push_back(reverseTraducciones[res[i]]);
		}
		sort(finalRes.begin(), finalRes.end());
		cout << "City map #" << scenario << ": " << finalRes.size() << " camera(s) found" << endl;
		for (int i = 0; i < finalRes.size(); i++)
		{
			cout << finalRes[i] << endl;
		}
		scenario++;
		cin >> locations;
		if (locations != 0)
			cout << endl;
	}
	return 0;
}