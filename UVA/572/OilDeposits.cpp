#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

struct Point
{
    int row, column;
};

int rows, columns;
string line;
char matrix[105][105];
bool visited[105][105];
int di[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dj[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int bfs(int row, int column)
{
    visited[row][column] = true;
    queue<Point> q;
    q.push({ row, column });
    Point current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (int i = 0; i < 8; i++)
        {
            int r = current.row + di[i], c = current.column + dj[i];

            if (r >= 0 && c >= 0 && r < rows && c < columns && !visited[r][c] && matrix[r][c] == '@')
            {
                visited[r][c] = true;
                q.push({ r, c });
            }
        }
    }
    return 1;
}

int main()
{
    while (cin >> rows >> columns && (rows != 0 || columns != 0))
    {
        for (int i = 0; i < rows; i++)
        {
            cin >> line;
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                visited[i][j] = false;
            }
        }
        int res = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (!visited[i][j] && matrix[i][j] == '@')
                    res += bfs(i, j);
            }
        }
        cout << res << endl;
    }
    return 0;
}