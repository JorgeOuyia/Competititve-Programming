#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

struct Moment
{
    int row, column, moment;
};

char matrix[15][20][20];
int distances[15][20][20];
int dk[12] = {-1, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1};
int di[12] = {-1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0};
int dj[12] = {0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1};
int columns, rows, moments;
string line;
Moment start;

int bfs(Moment start)
{
    distances[start.moment][start.row][start.column] = 0;
    queue<Moment> q;
    q.push(start);
    Moment current;
    while (!q.empty())
    {
        current = q.front(), q.pop();
        int actualMoment = current.moment;

        if (matrix[current.moment][current.row][current.column] == 'O')
            return distances[current.moment][current.row][current.column];

        for (int i = 0; i < 12; i++)
        {
            int r = current.row, c = current.column, m = current.moment;

            r += di[i], c += dj[i], m += dk[i];
            if (r >= 0 && c >= 0 && m >= 0 && r < rows && c < columns && m < moments && distances[m][r][c] == -1 && matrix[m][r][c] != '#' && matrix[m][r][c] != '!')
            {
                distances[m][r][c] = distances[current.moment][current.row][current.column] + 1;
                q.push({r, c, m});
            }
        }
    }
    return -1;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> columns >> rows >> moments;
        for (int k = 0; k < moments; k++)
        {
            for (int i = 0; i < rows; i++)
            {
                cin >> line;
                for (int j = 0; j < columns; j++)
                {
                    matrix[k][i][j] = line[j];
                    distances[k][i][j] = -1;
                    if (matrix[k][i][j] == 'X')
                        start = {i, j, k};
                }
            }
        }
        int steps = bfs(start);
        if (steps != -1)
            cout << steps << endl;
        else
            cout << "Hostage is death, destroy the bunker" << endl;
    }
    return 0;
}