#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

int t, rows, columns, row, column, cont;
char matrix[105][105];
bool visited[105][105];
int di[8] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dj[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
string line;

void floodFill(pair<int, int> u)
{
    visited[u.first][u.second] = true;
    cont++;

    for (int i = 0; i < 8; i++)
    {
        int r = u.first, c = u.second;
        r += di[i], c += dj[i];

        if (r >= 0 && c >= 0 && r < rows && c < columns && !visited[r][c] && matrix[r][c] == 'W')
            floodFill({ r, c });
    }
}

int main()
{
    cin >> t;
    getline(cin, line);
    getline(cin, line);
    int first = true;
    while (t--)
    {
        for (int i = 0; i < 102; i++)
            for (int j = 0; j < 102; j++)
                visited[i][j] = false;
        rows = 0;
        while (getline(cin, line) && line != "")
        {
            if (line[0] == 'W' || line[0] == 'L')
            {
                columns = line.length();
                for (int j = 0; j < line.length(); j++)
                    matrix[rows][j] = line[j];
                rows++;
            }
            else
            {
                cont = 0;
                istringstream ss(line);
                ss >> row;
                ss >> column;
                row--, column--;
                if (matrix[row][column] == 'L')
                {
                    cout << 0 << endl;
                    continue;
                }
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < columns; j++)
                        visited[i][j] = false;
                floodFill({ row, column });
                cout << cont << endl;
            }
        }
        if (t != 0)
            cout << endl;
    }
    return 0;
}