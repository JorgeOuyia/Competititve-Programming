#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

struct Bitmask
{
    int row, column, keys;
};

char matrix[105][105];
int distances[105][105][16];
int di[4] = { -1, 0, 1, 0 };
int dj[4] = { 0, 1, 0, -1 };
int columns, rows;
string line;
Bitmask start;

int bfs(Bitmask start)
{
    distances[start.row][start.column][start.keys] = 0;
    queue<Bitmask> q;
    q.push(start);
    Bitmask current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (matrix[current.row][current.column] == 'X')
            return distances[current.row][current.column][current.keys];

        for (int i = 0; i < 4; i++)
        {
            int r = current.row, c = current.column, k = current.keys;

            r += di[i], c += dj[i];
            if (r >= 0 && c >= 0 && r < rows && c < columns && matrix[r][c] != '#')
            {
                if (matrix[r][c] == 'b')
                    k |= 1;
                else if (matrix[r][c] == 'y')
                    k |= 2;
                else if (matrix[r][c] == 'r')
                    k |= 4;
                else if (matrix[r][c] == 'g')
                    k |= 8;
                if (distances[r][c][k] == -1)
                {
                    if ((matrix[r][c] == 'B' && (k & 1)) || (matrix[r][c] == 'Y' && (k & 2)) || (matrix[r][c] == 'R' && (k & 4)) || (matrix[r][c] == 'G' && (k & 8))
                        || (matrix[r][c] != 'B' && matrix[r][c] != 'Y' && matrix[r][c] != 'R' && matrix[r][c] != 'G'))
                    {
                        distances[r][c][k] = distances[current.row][current.column][current.keys] + 1;
                        q.push({ r, c, k });
                    }
                }
            }
        }
    }
    return -1;
}

int main()
{
    while (cin >> rows >> columns && (rows != 0 || columns != 0))
    {
        memset(distances, -1, sizeof(distances));
        for (int i = 0; i < rows; i++)
        {
            cin >> line;
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                if (matrix[i][j] == '*')
                    start = { i, j, 0 };
            }
        }
        int dist = bfs(start);
        if (dist != -1)
            cout << "Escape possible in " << dist << " steps." << endl;
        else
            cout << "The poor student is trapped!" << endl;
    }
    return 0;
}