#include <iostream>
#include <string>
#include <vector>

using namespace std;

int t, n, cont, ship;
int di[4] = { -1, 0, 1, 0 }, dj[4] = { 0, 1, 0, -1 };
char matrix[105][105];
bool visited[105][105];
string line;

void dfs(pair<int, int> u)
{
    visited[u.first][u.second] = true;
    if (matrix[u.first][u.second] == 'x')
        ship++;

    for (int i = 0; i < 4; i++)
    {
        int row = u.first, column = u.second;
        row += di[i], column += dj[i];

        if (row >= 0 && row < n && column >= 0 && column < n && matrix[row][column] != '.' && !visited[row][column])
        {
            dfs({ row, column });
        }
    }
}

int main()
{
    cin >> t;
    int scenario = 1;
    while (t--)
    {
        cin >> n;
        cont = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> line;
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = line[j];
                visited[i][j] = false;
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!visited[i][j] && matrix[i][j] != '.')
                {
                    ship = 0;
                    dfs({ i, j });
                    if (ship > 0)
                        cont++;
                }
            }
        }
        cout << "Case " << scenario << ": " << cont << endl;
        scenario++;
    }
    return 0;
}