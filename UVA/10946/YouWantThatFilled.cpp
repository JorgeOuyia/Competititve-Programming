#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
    int row, column;
};

struct Pair
{
    char character;
    int freq;

    bool operator<(const Pair &other) const
    {
        if (freq == other.freq)
            return character < other.character;
        return freq > other.freq;
    }
};

int rows, columns;
string line;
char matrix[55][55];
vector<Pair> result;
int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};

int bfs(int row, int column, char character)
{
    int res = 0;
    matrix[row][column] = '.';
    queue<Point> q;
    q.push({row, column});
    Point current;
    while (!q.empty())
    {
        current = q.front(), q.pop();
        res++;

        for (int i = 0; i < 4; i++)
        {
            int r = current.row + di[i], c = current.column + dj[i];

            if (r >= 0 && c >= 0 && r < rows && c < columns && matrix[r][c] == character)
            {
                matrix[r][c] = '.';
                q.push({r, c});
            }
        }
    }
    return res;
}

int main()
{
    int scenario = 1;
    while (cin >> rows >> columns && (rows != 0 || columns != 0))
    {
        result.clear();
        for (int i = 0; i < rows; i++)
        {
            cin >> line;
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
            }
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (matrix[i][j] != '.')
                    result.push_back({matrix[i][j], bfs(i, j, matrix[i][j])});
            }
        }
        sort(result.begin(), result.end());
        cout << "Problem " << scenario++ << ":" << endl;
        for (Pair p : result)
            cout << p.character << " " << p.freq << endl;
    }
    return 0;
}