#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
	int from, to, energy;
};

int rooms, energy, doorways, to;
vector<Edge> graph;
vector<int> reachable[105];
int energies[105];
bool visited[105];

bool bfs(int start, int end)
{
	for (int i = 1; i <= rooms; i++)
		visited[i] = false;
	visited[start] = true;
	queue<int> q;
	q.push(start);
	int current;
	while (!q.empty())
	{
		current = q.front(), q.pop();

		for (int v : reachable[current])
		{
			if (!visited[v])
				visited[v] = true, q.push(v);
		}
	}
	return visited[end];
}

bool bellmanFord(int start, int end)
{
	energies[start] = 100;

	int relaxation = rooms - 1;
	while (relaxation--)
	{
		for (Edge v : graph)
		{
			// If I cannot reach the starting point
			if (energies[v.from] <= 0)
				continue;
			energies[v.to] = max(energies[v.to], energies[v.from] + v.energy);
		}
	}
	bool cycle = false;
	for (Edge v : graph)
	{
		// If I cannot reach the starting point
		if (energies[v.from] <= 0)
			continue;
		if (energies[v.to] < energies[v.from] + v.energy && bfs(v.from, rooms))
			cycle = true;
	}
	return cycle || energies[rooms] > 0;
}

int main()
{
	int test = 1;
	while (cin >> rooms && rooms != -1)
	{
		graph.clear();
		for (int i = 1; i <= rooms; i++)
			energies[i] = -INF, visited[i] = false, reachable[i].clear();
		for (int i = 1; i <= rooms; i++)
		{
			cin >> energy >> doorways;
			for (int j = 0; j < doorways; j++)
			{
				cin >> to;
				graph.push_back({ i, to, energy });
				reachable[i].push_back(to);
			}
		}
		if (!bfs(1, rooms))
			cout << "hopeless" << endl;
		else
		{
			if (bellmanFord(1, rooms))
				cout << "winnable" << endl;
			else
				cout << "hopeless" << endl;
		}
	}
	return 0;
}