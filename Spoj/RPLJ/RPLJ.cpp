#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
 
using namespace std;
 
struct Point
{
	int row, column;
};
 
int scenario, dim, minNormalDistance, minDiagonalDistance;
string line;
 
char tablero[1005][1005];
bool visited[1005][1005];
vector<Point> mapA;
vector<Point> mapB;
 
void dfsA(int i, int j)
{
	mapA.push_back({ i, j });
	visited[i][j] = true;
	int row, column;
	for (int l = 0; l < 4; l++)
	{
		if (l == 0)
			row = i - 1, column = j;
		else if (l == 1)
			row = i, column = j + 1;
		else if (l == 2)
			row = i + 1, column = j;
		else
			row = i, column = j - 1;
 
		if (row >= 0 && row < dim && column >= 0 && column < dim && !visited[row][column] && tablero[row][column] == '*')
		{
			dfsA(row, column);
		}
	}
}
 
void dfsB(int i, int j)
{
	mapB.push_back({ i, j });
	visited[i][j] = true;
	int row, column;
	for (int l = 0; l < 4; l++)
	{
		if (l == 0)
			row = i - 1, column = j;
		else if (l == 1)
			row = i, column = j + 1;
		else if (l == 2)
			row = i + 1, column = j;
		else
			row = i, column = j - 1;
 
		if (row >= 0 && row < dim && column >= 0 && column < dim && !visited[row][column] && tablero[row][column] == '*')
		{
			dfsB(row, column);
		}
	}
}
 
int normalDistance(Point a, Point b)
{
	return abs(a.row - b.row) + abs(a.column - b.column);
}
 
int diagonalDistance(Point a, Point b)
{
	return max(abs(a.row - b.row), abs(a.column - b.column));
}
 
int main()
{
	int t;
	cin >> t;
	scenario = 1;
	while (t--)
	{
		cin >> dim;
		mapA.clear();
		mapB.clear();
		minNormalDistance = 0x3f3f3f3f;
		minDiagonalDistance = 0x3f3f3f3f;
		for (int i = 0; i < dim; i++)
		{
			cin >> line;
			for (int j = 0; j < dim; j++)
			{
				tablero[i][j] = line[j];
				visited[i][j] = false;
			}
		}
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				if (mapA.size() == 0 && !visited[i][j] && tablero[i][j] == '*')
				{
					dfsA(i, j);
				}
				if (mapB.size() == 0 && !visited[i][j] && tablero[i][j] == '*')
				{
					dfsB(i, j);
				}
			}
		}
		for (int i = 0; i < mapA.size(); i++)
		{
			for (int j = 0; j < mapB.size(); j++)
			{
				minNormalDistance = min(minNormalDistance, normalDistance(mapA[i], mapB[j]));
				minDiagonalDistance = min(minDiagonalDistance, diagonalDistance(mapA[i], mapB[j]));
			}
		}
		if (minNormalDistance <= minDiagonalDistance)
			cout << "Scenario #" << scenario << ": " << 1 << endl;
		else
			cout << "Scenario #" << scenario << ": " << 0 << endl;
		scenario++;
	}
	return 0;
} 