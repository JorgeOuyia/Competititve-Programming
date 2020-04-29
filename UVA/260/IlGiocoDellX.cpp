#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int sz;
string line;
char matrix[205][205];
bool visited[205][205];
int di[6] = { -1, -1, 0, 0, 1, 1 };
int dj[6] = { -1, 0, -1, 1, 0, 1 };

struct Point
{
    int row, column;
};

bool bfs(int row, int column, char character)
{
    visited[row][column] = true;
    queue<Point> q;
    q.push({ row, column });
    Point current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current.column == sz - 1)
            return true;

        for (int i = 0; i < 6; i++)
        {
            int r = current.row + di[i], c = current.column + dj[i];
            if (r >= 0 && c >= 0 && r < sz && c < sz && !visited[r][c] && matrix[r][c] == character)
            {
                visited[r][c] = true;
                q.push({ r, c });
            }
        }

    }
    return false;
}

int main()
{
    int scenario = 1;
    while (cin >> sz && sz != 0)
    {
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                visited[i][j] = false;
        for (int i = 0; i < sz; i++)
        {
            cin >> line;
            for (int j = 0; j < sz; j++)
                matrix[i][j] = line[j];
        }
        cout << scenario++ << " ";
        int printed = false;
        for (int i = 0; i < sz; i++)
        {
            if (!visited[i][0] && matrix[i][0] == 'w')
            {
                if (bfs(i, 0, matrix[i][0]))
                {
                    cout << "W" << endl;
                    printed = true;
                    break;
                }
            }
        }
        if (!printed)
            cout << "B" << endl;
    }
    return 0;
}