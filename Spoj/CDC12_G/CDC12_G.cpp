#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <tuple>
 
using namespace std;
 
struct Edge
{
	int node, dist;
 
	bool operator<(const Edge& other) const
	{
		return other.dist < dist;
	}
};
 
int t, dim, levels, aux, level, row, column, d, flag, minDist, scenario, currentDist;
char tablero[25][25][25];
string line;
vector<int> mustPass;
vector<int> path;
map<tuple<int, int, int>, int> trad;
vector<Edge> graph[25 * 25 * 25];
vector<Edge> subGraph[25 * 25 * 25];
int distances[25 * 25 * 25];
bool visited[25 * 25 * 25];
 
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
	if (dist >= minDist)
		return;
	visited[start] = true;
	if (start == end && path.size() == mustPass.size() - 1)
		minDist = min(dist, minDist);
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
	scenario = 1;
	cin >> t;
	while (t--)
	{
		aux = 1;
		trad.clear();
		mustPass.clear();
		flag = true;
		path.clear();
		minDist = 0x3f3f3f3f;
		cin >> dim >> levels;
		for (int i = 0; i <= levels * dim * dim; i++)
			graph[i].clear(), distances[i] = 0x3f3f3f3f, visited[i] = false, subGraph[i].clear();
		for (int k = 0; k < levels; k++)
		{
			for (int i = 0; i < dim; i++)
			{
				cin >> line;
				for (int j = 0; j < dim; j++)
				{
					tablero[k][i][j] = line[j];
					trad[{k, i, j}] = aux;
					aux++;
					if (tablero[k][i][j] == '*' ||(k == 0 && i == 0 && j == 0))
						mustPass.push_back(trad[{k, i, j}]);
				}
			}
		}
		// Rellenamos la lista de adyacencia
		for (int k = 0; k < levels; k++)
		{
			for (int i = 0; i < dim; i++)
			{
				for (int j = 0; j < dim; j++)
				{
					for (int l = 0; l < 12; l++)
					{
						// Mismo nivel
						if (l == 0)
							level = k, row = i - 1, column = j;
						else if (l == 1)
							level = k, row = i, column = j + 1;
						else if (l == 2)
							level = k, row = i + 1, column = j;
						else if (l == 3)
							level = k, row = i, column = j - 1;
 
						// Nivel superior
						else if (l == 4)
							level = k + 1, row = i - 1, column = j;
						else if (l == 5)
							level = k + 1, row = i, column = j + 1;
						else if (l == 6)
							level = k + 1, row = i + 1, column = j;
						else if (l == 7)
							level = k + 1, row = i, column = j - 1;
 
						// Nivel inferior
						else if (l == 8)
							level = k - 1, row = i - 1, column = j;
						else if (l == 9)
							level = k - 1, row = i, column = j + 1;
						else if (l == 10)
							level = k - 1, row = i + 1, column = j;
						else
							level = k - 1, row = i, column = j - 1;
 
						if (level >= 0 && row >= 0 && column >= 0 && level < levels && row < dim && column < dim && tablero[level][row][column] != '#')
						{
							graph[trad[{k, i, j}]].push_back({ trad[{level, row, column}], 1 });
						}
					}
				}
			}
		}
 
		// Calculamos la minima distancia de todos los puntos a todos
		for (int i = 0; i < mustPass.size(); i++)
		{
			for (int j = i + 1; j < mustPass.size(); j++)
			{
				for (int l = 0; l <= levels * dim * dim; l++)
				{
					distances[l] = 0x3f3f3f3f;
				}
				d = dijkstra(mustPass[i], mustPass[j]);
				if (d != 0x3f3f3f3f)
				{
					subGraph[mustPass[i]].push_back({ mustPass[j], d });
					subGraph[mustPass[j]].push_back({ mustPass[i], d });
				}
				else
				{
					flag = false;
				}
			}
		}
		if (!flag)
		{
			cout << "Scenario #" << scenario << ": -1" << endl;
			scenario++;
			continue;
		}
 
		// Calculamos todos los posibles caminos y nos quedamos con el menor de todos
		for (int i = 1; i < mustPass.size(); i++)
		{
			for (int j = 0; j <= levels * dim * dim; j++)
				visited[j] = false;
			currentDist = 0;
			dfs(1, mustPass[i], currentDist);
		}
		cout << "Scenario #" << scenario << ": " << minDist << endl;
		scenario++;
	}
	return 0;
}