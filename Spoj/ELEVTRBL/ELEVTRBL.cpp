#include <iostream>
#include <string>
#include <cmath>
#include <queue>
 
using namespace std;
 
int floors, start, goal, up, down, res;
 
int distances[1000005];
 
void bfs(int start)
{
	distances[start] = 0;
	queue<int> q;
	q.push(start);
	int node;
	int r;
	while (!q.empty())
	{
		node = q.front();
		q.pop();
		r = node + up;
		if (r <= floors && distances[r] == -1)
		{
			distances[r] = distances[node] + 1;
			q.push(r);
		}
		r = node - down;
		if (r >= 1 && distances[r] == -1)
		{
			distances[r] = distances[node] + 1;
			q.push(r);
		}
	}
}
 
int main()
{
	while (cin >> floors >> start >> goal >> up >> down)
	{
		for (int i = 1; i <= floors; i++)
			distances[i] = -1;
		bfs(start);
		if (distances[goal] != -1)
			cout << distances[goal];
		else
			cout << "use the stairs";
	}
	return 0;
}