#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Point2D
{
    int row, column, dist;
};

int rows, columns, rowsWithBombs, row, bombs, column;
bool visited[1005][1005];
char matrix[1005][1005];
int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};
Point2D start, last;

int bfs(Point2D start, Point2D end)
{
    visited[start.row][start.column] = true;
    queue<Point2D> q;
    q.push(start);
    Point2D current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current.row == end.row && current.column == end.column)
            return current.dist;

        for (int i = 0; i < 4; i++)
        {
            int r = current.row, c = current.column;

            r += di[i], c += dj[i];

            if (r >= 0 && r < rows && c >= 0 && c < columns && !visited[r][c])
            {
                visited[r][c] = true;
                q.push({r, c, current.dist + 1});
            }
        }
    }
    return -1;
}

int main()
{
    while (cin >> rows >> columns && (rows != 0 || columns != 0))
    {
        for (int i = 0; i <= rows; i++)
            for (int j = 0; j <= columns; j++)
                visited[i][j] = false;
        cin >> rowsWithBombs;
        for (int i = 0; i < rowsWithBombs; i++)
        {
            cin >> row >> bombs;
            for (int j = 0; j < bombs; j++)
            {
                cin >> column;
                visited[row][column] = true;
            }
        }
        cin >> start.row >> start.column;
        cin >> last.row >> last.column;
        start.dist = 0;
        cout << bfs(start, last) << endl;
    }
    return 0;
}