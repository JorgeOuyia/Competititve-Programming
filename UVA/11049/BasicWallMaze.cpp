#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#define INF 0x3f3f3f3f

using namespace std;

struct Point2D
{
    int row, column;

    bool operator==(const Point2D &other) const
    {
        return other.row == row && other.column == column;
    }

    bool operator!=(const Point2D &other) const
    {
        return other.row != row || other.column != column;
    }
};

struct Point2D_Hash
{
    size_t operator()(const Point2D &point) const
    {
        size_t h1 = hash<int>()(point.row);
        size_t h2 = hash<int>()(point.column);

        return h1 ^ h2;
    }
};

Point2D source, target, start, ending;
unordered_map<Point2D, unordered_set<Point2D, Point2D_Hash>, Point2D_Hash> forbiddenMovements;
Point2D parents[6][6];
int distances[6][6];
int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};

bool bfs(Point2D source, Point2D destiny)
{
    distances[source.row][source.column] = 0;
    queue<Point2D> q;
    q.push(source);
    Point2D current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current == destiny)
            return true;

        for (int i = 0; i < 4; i++)
        {
            int r = current.row + di[i], c = current.column + dj[i];

            if (r >= 0 && c >= 0 && r < 6 && c < 6 && forbiddenMovements[current].find({r, c}) == forbiddenMovements[current].end() && distances[r][c] > distances[current.row][current.column] + 1)
            {
                distances[r][c] = distances[current.row][current.column] + 1;
                parents[r][c] = {current.row, current.column};
                q.push({r, c});
            }
        }
    }
    return false;
}

int main()
{
    while (cin >> source.column >> source.row && (source.row || source.column))
    {
        forbiddenMovements.clear();
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++)
                parents[i][j] = {i, j}, distances[i][j] = INF;
        cin >> target.column >> target.row;
        source.row--, source.column--, target.row--, target.column--;
        for (int i = 0; i < 3; i++)
        {
            cin >> start.column >> start.row >> ending.column >> ending.row;
            if (start.row == ending.row)
            {
                if (start.row != 0 && start.row != 6)
                {
                    int column = min(start.column, ending.column);
                    while (column != max(ending.column, start.column))
                    {
                        int currentRow = start.row - 1;
                        int nextRow = start.row;
                        forbiddenMovements[{currentRow, column}].insert({nextRow, column});
                        forbiddenMovements[{nextRow, column}].insert({currentRow, column});
                        column++;
                    }
                }
            }
            else
            {
                if (start.column != 0 && start.column != 6)
                {
                    int row = min(start.row, ending.row);
                    while (row != max(ending.row, start.row))
                    {
                        int currentColumn = start.column - 1;
                        int nextColumn = start.column;
                        forbiddenMovements[{row, currentColumn}].insert({row, nextColumn});
                        forbiddenMovements[{row, nextColumn}].insert({row, currentColumn});
                        row++;
                    }
                }
            }
        }
        if (bfs(source, target))
        {
            vector<Point2D> path;
            Point2D u = target;
            while (u != parents[u.row][u.column])
            {
                path.push_back(u);
                u = parents[u.row][u.column];
            }
            path.push_back(source);
            reverse(path.begin(), path.end());
            string directions;
            for (int i = 1; i < path.size(); i++)
            {
                Point2D current = path[i - 1];
                Point2D next = path[i];
                if (current.row == next.row)
                {
                    if (current.column < next.column)
                        directions.push_back('E');
                    else
                        directions.push_back('W');
                }
                else
                {
                    if (next.row > current.row)
                        directions.push_back('S');
                    else
                        directions.push_back('N');
                }
            }
            cout << directions << endl;
        }
        else
        {
            cout << "" << endl;
        }
    }
    return 0;
}