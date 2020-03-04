#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <queue>
#include <map>
 
using namespace std;
 
struct Edge
{
	int node, dist;
 
	bool operator<(const Edge& other) const
	{
		return other.dist < dist;
	}
};
 
int r, c, aux, row, column, flag, minDist, currentDist;
string line;
char tablero[25][25];
map<pair<int, int>, int> trad;
vector<Edge> graph[25 * 25];
vector<Edge> subGraph[25 * 25];
vector<int> path;
int distances[25 * 25];
bool visited[25 * 25];
vector<int> mustPass;
pair<int, int> inicio;
 
int dijkstra(int start, int end)
{
	distances[start] = 0;
	priority_queue<Edge> pq;
	pq.push({ start, 0 });
	while (!pq.empty())
	{
		Edge n = pq.top();
		pq.pop();
		if (distances[n.node] >= n.dist)
		{
			for (Edge D : graph[n.node])
			{
				int peso = n.dist + D.dist;
				if (distances[D.node] > peso)
				{
					pq.push({ D.node, peso });
					distances[D.node] = peso;
				}
			}
		}
	}
	return distances[end];
}
 
void dfs(int start, int end, int dist)
{
	int in = trad[{inicio.first, inicio.second}];
	if (dist >= minDist)
		return;
	visited[start] = true;
	if (start == end && path.size() == mustPass.size() - 1)
	{
		minDist = min(minDist, dist);
	}
	for (Edge u : subGraph[start])
	{
		if (!visited[u.node])
		{
			path.push_back(u.node);
			dist += u.dist;
			dfs(u.node, end, dist);
			path.erase(find(path.begin(), path.end(), u.node));
			dist -= u.dist;
		}
	}
	visited[start] = false;
}
 
int main()
{
	while (cin >> c >> r && (c != 0 || r != 0))
	{
		trad.clear();
		aux = 1;
		flag = true;
		mustPass.clear();
		minDist = 0x3f3f3f3f;
		for (int i = 0; i <= r * c; i++)
			graph[i].clear(), subGraph[i].clear(), distances[i] = 0x3f3f3f3f;
		for (int i = 0; i < r; i++)
		{
			cin >> line;
			for (int j = 0; j < c; j++)
			{
				tablero[i][j] = line[j];
				trad[{i, j}] = aux;
				aux++;
				if (tablero[i][j] == 'o')
					inicio.first = i, inicio.second = j, mustPass.push_back(trad[{i, j}]);
				if (tablero[i][j] == '*')
					mustPass.push_back(trad[{i, j}]);
			}
		}
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				for (int l = 0; l < 4; l++)
				{
					if (l == 0)
						row = i - 1, column = j;
					else if (l == 1)
						row = i, column = j + 1;
					else if (l == 2)
						row = i + 1, column = j;
					else
						row = i, column = j - 1;
					if (row >= 0 && column >= 0 && row < r && column < c && tablero[row][column] != 'x')
					{
						graph[trad[{i, j}]].push_back({ trad[{row, column}], 1 });
					}
				}
			}
		}
		for (int i = 0; i < mustPass.size(); i++)
		{
			for (int j = i + 1; j < mustPass.size(); j++)
			{
				for (int l = 0; l <= r * c; l++)
					distances[l] = 0x3f3f3f3f;
				int d = dijkstra(mustPass[i], mustPass[j]);
				if (d != 0x3f3f3f3f)
				{
					subGraph[mustPass[i]].push_back({ mustPass[j], d }), subGraph[mustPass[j]].push_back({ mustPass[i], d });
				}
				else
					flag = false;
			}
		}
		if (!flag)
		{
			cout << -1 << endl;
			continue;
		}
		for (int i = 0; i < mustPass.size(); i++)
		{
			for (int j = 0; j <= r * c; j++)
				visited[j] = false;
			if (trad[{inicio.first, inicio.second}] != mustPass[i])
			{
				currentDist = 0;
				dfs(trad[{inicio.first, inicio.second}], mustPass[i], currentDist);
			}
		}
		cout << minDist << endl;
	}
	return 0;
}