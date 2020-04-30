#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
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
unordered_map<char, int> values;
char matrix[1000][1000];
bool visited[1000][1000];
int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};
vector<Pair> result;

void bfs(int row, int column, char character)
{
    visited[row][column] = true;
    queue<Point> q;
    q.push({row, column});
    Point current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        for (int i = 0; i < 4; i++)
        {
            int r = current.row + di[i], c = current.column + dj[i];

            if (r >= 0 && c >= 0 && r < rows && c < columns && !visited[r][c] && matrix[r][c] == character)
            {
                visited[r][c] = true;
                q.push({r, c});
            }
        }
    }
}

int main()
{
    int world = 1;
    int t;
    cin >> t;
    while (t--)
    {
        cin >> rows >> columns;
        values.clear();
        result.clear();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                visited[i][j] = false;
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
                if (!visited[i][j])
                    values[matrix[i][j]]++, bfs(i, j, matrix[i][j]);
            }
        }
        for (auto it = values.begin(); it != values.end(); ++it)
            result.push_back({it->first, it->second});
        sort(result.begin(), result.end());
        cout << "World #" << world++ << endl;
        for (Pair p : result)
        {
            cout << p.character << ": " << p.freq << endl;
        }
    }
    return 0;
}