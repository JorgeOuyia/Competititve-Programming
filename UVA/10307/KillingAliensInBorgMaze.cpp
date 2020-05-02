#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
    int from, to, dist;

    bool operator<(const Edge &other) const
    {
        return other.dist < dist;
    }
};

struct Point2D
{
    int row, column;

    bool operator==(const Point2D &other) const
    {
        return other.row == row && other.column == column;
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

int rows, columns, mstSum;
string line;
int distances[55][55];
char matrix[55][55];
int parents[55 * 55];
int sz[55 * 55];
int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};
priority_queue<Edge> graph;
vector<Point2D> mustPass;
unordered_map<Point2D, int, Point2D_Hash> hashMap;
Point2D start;

void bfs(Point2D start)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            distances[i][j] = INF;
    distances[start.row][start.column] = 0;
    queue<Point2D> q;
    q.push(start);
    Point2D current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (int i = 0; i < 4; i++)
        {
            int r = current.row + di[i], c = current.column + dj[i];

            if (r >= 0 && c >= 0 && r < rows && c < columns && matrix[r][c] != '#' && distances[r][c] > distances[current.row][current.column] + 1)
            {
                distances[r][c] = distances[current.row][current.column] + 1;
                q.push({r, c});
            }
        }
    }
}

int find(int x)
{
    if (parents[x] == x)
        return parents[x];
    return parents[x] = find(parents[x]);
}

void connect(int x, int y, int cost)
{
    x = find(x);
    y = find(y);

    if (x != y)
    {
        if (sz[x] >= sz[y])
            parents[y] = x, sz[x] += sz[y];
        else
            parents[x] = y, sz[y] += sz[x];
        mstSum += cost;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> columns >> rows;
        mustPass.clear();
        hashMap.clear();
        int id = 1;
        mstSum = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                hashMap[{i, j}] = id++;
        for (int i = 0; i <= rows * columns; i++)
            parents[i] = i, sz[i] = 1;
        cin.ignore();
        for (int i = 0; i < rows; i++)
        {
            getline(cin, line);
            if (line.length() < columns)
                while (line.length() < columns)
                    line.push_back(' ');
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                if (matrix[i][j] == 'S' || matrix[i][j] == 'A')
                    mustPass.push_back({i, j});
            }
        }
        for (int i = 0; i < mustPass.size(); i++)
        {
            Point2D from = mustPass[i];
            bfs(from);
            for (int j = i + 1; j < mustPass.size(); j++)
            {
                Point2D to = mustPass[j];
                graph.push({hashMap[from], hashMap[to], distances[to.row][to.column]});
                graph.push({hashMap[to], hashMap[from], distances[to.row][to.column]});
            }
        }
        Edge current;
        while (!graph.empty())
        {
            current = graph.top(), graph.pop();
            int from = current.from;
            int to = current.to;
            int cost = current.dist;
            connect(from, to, cost);
        }
        cout << mstSum << endl;
    }
    return 0;
}