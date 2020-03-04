#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <stack>
#include <queue>
#include <set>
 
using namespace std;
 
struct State
{
	int level, number;
 
	bool operator<(const State& other) const
	{
		if (other.level < level)
			return true;
		else if (other.level == level)
			return other.number < number;
		return false;
	}
};
 
vector<pair<int, int>> order;
bool visited[1005];
int inDegree[1005];
int t, employees, relations, a, b, scenario;
vector<int> adjList[1005];
priority_queue<State> pq;
 
void kahnTopoSort()
{
	State s;
	int number, level;
	while (!pq.empty())
	{
		s = pq.top();
		pq.pop();
 
		order.push_back({ s.level, s.number });
 
		number = s.number;
		level = s.level;
		for (int j : adjList[number])
		{
			if (!visited[j])
			{
				inDegree[j]--;
				if (inDegree[j] == 0)
				{
					pq.push({ level + 1, j });
					visited[j] = true;
				}
			}
		}
	}
}
 
int main()
{
	scenario = 1;
	cin >> t;
	while (t--)
	{
		order.clear();
		cin >> employees >> relations;
		for (int i = 0; i < employees; i++)
			visited[i] = false, inDegree[i] = 0, adjList[i].clear();
		while (!pq.empty())
			pq.pop();
		for (int i = 0; i < relations; i++)
		{
			cin >> a >> b;
			inDegree[a]++;
			adjList[b].push_back(a);
		}
		for (int i = 0; i < employees; i++)
		{
			if (inDegree[i] == 0)
			{
				pq.push({ 1, i });
				visited[i] = true;
			}
		}
		kahnTopoSort();
		sort(order.begin(), order.end());
		cout << "Scenario #" << scenario << ":" << endl;
		for (int i = 0; i < order.size(); i++)
		{
			cout << order[i].first << " " << order[i].second << endl;
		}
		scenario++;
	}
	return 0;
}