#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
#include <stack>
 
using namespace std;
 
int t, rows, columns, pointer;
char tablero[105][105];
bool visited[105][105], flag;
string line, pattern = "ALLIZZWELL";
 
struct Point
{
	int row, column;
};
 
bool dfs(int i, int j, int l)
{
	int row, column;
	if (l >= pattern.size())
		return true;
		for (int t = 0; t < 8; t++)
		{
			if (t == 0)
				row = i - 1, column = j;
			else if (t == 1)
				row = i - 1, column = j + 1;
			else if (t == 2)
				row = i, column = j + 1;
			else if (t == 3)
				row = i + 1, column = j + 1;
			else if (t == 4)
				row = i + 1, column = j;
			else if (t == 5)
				row = i + 1, column = j - 1;
			else if (t == 6)
				row = i, column = j - 1;
			else
				row = i - 1, column = j - 1;
			if (row >= 0 && row < rows && column >= 0 && column < columns && !visited[row][column] && tablero[row][column] == pattern[l])
			{
				visited[row][column] = true;
				if (dfs(row, column, l + 1))
					return true;
				visited[row][column] = false;
			}
		}
	return false;
}
 
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> rows >> columns;
		flag = false;
		pointer = 1;
		for (int i = 0; i < rows; i++)
		{
			cin >> line;
			for (int j = 0; j < columns; j++)
			{
				tablero[i][j] = line[j];
				visited[i][j] = false;
			}
		}
		for (int i = 0; i < rows && !flag; i++)
		{
			for (int j = 0; j < columns && !flag; j++)
			{
				if (tablero[i][j] == 'A')
				{
					flag = dfs(i, j, 1);
				}
			}
		}
		if (flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}