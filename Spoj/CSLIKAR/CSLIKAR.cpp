#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int rows, columns;
int fire[55][55];
int painter[55][55];
char matrix[55][55];
int di[4] = { -1, 0, 1, 0 };
int dj[4] = { 0, 1, 0, -1 };
string line;
queue<pair<int, int>> fireBoxes;
pair<int, int> start, last;

void floodFillFire()
{
    pair<int, int> current;
    while (!fireBoxes.empty())
    {
        current = fireBoxes.front(), fireBoxes.pop();

        for (int i = 0; i < 4; i++)
        {
            int r = current.first, c = current.second;

            r += di[i], c += dj[i];
            if (r >= 0 && c >= 0 && r < rows && c < columns && matrix[r][c] != 'X' && matrix[r][c] != 'D' && fire[r][c] == INF)
            {
                fire[r][c] = fire[current.first][current.second] + 1;
                fireBoxes.push({ r, c });
            }
        }
    }
}

void floodFillPainter(pair<int, int> start)
{
    painter[start.first][start.second] = 0;
    queue<pair<int, int>> q;
    q.push(start);
    pair<int, int> current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (int i = 0; i < 4; i++)
        {
            int r = current.first, c = current.second;

            r += di[i], c += dj[i];
            if (r >= 0 && c >= 0 && r < rows && c < columns && matrix[r][c] != 'X' && matrix[r][c] != 'D' && matrix[r][c] != '*' && painter[r][c] == INF && painter[current.first][current.second] + 1 < fire[r][c])
            {
                painter[r][c] = painter[current.first][current.second] + 1;
                q.push({ r, c });
            }
        }
    }
}

int main()
{
    while (cin >> rows >> columns)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                fire[i][j] = INF, painter[i][j] = INF;
        for (int i = 0; i < rows; i++)
        {
            cin >> line;
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                if (matrix[i][j] == 'S')
                    start = { i, j }, painter[i][j] = 0;
                else if (matrix[i][j] == 'D')
                    last = { i, j };
                else if (matrix[i][j] == '*')
                    fireBoxes.push({ i, j }), fire[i][j] = 0;
            }
        }
        floodFillFire(), floodFillPainter(start);
        int res = INF;
        for (int i = 0; i < 4; i++)
        {
            int r = last.first, c = last.second;

            r += di[i], c += dj[i];
            if (r >= 0 && c >= 0 && r < rows && c < columns)
            {
                if (painter[r][c] < fire[r][c])
                    res = min(res, painter[r][c]);
            }
        }
        if (res != INF)
            cout << res + 1 << endl;
        else
            cout << "KAKTUS" << endl;
    }
    return 0;
}