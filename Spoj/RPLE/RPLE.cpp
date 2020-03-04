#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
 
using namespace std;
 
int nodes, edges, a, b, spying;
 
vector<int> graph[1005];
map<int, bool> espias;
 
int main()
{
	int t, scenario = 1;
	cin >> t;
	while (t--)
	{
		cin >> nodes >> edges;
		spying = 1;
		espias.clear();
		for (int i = 0; i < nodes; i++)
		{
			graph[i].clear();
		}
		for (int i = 0; i < edges; i++)
		{
			cin >> a >> b;
			graph[a].push_back(b);
			espias[a] = true;
		}
		for (int i = 0; i < nodes; i++)
		{
			for (int j : graph[i])
			{
				if (espias[j])
					spying = 0;
			}
		}
		cout << "Scenario #" << scenario << ": ";
		if (spying)
			cout << "spying" << endl;
		else
			cout << "spied" << endl;
		scenario++;
	}
	return 0;
} 