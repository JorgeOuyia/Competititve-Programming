#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

struct Point
{
	int row, column;
};

string line;
char matrix[85][85];
int di[4] = { -1, 0, 1, 0 };
int dj[4] = { 0, 1, 0, -1 };

void bfs(int row, int column, char character)
{
	matrix[row][column] = character;
	queue<Point> q;
	q.push({ row, column });
	Point current;
	while (!q.empty())
	{
		current = q.front(), q.pop();

		for (int i = 0; i < 4; i++)
		{
			int r = current.row + di[i], c = current.column + dj[i];

			if (r >= 0 && c >= 0 && matrix[r][c] == ' ')
			{
				matrix[r][c] = character;
				q.push({ r, c });
			}
		}
	}
}

int main()
{
	int first = true, rows = 0, columns = 0;
	char contorn;
	for (int i = 0; i < 85; i++)
		for (int j = 0; j < 85; j++)
			matrix[i][j] = '@';
	while (getline(cin, line))
	{
		int fullUnderscoure = true;
		for (int i = 0; i < line.length(); i++)
			if (line[i] != '_')
				fullUnderscoure = false;
		if (line == " " || line == "")
		{
			fullUnderscoure = false;
		}
		if (fullUnderscoure)
		{
			int contin = true;
			for (int i = 0; i < rows && contin; i++)
			{
				for (int j = 0; j < columns && contin; j++)
				{
					if (matrix[i][j] != ' ' && matrix[i][j] != '@')
					{
						contorn = matrix[i][j];
						contin = false;
						break;
					}
				}
			}
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < columns; j++)
				{
					if (matrix[i][j] != ' ' && matrix[i][j] != contorn && matrix[i][j] != '@')
						bfs(i, j, matrix[i][j]);
				}
			}
			int col = 0;
			for (int i = 0; i < rows; i++)
			{
				col = 0;
				while (matrix[i][col] != '@')
					cout << matrix[i][col++];
				cout << endl;
			}
			cout << line << endl;
			first = true;
			rows = 0;
			for (int i = 0; i < 85; i++) for (int j = 0; j < 85; j++) matrix[i][j] = '@';
		}
		else
		{
			for (int i = 0; i < line.length(); i++)
				matrix[rows][i] = line[i];
			rows++;
			columns = max((int)line.length(), columns);
		}
	}
	return 0;
}