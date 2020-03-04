#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
 
using namespace std;
 
struct State
{
	int num;
 
	bool operator<(const State& other) const
	{
		return other.num < num;
	}
};
 
int tasks, rules, a, b, c, d;
vector<int> graph[105];
bool visited[105];
int inDegree[105];
vector<int> topo;
priority_queue<State> pq;
 
void kahnTopoSort()
{
	State s;
	while (!pq.empty())
	{
		s = pq.top();
		pq.pop();
 
		topo.push_back(s.num);
 
		for (int j : graph[s.num])
		{
			if (!visited[j])
			{
				inDegree[j]--;
				if (inDegree[j] == 0)
					visited[j] = true, pq.push({ j });
			}
		}
	}
}
 
 
int main()
{
	while (cin >> tasks >> rules)
	{
		for (int i = 1; i <= tasks; i++)
			visited[i] = false, inDegree[i] = 0;
		for (int i = 0; i < rules; i++)
		{
			cin >> a >> b;
			while (b--)
			{
				cin >> c;
				graph[c].push_back(a);
				inDegree[a]++;
			}
		}
		for (int i = 1; i <= tasks; i++)
			if (inDegree[i] == 0)
				pq.push({ i });
		kahnTopoSort();
		for (int i = 0; i < topo.size(); i++)
			cout << topo[i] << " ";
	}
	return 0;
}