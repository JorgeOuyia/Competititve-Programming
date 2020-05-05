#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

struct Point2D
{
    int row, column;
};

int steps, minSteps;
char solution[5][5] = { {'1', '1', '1', '1', '1'},
                       {'0', '1', '1', '1', '1'},
                       {'0', '0', ' ', '1', '1'},
                       {'0', '0', '0', '0', '1'},
                       {'0', '0', '0', '0', '0'} };
char matrix[5][5];
string line;
Point2D start;
int di[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int dj[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

bool isSolution()
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] != solution[i][j])
                return false;
    return true;
}

void dfs(int row, int column, int steps)
{
    if (steps >= 11 || steps >= minSteps)
        return;
    if (isSolution())
    {
        minSteps = min(minSteps, steps);
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        int r = row + di[i], c = column + dj[i];

        if (r >= 0 && c >= 0 && r < 5 && c < 5)
        {
            swap(matrix[row][column], matrix[r][c]);
            dfs(r, c, steps + 1);
            swap(matrix[row][column], matrix[r][c]);
        }
    }
}

int main()
{
    int t;
    cin >> t;
    cin.ignore();
    while (t--)
    {
        minSteps = INF;
        for (int i = 0; i < 5; i++)
        {
            getline(cin, line);
            for (int j = 0; j < 5; j++)
            {
                matrix[i][j] = line[j];
                if (matrix[i][j] == ' ')
                    start = { i, j };
            }
        }
        dfs(start.row, start.column, 0);
        if (minSteps > 11)
            cout << "Unsolvable in less than 11 move(s)." << endl;
        else
            cout << "Solvable in " << minSteps << " move(s)." << endl;
    }
    return 0;
}