#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <sstream>

#define INF 0x3f3f3f3f

using namespace std;

int connectionNumber, from, to, node, ttl;
unordered_map<int, int> hashMap;
int graph[105][105];
string line;

int main()
{
	int scenario = 1;
	while (cin >> connectionNumber && connectionNumber != 0)
	{
		hashMap.clear();
		for (int i = 1; i < 105; i++)
			for (int j = 1; j < 105; j++)
				graph[i][j] = INF, graph[i][i] = 0;
		int id = 1;
		for (int i = 0; i < connectionNumber; i++)
		{
			cin >> from >> to;
			if (hashMap.find(from) == hashMap.end())
				hashMap[from] = id++;
			if (hashMap.find(to) == hashMap.end())
				hashMap[to] = id++;
			graph[hashMap[from]][hashMap[to]] = 1;
			graph[hashMap[to]][hashMap[from]] = 1;
		}
		for (int k = 1; k <= hashMap.size(); k++)
		{
			for (int i = 1; i <= hashMap.size(); i++)
			{
				for (int j = 1; j <= hashMap.size(); j++)
				{
					graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
				}
			}
		}
		while (cin >> node >> ttl && (node != 0 || ttl != 0))
		{
			if (node == 0 && ttl == 0)
				break;
			if (hashMap.find(node) == hashMap.end())
				cout << "Case " << scenario << ": " << hashMap.size() << " nodes not reachable from node " << node << " with TTL = " << ttl << "." << endl;
			else
			{
				int source = hashMap[node];
				int cont = 0;
				for (int i = 1; i <= hashMap.size(); i++)
					if (graph[source][i] > ttl&& i != source)
						cont++;
				cout << "Case " << scenario << ": " << cont << " nodes not reachable from node " << node << " with TTL = " << ttl << "." << endl;
			}
			scenario++;
		}
	}
	return 0;
}