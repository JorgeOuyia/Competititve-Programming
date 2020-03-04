#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
 
using namespace std;
 
int t, scenario, bugs, interactions, a, b, flag;
 
vector<int> grafo[2002];
bool visitado[2002];
int sexo[2002];
 
void heterosexual(int u)
{
	stack<int> q;
	q.push(u);
	visitado[u] = true;
	sexo[u] = 1;
	int v;
	while (!q.empty())
	{
		v = q.top();
		q.pop();
		for (int i = 0; i < grafo[v].size(); i++)
		{
			if (sexo[grafo[v][i]] == -1)
			{
				q.push(grafo[v][i]);
				sexo[grafo[v][i]] = 1 - sexo[v];
				visitado[grafo[v][i]] = true;
			}
			else if (sexo[grafo[v][i]] == sexo[v])
				flag = 0;
		}
	}
}
 
int main()
{
	scenario = 1;
	cin >> t;
	while (t--)
	{
		flag = 1;
		cin >> bugs >> interactions;
		for (int i = 0; i <= bugs; i++)
		{
			sexo[i] = -1;
			visitado[i] = false;
			grafo[i].clear();
		}
		for (int i = 0; i < interactions; i++)
		{
			cin >> a >> b;
			grafo[a].push_back(b);
			grafo[b].push_back(a);
		}
		for (int i = 1; i <= bugs && flag; i++)
		{
			if (!visitado[i])
				heterosexual(i);
		}
		if (flag)
			cout << "Scenario #" << scenario << ":" << endl << "No suspicious bugs found!" << endl;
		else
			cout << "Scenario #" << scenario << ":" << endl << "Suspicious bugs found!" << endl;
		scenario++;
	}
	return 0;
} 