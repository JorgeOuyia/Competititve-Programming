#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

int tasks, precedences, a, b;

vector<int> graph[105];
bool visited[105];
stack<int> order;

void topologicalSort(int n)
{
	if (visited[n])
		return;
	visited[n] = true;
	for (int v : graph[n])
		topologicalSort(v);
	order.push(n);
	return;
}

int main()
{
	while (cin >> tasks >> precedences && (tasks != 0 || precedences != 0))
	{
		while (!order.empty())
			order.pop();
		for (int i = 1; i <= tasks; i++)
		{
			visited[i] = false;
			graph[i].clear();
		}
		for (int i = 0; i < precedences; i++)
		{
			cin >> a >> b;
			graph[a].push_back(b);
		}
		for (int i = 1; i <= tasks; i++)
		{
			if (!visited[i])
				topologicalSort(i);
		}
		int first = true;
		while (!order.empty())
		{
			if (first)
			{
				first = false;
				cout << order.top();
			}
			else
				cout << " " << order.top();
			order.pop();
		}
		cout << endl;
	}
	return 0;
}