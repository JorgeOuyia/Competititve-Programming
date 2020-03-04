#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;

int people, calls, cont, scc, scenario;
vector<int> graph[30];
map<string, int> traducciones;
map<int, string> reverseTraducciones;
map<int, vector<string>> res;
vector<int> transposeGraph[30];
bool visited[30];
bool transposeVisited[30];
stack<int> topoOrder;
string f1, f2;

void topoSort(int v)
{
	if (visited[v])
		return;
	visited[v] = true;
	for (int u : graph[v])
		topoSort(u);
	topoOrder.push(v);
}

void dfs(int v)
{
	if (transposeVisited[v])
		return;
	transposeVisited[v] = true;
	res[scc].push_back(reverseTraducciones[v]);
	for (int u : transposeGraph[v])
		dfs(u);
}

void kosaraju()
{
	int vertex;
	while (!topoOrder.empty())
	{
		vertex = topoOrder.top();
		topoOrder.pop();
		if (!transposeVisited[vertex])
		{
			dfs(vertex);
			scc++;
		}
	}
}

int main()
{
	scenario = 1;
	while (cin >> people >> calls && (people != 0 || calls != 0))
	{
		cont = 1;
		traducciones.clear();
		reverseTraducciones.clear();
		res.clear();
		scc = 0;
		while (!topoOrder.empty())
			topoOrder.pop();
		for (int i = 1; i <= people; i++)
			transposeVisited[i] = false, transposeGraph[i].clear(), visited[i] = false, graph[i].clear();
		for (int i = 0; i < calls; i++)
		{
			cin >> f1 >> f2;
			if (traducciones[f1] == 0)
				traducciones[f1] = cont, reverseTraducciones[cont] = f1, cont++;
			if (traducciones[f2] == 0)
				traducciones[f2] = cont, reverseTraducciones[cont] = f2, cont++;
			graph[traducciones[f1]].push_back(traducciones[f2]);
			transposeGraph[traducciones[f2]].push_back(traducciones[f1]);
		}
		for (int i = 1; i <= people; i++)
		{
			if (!visited[i])
				topoSort(i);
		}
		kosaraju();
		cout << "Calling circles for data set " << scenario << ":" << endl;
		for (map<int, vector<string>>::iterator it = res.begin(); it != res.end(); ++it)
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				if (i == 0)
					cout << it->second[i];
				else
					cout << ", " << it->second[i];
			}
			cout << endl;
		}
		scenario++;
	}
	return 0;
}