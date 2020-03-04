#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
 
using namespace std;
 
char tablero[15][15];
bool visited[15][15];
 
int rows, skip, columns, totalSquares, res, scenario, visitedCells, maxColumn;
pair<int, int> first;
 
void dfs(int i, int j, int cont)
{
	visited[i][j] = true;
	bool noRoute = true;
	int row, column;
	for (int l = 0; l < 8; l++)
	{
		if (l == 0)
			row = i - 2, column = j - 1;
		else if (l == 1)
			row = i - 2, column = j + 1;
		else if (l == 2)
			row = i - 1, column = j - 2;
		else if (l == 3)
			row = i - 1, column = j + 2;
		else if (l == 4)
			row = i + 1, column = j - 2;
		else if (l == 5)
			row = i + 1, column = j + 2;
		else if (l == 6)
			row = i + 2, column = j - 1;
		else
			row = i + 2, column = j + 1;
 
		if (row >= 0 && column >= 0 && row < rows && column < maxColumn && tablero[row][column] != '.' && !visited[row][column])
		{
			noRoute = false;
			dfs(row, column, cont + 1);
		}
	}
	if (noRoute)
	{
		if (visitedCells < cont)
			visitedCells = cont;
	}
	visited[i][j] = false;
}
 
int main()
{
	scenario = 1;
	while (cin >> rows && rows != 0)
	{
		totalSquares = 0;
		maxColumn = -1;
		visitedCells = -1;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				tablero[i][j] = '.';
				visited[i][j] = false;
			}
		}
		for (int i = 0; i < rows; i++)
		{
			cin >> skip >> columns;
			for (int j = skip; j < skip + columns; j++)
			{
				tablero[i][j] = '#';
				totalSquares++;
				maxColumn = max(maxColumn, j + 1);
			}
		}
		dfs(0, 0, 1);
		res = totalSquares - visitedCells;
		if (res == 1)
			cout << "Case " << scenario << ", " << res << " square can not be reached." << endl;
		else
			cout << "Case " << scenario << ", " << res << " squares can not be reached." << endl;
		scenario++;
	}
	return 0;
}