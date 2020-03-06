#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

struct Edge
{
	int from, to, dist;

	bool operator<(const Edge& other) const
	{
		return other.dist < dist;
	}
};

int junctions, streets, bar, charly, nito, from, to, dist, maxDist, distCharly, distNito;
vector<Edge> graph[5005];
vector<Edge> allConections;
vector<Edge> path[5005];
int distancesBar[5005];
int distancesCharly[5005];
int distancesNito[5005];
bool visited[5005];
vector<int> pathNito, pathCharly;

void dijkstra(int start, int end, int *distances)
{
	distances[start] = 0;
	priority_queue<Edge> pq;
	pq.push({ start, start, 0 });
	Edge current;
	while (!pq.empty())
	{
		current = pq.top(), pq.pop();
		if (distances[current.to] >= current.dist)
		{
			for (Edge D : graph[current.to])
			{
				int w = current.dist + D.dist;
				if (w < distances[D.to])
				{
					pq.push({ D.from, D.to, w });
					distances[D.to] = w;
				}
			}
		}
	}
}

void dfs(int v, int dist)
{
	visited[v] = true;
	if (dist > maxDist)
		maxDist = dist;
	for (Edge u : path[v])
	{
		if (!visited[u.to])
		{
			dfs(u.to, dist + u.dist);
		}
	}
}

int main()
{
	while (cin >> junctions >> bar >> charly >> nito >> streets &&
		(junctions != -1 || bar != -1 || charly != -1 || nito != -1 || streets != -1))
	{
		for (int i = 1; i <= junctions; i++)
			graph[i].clear(), path[i].clear(), distancesCharly[i] = 0x3f3f3f3f, distancesNito[i] = 0x3f3f3f3f, distancesBar[i] = 0x3f3f3f3f, visited[i] = false;
		allConections.clear();
		maxDist = -1;
		distCharly = 0;
		distNito = 0;
		for (int i = 0; i < streets; i++)
		{
			cin >> from >> to >> dist;
			graph[from].push_back({ from, to, dist });
			graph[to].push_back({ to, from, dist });

			allConections.push_back({ from, to, dist });
			allConections.push_back({ to, from, dist });
		}
		dijkstra(bar, junctions, distancesBar);
		dijkstra(charly, junctions, distancesCharly);
		dijkstra(nito, junctions, distancesNito);
		for (Edge e : allConections)
		{
			if ((distancesBar[e.from] + e.dist + distancesCharly[e.to] == distancesBar[charly]) && (distancesBar[e.from] + e.dist + distancesNito[e.to] == distancesBar[nito]))
				path[e.from].push_back({ e.from, e.to, e.dist });
		}
		dfs(bar, 0);
		distCharly = distancesBar[charly] - maxDist != 0 ? distancesBar[charly] - maxDist : 0;
		distNito = distancesBar[nito] - maxDist != 0 ? distancesBar[nito] - maxDist : 0;
		cout << maxDist << " " << distCharly << " " << distNito << endl;
	}
	return 0;
}