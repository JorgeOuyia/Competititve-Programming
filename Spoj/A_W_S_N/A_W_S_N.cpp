#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
    int node, dist;

    bool operator<(const Edge& other) const
    {
        return other.dist < dist;
    }
};

int rows, columns, minDist, beginning, ending;
char matrix[105][105];
vector<Edge> allGraph[105 * 105];
vector<Edge> subGraph[105 * 105];
int distances[105 * 105];
bool visited[105 * 105];
int di[4] = {-1, 0, 1, 0}, dj[4] = {0, 1, 0, -1};
vector<int> mustPass;
vector<int> path;
map<pair<int, int>, int> trad;
string line;

void dijkstra(int start)
{
    for (int i = 1; i <= rows * columns; i++)
        distances[i] = INF;
    distances[start] = 0;
    priority_queue<Edge> pq;
    pq.push({start, 0});
    Edge current;
    while(!pq.empty())
    {
        current = pq.top();
        pq.pop();

        if (distances[current.node] >= current.dist)
        {
            for (Edge to : allGraph[current.node])
            {
                int peso = to.dist + current.dist;

                if (peso < distances[to.node])
                {
                    pq.push({to.node, peso});
                    distances[to.node] = peso;
                }
            }
        }
    }
}

void dfs(int u, int end, int dist)
{
    if (dist > minDist)
        return;
    if (path.size() == mustPass.size() - 1 && u == end)
    {
        minDist = min(minDist, dist);
    }
    visited[u] = true;
    for (Edge v : subGraph[u])
    {
        if (!visited[v.node])
        {
            path.push_back(v.node);
            dist += v.dist;
            dfs(v.node, end, dist);
            path.erase(find(path.begin(), path.end(), v.node));
            dist -= v.dist;
        }
    }
    visited[u] = false;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> rows >> columns;

        // Clear zone
        mustPass.clear();
        trad.clear();
        minDist = INF;
        for (int i = 1; i <= rows * columns; i++)
        {
            distances[i] = INF;
            visited[i] = false;
            allGraph[i].clear();
            subGraph[i].clear();
        }

        // Reading zone
        int aux = 1;
        for (int i = 0; i < rows; i++)
        {
            cin >> line;
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                trad[{i, j}] = aux++;
                if (matrix[i][j] == 'T' || matrix[i][j] == 'W' || matrix[i][j] == 'C')
                    mustPass.push_back(trad[{i, j}]);
                if (matrix[i][j] == 'T')
                    beginning = trad[{i, j}];
                if (matrix[i][j] == 'W')
                    ending = trad[{i, j}];

            }
        }

        // Pass graph to adjacency list
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                for (int l = 0; l < 4; l++)
                {
                    int row = i;
                    int column = j;
                    row += di[l];
                    column += dj[l];

                    if (row >= 0 && column >= 0 && row < rows && column < columns && matrix[row][column] != '#')
                    {
                        allGraph[trad[{i, j}]].push_back({trad[{row, column}], 1});
                    }
                }
            }
        }
        bool flag = true;
        for (int i = 0; i < mustPass.size() && flag; i++)
        {
            dijkstra(mustPass[i]);
            for (int j = i + 1; j < mustPass.size() && flag; j++)
            {
                if (distances[mustPass[j]] == INF)
                    flag = false;
                subGraph[mustPass[i]].push_back({mustPass[j], distances[mustPass[j]]});
                subGraph[mustPass[j]].push_back({mustPass[i], distances[mustPass[j]]});
            }
        }
        if (!flag)
        {
            cout << "Mission Failed!" << endl;
            continue;
        }
        dfs(beginning, ending, 0);
        cout << minDist << endl;
    }
    return 0;
}