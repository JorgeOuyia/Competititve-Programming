#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>

using namespace std;

struct Pair_Hash
{
	template <class T1, class T2>
	size_t operator()(pair<T1, T2> const& pair) const
	{
		size_t h1 = hash<T1>()(pair.first);
		size_t h2 = hash<T2>()(pair.second);

		return h1 ^ h2;
	}
};

long long int dim, places, row, column;
char dir;
pair<int, int> start, last;
vector<int> graph[35 * 35];
bool visited[35 * 35];
long long int dp[35 * 35];
unordered_map<pair<int, int>, unordered_set<pair<int, int>, Pair_Hash>, Pair_Hash> restrictions;
unordered_map<pair<int, int>, int, Pair_Hash> hashMap;
stack<int> topoOrder;
map<int, int> allNodes;

void topoSort()
{
	queue<int> q;
	for (auto it = allNodes.begin(); it != allNodes.end(); ++it)
	{
		if (!it->second)
			q.push(it->first);
	}

	int current;
	while (!q.empty())
	{
		current = q.front(), q.pop();
		topoOrder.push(current);

		for (int v : graph[current])
		{
			allNodes[v]--;

			if (!allNodes[v])
				q.push(v);
		}
	}
}

long long int countAllPaths(int source, int destination)
{
	dp[destination] = 1;

	int u;
	while (!topoOrder.empty())
	{
		u = topoOrder.top(), topoOrder.pop();
		for (int v : graph[u])
			dp[u] += dp[v];
	}
	return dp[source];
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cin >> dim;
		cin >> start.second >> start.first;
		cin >> last.second >> last.first;
		cin >> places;
		restrictions.clear();
		allNodes.clear();
		int id = 1;
		for (int i = 0; i <= dim * dim; i++)
			graph[i].clear(), visited[i] = false, dp[i] = 0;
		for (int i = 1; i <= dim; i++)
			for (int j = 1; j <= dim; j++)
				hashMap[{i, j}] = id++;
		for (int i = 0; i < places; i++)
		{
			cin >> column >> row >> dir;
			if (dir == 'N')
				restrictions[{row, column}].insert({ row + 1, column }), restrictions[{row + 1, column}].insert({ row, column });
			else if (dir == 'S')
				restrictions[{row, column}].insert({ row - 1, column }), restrictions[{row - 1, column}].insert({ row, column });
			else if (dir == 'E')
				restrictions[{row, column}].insert({ row, column + 1 }), restrictions[{row, column + 1}].insert({ row, column });
			else
				restrictions[{row, column}].insert({ row, column - 1 }), restrictions[{row, column - 1}].insert({ row, column });
		}
		for (int i = 1; i <= dim; i++)
		{
			for (int j = 1; j <= dim; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					pair<int, int> source, destiny;
					int r = i, c = j;
					source = { i, j };
					if (k == 0)
						r += 1;
					else
						c += 1;
					if (r >= 1 && r <= dim && c >= 1 && c <= dim)
					{
						destiny = { r, c };
						if (restrictions.find(source) != restrictions.end())
						{
							if (restrictions[source].find(destiny) != restrictions[source].end())
								continue;
						}
						if (restrictions.find(destiny) != restrictions.end())
						{
							if (restrictions[destiny].find(source) != restrictions[destiny].end())
								continue;
						}
						graph[hashMap[{i, j}]].push_back(hashMap[{r, c}]);
						allNodes[hashMap[{i, j}]];
						allNodes[hashMap[{r, c}]]++;
					}
				}
			}
		}
		topoSort();
		cout << countAllPaths(hashMap[start], hashMap[last]) << endl;
	}
	return 0;
}