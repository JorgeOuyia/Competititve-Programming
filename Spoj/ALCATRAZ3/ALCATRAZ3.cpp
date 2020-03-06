#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Point
{
    int row, column;
};

int rows, columns, minDist, row, column, flag;
Point pos;
vector<pair<int, int>> path;
char matrix[105][105];
bool visited[105][105];
map<pair<int, int>, bool> finals;

int calculateDistance(Point from, Point to)
{
    return abs(from.row - to.row) + abs(from.column - to.column);
}

void dfs(int row, int column, int dist)
{
    visited[row][column] = true;
    if (finals[{row, column}] && dist >= minDist - 1)
    {
        flag = 1;
    }
    int r = row, c = column;
    for (int i = 0; i < 4; i++)
    {
        r = row, c = column;
        if (i == 0)
            r -= 1;
        else if (i == 1)
            c += 1;
        else if (i == 2)
            r += 1;
        else
            c -= 1;

        if (!visited[r][c] && matrix[r][c] == '.' && r < rows && c < columns)
        {
            dfs(r, c, dist + 1);
        }
    }
    visited[row][column] = false;
}

int main()
{
    while (cin >> rows >> columns)
    {
        flag = 0;
        path.clear();
        finals.clear();
        cin >> minDist;
        cin >> row >> column;
        row--, column--;
        pos.row = row;
        pos.column = column;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                visited[i][j] = false;
                cin >> matrix[i][j];
            }
        }
        int r = row, c = column;
        for (int i = 0; i < 4; i++)
        {
            r = row, c = column;
            if (i == 0)
                r -= 1;
            else if (i == 1)
                c += 1;
            else if (i == 2)
                r += 1;
            else
                c -= 1;

            if (matrix[r][c] == '.' && r < rows && c < columns)
            {
                finals[{r, c}] = 1;
            }
        }
        dfs(row, column, 0);
        if (flag)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}