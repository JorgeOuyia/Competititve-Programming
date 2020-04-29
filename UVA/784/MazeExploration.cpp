#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

struct Point
{
    int row, column;
};

char matrix[85][85];
string line;
Point start;
int di[4] = { -1, 0, 1, 0 };
int dj[4] = { 0, 1, 0, -1 };

void bfs(int row, int column)
{
    matrix[row][column] = '#';
    queue<Point> q;
    q.push({ row, column });
    Point current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (int i = 0; i < 4; i++)
        {
            int r = current.row + di[i], c = current.column + dj[i];

            if (r >= 0 && c >= 0 && matrix[r][c] == ' ')
            {
                matrix[r][c] = '#';
                q.push({ r, c });
            }
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
        for (int i = 0; i < 85; i++)
            for (int j = 0; j < 85; j++)
                matrix[i][j] = '@';
        int rows = 0;
        start = { -1, -1 };
        while (getline(cin, line))
        {
            int fullUnderscore = true;
            for (int i = 0; i < line.length(); i++)
                if (line[i] != '_')
                    fullUnderscore = false;
            if (fullUnderscore)
                break;
            for (int i = 0; i < line.length(); i++)
            {
                matrix[rows][i] = line[i];
                if (matrix[rows][i] == '*')
                    start = { rows, i };
            }
            rows++;
        }
        if (start.row != -1 && start.column != -1)
            bfs(start.row, start.column);
        for (int i = 0; i < rows; i++)
        {
            int col = 0;
            while (matrix[i][col] != '@' && col < 85)
                cout << matrix[i][col++];
            cout << endl;
        }
        cout << line << endl;

    }
    return 0;
}