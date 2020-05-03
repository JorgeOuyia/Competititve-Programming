#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

#define INF 0x3f3f3f3f

using namespace std;

struct Point2D
{
    int row, column;
};

string source, destiny;
Point2D from, to;
int distances[8][8];
int di[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dj[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int bfs(Point2D start, Point2D last)
{
    distances[start.row][start.column] = 0;
    queue<Point2D> q;
    q.push(start);
    Point2D current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current.row == last.row && current.column == last.column)
            return distances[current.row][current.column];

        for (int i = 0; i < 8; i++)
        {
            int r = current.row + di[i], c = current.column + dj[i];

            if (r >= 0 && c >= 0 && r < 8 && c < 8 && distances[r][c] > distances[current.row][current.column] + 1)
                distances[r][c] = distances[current.row][current.column] + 1, q.push({r, c});
        }
    }
    return -1;
}

int main()
{
    while (cin >> source >> destiny)
    {
        from.row = source[1] - '0' - 1;
        from.column = source[0] - 'a';

        to.row = destiny[1] - '0' - 1;
        to.column = destiny[0] - 'a';

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                distances[i][j] = INF;
        cout << "To get from " << source << " to " << destiny << " takes " << bfs(from, to) << " knight moves." << endl;
    }
    return 0;
}