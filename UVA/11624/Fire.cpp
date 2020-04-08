#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>

#define INF 0x3f3f3f3f

using namespace std;

struct Point2D
{
    int row, column, time;
};

int rows, columns;
char matrix[1005][1005];
int fire[1005][1005];
int joe[1005][1005];
int di[4] = { -1, 0, 1, 0 };
int dj[4] = { 0, 1, 0, -1 };
string line;
Point2D start;
queue<Point2D> f;

void floodFillFire()
{
    Point2D current;
    while (!f.empty())
    {
        current = f.front(), f.pop();
        fire[current.row][current.column] = current.time;

        for (int i = 0; i < 4; i++)
        {
            int r = current.row, c = current.column;

            r += di[i], c += dj[i];
            if (r >= 0 && c >= 0 && r < rows && c < columns && matrix[r][c] != '#' && fire[r][c] == INF)
            {
                fire[r][c] = current.time + 1;
                f.push({ r, c, current.time + 1 });
            }
        }
    }
}

void floodFillJoe(Point2D start)
{
    joe[start.row][start.column] = 0;
    queue<Point2D> q;
    q.push(start);
    Point2D current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (int i = 0; i < 4; i++)
        {
            int r = current.row, c = current.column;

            r += di[i], c += dj[i];
            if (r >= 0 && r < rows && c >= 0 && c < columns && matrix[r][c] != '#' && joe[r][c] == INF)
            {
                joe[r][c] = current.time + 1;
                q.push({ r, c, current.time + 1 });
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> rows >> columns;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                fire[i][j] = INF, joe[i][j] = INF;
        for (int i = 0; i < rows; i++)
        {
            cin >> line;
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                if (matrix[i][j] == 'J')
                    start = { i, j, 0 };
                else if (matrix[i][j] == 'F')
                    f.push({ i, j, 0 });
            }
        }
        floodFillFire();
        floodFillJoe(start);

        int res = INF;
        for (int i = 0; i < rows; i++)
        {
            if (joe[i][0] < fire[i][0])
                res = min(res, joe[i][0]);
            if (joe[i][columns - 1] < fire[i][columns - 1])
                res = min(res, joe[i][columns - 1]);
        }

        for (int i = 0; i < columns; i++)
        {
            if (joe[0][i] < fire[0][i])
                res = min(res, joe[0][i]);
            if (joe[rows - 1][i] < fire[rows - 1][i])
                res = min(res, joe[rows - 1][i]);
        }
        if (res != INF)
            cout << res + 1 << endl;
        else
            cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}