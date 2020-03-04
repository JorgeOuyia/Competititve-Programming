#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <map>
 
using namespace std;
 
struct Point
{
	int row, column;
};
 
int dim, querys, factor, queryi, queryj;
 
char tablero[505][505];
int factores[505][505];
 
void bfs(Point v)
{
	factores[v.row][v.column] = 5;
 
	queue<Point> q;
	q.push(v);
	Point p;
	int row, column;
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		
		for (int i = 0; i < 8; i++)
		{
			if (i == 0)
				row = p.row - 1, column = p.column;
			else if (i == 1)
				row = p.row - 1, column = p.column + 1;
			else if (i == 2)
				row = p.row, column = p.column + 1;
			else if (i == 3)
				row = p.row + 1, column = p.column + 1;
			else if (i == 4)
				row = p.row + 1, column = p.column;
			else if (i == 5)
				row = p.row + 1, column = p.column - 1;
			else if (i == 6)
				row = p.row, column = p.column - 1;
			else
				row = p.row - 1, column = p.column - 1;
 
			if (row >= 0 && row < dim && column >= 0 && column < dim && factores[row][column] <= factores[p.row][p.column] - 1)
			{
				factores[row][column] = factores[p.row][p.column] - 1;
				q.push({ row, column });
			}
		}
	}
}
 
 
int main()
{
	while (cin >> dim >> querys)
	{
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				cin >> tablero[i][j];
				factores[i][j] = 1;
			}
		}
		for (int i = 0; i < querys; i++)
		{
			cin >> queryi >> queryj;
			queryi--, queryj--;
			bfs({ queryi, queryj });
		}
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				cout << (char)(((tablero[i][j] * factores[i][j]) % 93) + 33);
				if (j != dim - 1)
					cout << " ";
			}
			cout << endl;
		}
	}
	return 0;
}