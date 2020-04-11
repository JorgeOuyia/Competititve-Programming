#include <iostream>
#include <iostream>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
	int row, column, dist;

	bool operator<(const Edge& other) const
	{
		return other.dist < dist;
	}
};

int matrix[1005][1005];
int distances[1005][1005];
int di[4] = { -1, 0, 1, 0 };
int dj[4] = { 0, 1, 0, -1 };
int rows, columns;

int dijkstra(Edge start)
{
	distances[start.row][start.column] = matrix[start.row][start.column];
	priority_queue<Edge> pq;
	pq.push({ start.row, start.column, distances[start.row][start.column] });
	Edge current;
	while (!pq.empty())
	{
		current = pq.top(), pq.pop();

		for (int i = 0; i < 4; i++)
		{
			int r = current.row, c = current.column;

			r += di[i], c += dj[i];

			if (r >= 0 && c >= 0 && r < rows && c < columns && (distances[r][c] > distances[current.row][current.column] + matrix[r][c]))
			{
				distances[r][c] = distances[current.row][current.column] + matrix[r][c];
				pq.push({ r, c, distances[current.row][current.column] + matrix[r][c] });
			}
		}
	}
	return distances[rows - 1][columns - 1];
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cin >> rows >> columns;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				cin >> matrix[i][j];
				distances[i][j] = INF;
			}
		}
		cout << dijkstra({ 0, 0, matrix[0][0] }) << endl;
	}
	return 0;
}