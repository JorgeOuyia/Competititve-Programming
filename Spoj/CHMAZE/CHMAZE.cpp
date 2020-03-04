#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
struct Point
{
	int row, column, pattern, dist;
};
 
int rows, columns, patterns, res, scenario;
string line;
int tablero[25][25][15];
 
int bfs(Point start, Point end)
{
	queue<Point> q;
	Point p;
	if (start.row == end.row && start.column == end.column)
		return 0;
	tablero[start.row][start.column][start.pattern] = 1;
	p.row = start.row;
	p.column = start.column;
	p.pattern = start.pattern;
	p.dist = start.dist;
	q.push(p);
	Point v;
	int row, column, pattern;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		for (int i = 0; i < 5; i++)
		{
			pattern = (v.pattern + 1) % patterns;
			if (i == 0)
				row = v.row, column = v.column;
			else if (i == 1)
				row = v.row + 1, column = v.column;
			else if (i == 2)
				row = v.row - 1, column = v.column;
			else if (i == 3)
				row = v.row, column = v.column + 1;
			else if (i == 4)
				row = v.row, column = v.column - 1;
			if (row >= 0 && column >= 0 && row < rows && column < columns && tablero[row][column][pattern] == 0)
			{
				tablero[row][column][pattern] = 1;
				Point u;
				u.row = row;
				u.column = column;
				u.pattern = pattern;
				u.dist = v.dist + 1;
				if (row == end.row && column == end.column)
					return v.dist;
				q.push(u);
			}
		}
	}
	return -1;
}
 
int main()
{
	scenario = 1;
	while (cin >> rows >> columns >> patterns && (rows != 0 || columns != 0 || patterns != 0))
	{
		for (int k = 0; k < patterns; k++)
		{
			for (int i = 0; i < rows; i++)
			{
				cin >> line;
				for (int j = 0; j < columns; j++)
				{
					tablero[i][j][k] = line[j] - '0';
				}
			}
		}
		res = bfs({ 0, 0, 0, 1 }, { rows - 1, columns - 1, 0, 0 });
		if (res != -1)
			cout << "Case " << scenario << ": " << "Luke and Leia can escape in " << res << " steps." << endl;
		else
			cout << "Case " << scenario << ": " << "Luke and Leia cannot escape." << endl;
		scenario++;
	}
	return 0;
}