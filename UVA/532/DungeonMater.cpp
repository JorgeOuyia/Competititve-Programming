#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <string>

#define INF 0x3f3f3f3f

using namespace std;

struct Point3D
{
    int level, row, column, dist;
};

struct Result
{
    bool possible;
    int dist;
};

int levels, rows, columns;
char matrix[35][35][35];
bool visited[35][35][35];
int dk[6] = {0, 0, 0, 0, 1, -1};
int di[6] = {-1, 0, 1, 0, 0, 0};
int dj[6] = {0, 1, 0, -1, 0, 0};
string line;
Point3D start, last;
Result res;

Result bfs(Point3D start, Point3D end)
{
    visited[start.level][start.row][start.column] = true;
    queue<Point3D> q;
    q.push(start);
    Point3D current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current.level == end.level && current.row == end.row && current.column == end.column)
            return {true, current.dist};

        for (int i = 0; i < 6; i++)
        {
            int l = current.level, r = current.row, c = current.column;

            l += dk[i], r += di[i], c += dj[i];
            if (l >= 0 && l < levels && r >= 0 && r < rows && c >= 0 && c < columns && !visited[l][r][c] && matrix[l][r][c] != '#')
            {
                visited[l][r][c] = true;
                q.push({l, r, c, current.dist + 1});
            }
        }
    }
    return {false, INF};
}

int main()
{
    while (cin >> levels >> rows >> columns && (levels != 0 || rows != 0 || columns != 0))
    {
        for (int k = 0; k < levels; k++)
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                    visited[k][i][j] = false;
        for (int k = 0; k < levels; k++)
        {
            for (int i = 0; i < rows; i++)
            {
                cin >> line;
                for (int j = 0; j < columns; j++)
                {
                    matrix[k][i][j] = line[j];
                    if (matrix[k][i][j] == 'S')
                        start = {k, i, j, 0};
                    else if (matrix[k][i][j] == 'E')
                        last = {k, i, j, 0};
                }
            }
        }
        res = bfs(start, last);
        if (!res.possible)
            cout << "Trapped!" << endl;
        else
            cout << "Escaped in " << res.dist << " minute(s)." << endl;
    }
    return 0;
}