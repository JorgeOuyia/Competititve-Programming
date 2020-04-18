#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;

int n, r, c, cont, conj, flag;
int matrix[105][105];
bool visited[105][105];
string line;

void dfs(int row, int column, int ancestor)
{
    if (row >= n || column >= n || row < 0 || column < 0 || visited[row][column] || matrix[row][column] != ancestor)
        return;
    visited[row][column] = true;
    cont++;
    dfs(row - 1, column, ancestor);
    dfs(row, column + 1, ancestor);
    dfs(row + 1, column, ancestor);
    dfs(row, column - 1, ancestor);
}

int main()
{
    while (cin >> n && n != 0)
    {
        flag = true;
        cont = 0, conj = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                matrix[i][j] = n, visited[i][j] = false;
        cin.ignore();
        for (int i = 0; i < n - 1; i++)
        {
            getline(cin, line);
            istringstream ss(line);
            while (ss >> r >> c)
                matrix[r - 1][c - 1] = i;
        }
        for (int i = 0; i < n && flag; i++)
        {
            for (int j = 0; j < n && flag; j++)
            {
                if (!visited[i][j])
                    conj++, cont = 0, dfs(i, j, matrix[i][j]);
                if (cont != n || conj > n)
                    flag = false;
            }
        }
        if (!flag)
            cout << "wrong" << endl;
        else
            cout << "good" << endl;
    }
    return 0;
}