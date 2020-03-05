#include <iostream>

using namespace std;

int n, m, num, ant, current;
int parent[30005], sz[30005];

int find(int v)
{
	if (parent[v] == v)
		return parent[v];
	return parent[v] = find(parent[v]);
}

void connect(int u, int v)
{
	u = find(u);
	v = find(v);
	if (u != v)
	{
		if (sz[u] >= sz[v])
		{
			parent[v] = u;
			sz[u] += sz[v];
		}
		else
		{
			parent[u] = v;
			sz[v] += sz[u];
		}
	}
}

int main()
{
	while (cin >> n >> m && (n != 0 || m != 0))
	{
		for (int i = 0; i < n; i++)
			parent[i] = i, sz[i] = 1;
		for (int i = 0; i < m; i++)
		{
			cin >> num;
			cin >> ant;
			for (int i = 0; i < num - 1; i++)
			{
				cin >> current;
				connect(ant, current);
				ant = current;
			}
		}
		cout << sz[find(0)] << endl;
	}
	return 0;
}