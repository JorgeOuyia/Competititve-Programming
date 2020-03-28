#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair_Hash
{
    template <class T1, class T2>
    size_t operator()(pair<T1, T2> const &pair) const
    {
        size_t h1 = hash<T1>()(pair.first);
        size_t h2 = hash<T2>()(pair.second);

        return h1 ^ h2;
    }
};

int rows, columns, aux;
char matrix[55][55];
bool visited[55][55];
int di[4] = {-1, 0, 1, 0}, dj[4] = {0, 1, 0, -1};
unordered_map<pair<int, int>, int, Pair_Hash> components;
unordered_map<int, int> res;
vector<int> dices;
string line;

void dfs(pair<int, int> u, int comp)
{
    visited[u.first][u.second] = true;
    components[u] = comp;

    for (int i = 0; i < 4; i++)
    {
        int r = u.first, c = u.second;

        r += di[i], c += dj[i];
        if (r >= 0 && c >= 0 && r < rows && c < columns && matrix[r][c] != '.' && !visited[r][c])
            dfs({r, c}, comp);
    }
}

void countThrow(pair<int, int> u)
{
    visited[u.first][u.second] = true;

    for (int i = 0; i < 4; i++)
    {
        int r = u.first, c = u.second;

        r += di[i], c += dj[i];
        if (r >= 0 && c >= 0 && r < rows && c < columns && !visited[r][c] && matrix[r][c] == 'X')
            countThrow({r, c});
    }
}

int main()
{
    int scenario = 1;
    while (cin >> columns >> rows && (rows != 0 || columns != 0))
    {
        components.clear();
        res.clear();
        dices.clear();
        aux = 1;
        for (int i = 0; i < rows; i++)
        {
            cin >> line;
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                visited[i][j] = false;
            }
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (matrix[i][j] != '.' && !visited[i][j])
                    dfs({i, j}, aux++);
            }
        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                visited[i][j] = false;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (matrix[i][j] == 'X' && !visited[i][j])
                {
                    countThrow({i, j});
                    res[components[{i, j}]]++;
                }
            }
        }
        cout << "Throw " << scenario << endl;
        for (auto it = res.begin(); it != res.end(); ++it)
            dices.push_back(it->second);
        sort(dices.begin(), dices.end());
        for (int i = 0; i < dices.size(); i++)
        {
            if (i == 0)
                cout << dices[i];
            else
                cout << " " << dices[i];
        }
        cout << endl;
        cout << endl;
        scenario++;
    }
    return 0;
}