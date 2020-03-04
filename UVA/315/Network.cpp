#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <sstream>

using namespace std;

int places, node, c;
vector<int> graph[105];
bool visited[105];
int tin[105], low[105];
int id;
set<int> artPoints;
string line;

void articulationPoints(int v, int p = -1)
{
	visited[v] = true;
	tin[v] = low[v] = id++;
	int children = 0;
	for (int D : graph[v])
	{
		if (D == v)
			continue;
		if (visited[D])
			low[v] = min(low[v], tin[D]);
		else
		{
			articulationPoints(D, v);
			low[v] = min(low[v], low[D]);
			if (low[D] >= tin[v] && p != -1)
				artPoints.insert(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
		artPoints.insert(v);
}

void findCutVertices()
{
	artPoints.clear();
	id = 1;
	for (int i = 1; i <= places; i++)
		visited[i] = false, low[i] = -1, tin[i] = -1;
	for (int i = 1; i <= places; i++)
		if (!visited[i])
			articulationPoints(i);
}

int main()
{
	while (cin >> places && places != 0)
	{
		for (int i = 1; i <= places; i++)
			graph[i].clear();
		cin.ignore();
		while (getline(cin, line) && line != "0")
		{
			istringstream ss(line);
			ss >> node;
			int n;
			while (ss >> n)
				graph[node].push_back(n), graph[n].push_back(node);

		}
		findCutVertices();
		cout << artPoints.size() << endl;
	}
	return 0;
}