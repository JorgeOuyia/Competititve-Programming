#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

struct Point
{
    int row, column;
};

int sz;
string line;
int matrix[30][30];
bool visited[30][30];
int di[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dj[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int bfs(int row, int column)
{
    visited[row][column] = true;
    queue<Point> q;
    q.push({row, column});
    Point current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (int i = 0; i < 8; i++)
        {
            int r = current.row + di[i], c = current.column + dj[i];

            if (r >= 0 && c >= 0 && r < sz && c < sz && !visited[r][c] && matrix[r][c])
            {
                visited[r][c] = true;
                q.push({r, c});
            }
        }
    }
    return 1;
}

int main()
{
    int scenario = 1;
    while (cin >> sz)
    {
        for (int i = 0; i < sz; i++)
        {
            cin >> line;
            for (int j = 0; j < sz; j++)
            {
                matrix[i][j] = line[j] - '0';
                visited[i][j] = false;
            }
        }
        int res = 0;
        for (int i = 0; i < sz; i++)
        {
            for (int j = 0; j < sz; j++)
            {
                if (!visited[i][j] && matrix[i][j])
                {
                    res += bfs(i, j);
                }
            }
        }
        cout << "Image number " << scenario++ << " contains " << res << " war eagles." << endl;
    }
    return 0;
}