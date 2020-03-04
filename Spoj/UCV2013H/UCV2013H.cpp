#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
 
using namespace std;
 
int rows, columns;
 
int tablero[255][255], cont, total;
bool visited[255][255];
map<int, int> tam;
 
void dfs(int i, int j)
{
	visited[i][j] = true;
	cont++;
 
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
 
		if (row >= 0 && column >= 0 && row < rows && column < columns && !visited[row][column] && tablero[row][column] == 1)
		{
			dfs(row, column);
		}
	}
}
 
int main()
{
	while (cin >> rows >> columns && (rows != 0 || columns != 0))
	{
		tam.clear();
		cont = 1;
		total = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				cin >> tablero[i][j];
				visited[i][j] = false;
			}
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (!visited[i][j] && tablero[i][j] == 1)
				{
					total++;
					cont = 0;
					dfs(i, j);
					tam[cont]++;
				}
			}
		}
		cout << total << endl;
		for (map<int, int>::iterator it = tam.begin(); it != tam.end(); ++it)
		{
			cout << it->first << " " << it->second << endl;
		}
	}
	return 0;
}