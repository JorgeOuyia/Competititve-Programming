#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <map>
 
using namespace std;
 
struct Point
{
	int row, column, doorsState;
};
 
int rows, columns;
string line;
char tablero[105][105];
int distances[105][105][3];
Point harry;
 
int bfs(Point start)
{
	if (start.row == rows - 1 || start.column == columns - 1 || start.row == 0 || start.column == 0)
		return 1;
	queue<Point> q;
	distances[start.row][start.column][start.doorsState] = 1;
	Point p;
	Point v;
	q.push(start);
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
				v.row = p.row - 1, v.column = p.column, v.doorsState = p.doorsState;
			else if (i == 1)
				v.row = p.row, v.column = p.column + 1, v.doorsState = p.doorsState;
			else if (i == 2)
				v.row = p.row + 1, v.column = p.column, v.doorsState = p.doorsState;
			else
				v.row = p.row, v.column = p.column - 1, v.doorsState = p.doorsState;
			if (v.row >= 0 && v.row < rows && v.column >= 0 && v.column < columns && tablero[v.row][v.column] != 'W')
			{
				if ((tablero[v.row][v.column] == 'D' && v.doorsState == 1) || (tablero[v.row][v.column] != 'D'))
				{
					if (v.row == 0 || v.row == rows - 1 || v.column == 0 || v.column == columns - 1)
						return distances[p.row][p.column][p.doorsState] + 1;
					if (tablero[v.row][v.column] == 'O')
						v.doorsState = 1;
					else if (tablero[v.row][v.column] == 'C')
						v.doorsState = 2;
					if (distances[v.row][v.column][v.doorsState] > distances[p.row][p.column][p.doorsState] + 1)
					{
						q.push(v);
						distances[v.row][v.column][v.doorsState] = distances[p.row][p.column][p.doorsState] + 1;
					}
				}
			}
		}
	}
	return -1;
}
 
int main()
{
	while (cin >> rows >> columns && (rows != -1 || columns != -1))
	{
		for (int i = 0; i < rows; i++)
		{
			cin >> line;
			for (int j = 0; j < columns; j++)
			{
				tablero[i][j] = line[j];
				distances[i][j][0] = 0x3f3f3f3f - 100;
				distances[i][j][1] = 0x3f3f3f3f - 100;
				distances[i][j][2] = 0x3f3f3f3f - 100;
				if (tablero[i][j] == 'H')
					harry.row = i, harry.column = j, harry.doorsState = 0;
			}
		}
		cout << bfs(harry) << endl;
	}
	return 0;
}