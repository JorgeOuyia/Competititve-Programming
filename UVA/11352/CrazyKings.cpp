#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

struct Point2D
{
    int row, column;

    bool operator==(const Point2D &other) const
    {
        return other.row == row && other.column == column;
    }
};

int rows, columns;
string line;
Point2D source, destiny;
char matrix[105][105];
int distances[105][105];
int diKnight[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int djKnight[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int diKing[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int djKing[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void calculateForbiddenPositions()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (matrix[i][j] == 'Z')
            {
                for (int k = 0; k < 8; k++)
                {
                    int r = i + diKnight[k], c = j + djKnight[k];

                    if (r >= 0 && c >= 0 && r < rows && c < columns && matrix[r][c] == '.')
                        matrix[r][c] = 'G';
                }
            }
        }
    }
}

int bfs(Point2D start, Point2D target)
{
    distances[start.row][start.column] = 0;
    queue<Point2D> q;
    q.push(start);
    Point2D current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current == target)
            return distances[current.row][current.column];

        for (int i = 0; i < 8; i++)
        {
            int r = current.row + diKing[i], c = current.column + djKing[i];

            if (r >= 0 && c >= 0 && r < rows && c < columns && matrix[r][c] != 'Z' && matrix[r][c] != 'G' && distances[r][c] > distances[current.row][current.column] + 1)
                distances[r][c] = distances[current.row][current.column] + 1, q.push({r, c});
        }
    }
    return -1;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> rows >> columns;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                distances[i][j] = INF;
        for (int i = 0; i < rows; i++)
        {
            cin >> line;
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                if (matrix[i][j] == 'A')
                    source = {i, j};
                if (matrix[i][j] == 'B')
                    destiny = {i, j};
            }
        }
        calculateForbiddenPositions();
        int dist = bfs(source, destiny);
        if (dist != -1)
            cout << "Minimal possible length of a trip is " << dist << endl;
        else
            cout << "King Peter, you can't go now!" << endl;
    }
    return 0;
}