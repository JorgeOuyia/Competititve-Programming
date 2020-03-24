#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int rows, columns, r, c, maxDist, dist;
string line;
char matrix[25][25];
bool visited[25][25];
char land;
int di[4] = { -1, 0, 1, 0 }, dj[4] = { 0, 1, 0, -1 };

void floodFill(pair<int, int> u)
{
    visited[u.first][u.second] = true;
    dist++;

    for (int i = 0; i < 4; i++)
    {
        int row = u.first, column = u.second;
        row += di[i];
        column += dj[i];

        if (column == -1)
            column = columns - 1;
        else if (column == columns)
            column = 0;

        if (row >= 0 && column >= 0 && row < rows && column < columns && matrix[row][column] == land && !visited[row][column])
        {
            floodFill({ row, column });
        }
    }
}

int main()
{
    while (cin >> rows >> columns)
    {
        cin.ignore();
        maxDist = 0;
        for (int i = 0; i < rows; i++)
        {
            getline(cin, line);
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                visited[i][j] = false;
            }
        }
        cin >> r >> c;
        land = matrix[r][c];
        floodFill({ r, c });

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (!visited[i][j] && matrix[i][j] == land)
                {
                    dist = 0;
                    floodFill({ i, j });
                    maxDist = max(maxDist, dist);
                }
            }
        }
        cout << maxDist << endl;
    }
    return 0;
}