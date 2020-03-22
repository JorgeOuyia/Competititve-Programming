#include <iostream>
#include <string>

using namespace std;

int rows, columns, horizontal, vertical, n, x, y;
bool visited[105][105];
char matrix[105][105];
int frec[105][105];

void dfs(pair<int, int> u)
{
    visited[u.first][u.second] = true;

    for (int i = 0; i < 8; i++)
    {
        int row = u.first, column = u.second;

        if (i == 0)
            row -= vertical, column += horizontal;
        else if (i == 1)
            row -= vertical, column -= horizontal;
        else if (i == 2)
            row += vertical, column += horizontal;
        else if (i == 3)
            row += vertical, column -= horizontal;
        else if (i == 4)
            row -= horizontal, column += vertical;
        else if (i == 5)
            row -= horizontal, column -= vertical;
        else if (i == 6)
            row += horizontal, column += vertical;
        else
            row += horizontal, column -= vertical;

        if (row >= 0 && column >= 0 && row < rows && column < columns && matrix[row][column] != '#')
        {
            frec[row][column]++;
            if (!visited[row][column])
                dfs({row, column});
        }
    }
}

int main()
{
    int t, scenario = 1;
    cin >> t;
    while (t--)
    {
        cin >> rows >> columns >> horizontal >> vertical;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                visited[i][j] = false;
                matrix[i][j] = '.';
                frec[i][j] = 0;
            }
        }
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            matrix[x][y] = '#';
        }
        dfs({0, 0});
        int odd, even;
        odd = 0, even = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (horizontal == vertical || horizontal == 0 || vertical == 0)
                    frec[i][j] /= 2;
                if (frec[i][j] != 0 || (!i && !j))
                {
                    if (frec[i][j] % 2 == 0)
                        even++;
                    else
                        odd++;
                }
            }
        }
        cout << "Case " << scenario << ": " << even << " " << odd << endl;
        scenario++;
    }
    return 0;
}