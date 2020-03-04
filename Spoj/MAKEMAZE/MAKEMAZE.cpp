#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
 
using namespace std;
 
struct Point
{
	int row, column;
};
 
int t, rows, columns, flag, openings;
string line;
char tablero[25][25];
bool visited[25][25];
vector<Point> points;
 
void bfs(Point start, Point end)
{
	visited[start.row][start.column] = true;
	queue<Point> q;
	Point p;
	q.push(start);
	int row, column;
	while (!q.empty())
	{
		p = q.front();
		q.pop();
 
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
				row = p.row - 1, column = p.column;
			else if (i == 1)
				row = p.row, column = p.column + 1;
			else if (i == 2)
				row = p.row + 1, column = p.column;
			else
				row = p.row, column = p.column - 1;
 
			if (row >= 0 && column >= 0 && row < rows && column < columns && !visited[row][column] && tablero[row][column] == '.')
			{
				if (end.row == row && end.column == column)
					flag = 1;
				q.push({ row, column });
				visited[row][column] = true;
			}
		}
	}
}
 
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> rows >> columns;
		flag = 0;
		openings = 0;
		points.clear();
		for (int i = 0; i < rows; i++)
		{
			cin >> line;
			for (int j = 0; j < columns; j++)
			{
				tablero[i][j] = line[j];
				visited[i][j] = false;
				if ((i == 0 || j == 0 || i == rows - 1 || j == columns - 1) && tablero[i][j] == '.')
				{
					openings++;
					points.push_back({ i, j });
				}
			}
		}
		if (openings != 2)
			cout << "invalid" << endl;
		else
		{
			bfs(points[0], points[1]);
			if (flag)
				cout << "valid" << endl;
			else cout << "invalid" << endl;
		}
	}
	return 0;
}