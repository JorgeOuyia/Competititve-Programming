#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <map>

#define INF 0x3f3f3f3f

using namespace std;

struct Pair_Hash
{
    template<class T1, class T2>
    size_t operator()(pair<T1, T2> const& pair) const
    {
        size_t h1 = hash<T1>()(pair.first);
        size_t h2 = hash<T2>()(pair.second);

        return h1 ^ h2;
    }
};

struct Edge
{
    int node, dist;

    bool operator<(const Edge& other) const
    {
        return other.dist < dist;
    }
};

int columns, rows, column, row;
char matrix[105][105];
vector<Edge> graph[105 * 105];
vector<int> subGraph[105 * 105];
int distances[105 * 105];
int inDegree[105 * 105];
int dp[105 * 105];
unordered_map<pair<int, int>, int, Pair_Hash> hashMap;
unordered_map<int, unordered_set<int>> ancestors;
vector<int> topoOrder;
map<int, int> allNodes;
string line;
int di[2] = { 1, 0};
int dj[2] = { 0, 1 };

void dijkstra(int start)
{
    distances[start] = 0;
    priority_queue<Edge> pq;
    pq.push({ start, 0 });
    Edge current;
    while (!pq.empty())
    {
        current = pq.top(), pq.pop();

        if (distances[current.node] >= current.dist)
        {
            for (Edge to : graph[current.node])
            {
                int peso = current.dist + to.dist;
                if (peso < distances[to.node])
                {
                    distances[to.node] = peso;
                    pq.push({ to.node, peso });
                    if (ancestors.find(to.node) != ancestors.end())
                        ancestors[to.node].clear();
                    ancestors[to.node].insert(current.node);
                }
                else if (peso == distances[to.node])
                    ancestors[to.node].insert(current.node);
            }
        }
    }
}

void topoSort()
{
    queue<int> q;
    for (auto it = allNodes.begin(); it != allNodes.end(); ++it)
        if (it->second == 0)
            q.push(it->first);
    int current;
    while (!q.empty())
    {
        current = q.front(), q.pop();
        topoOrder.push_back(current);

        for (int v : subGraph[current])
        {
            allNodes[v]--;

            if (!allNodes[v])
                q.push(v);
        }
    }
    reverse(topoOrder.begin(), topoOrder.end());
}

int countPaths(int source, int destination)
{
    dp[destination] = 1;

    for (int u : topoOrder)
    {
        for (int v : subGraph[u])
            dp[u] += dp[v];
    }
    return dp[source];
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int id = 1;
        cin >> rows >> columns;
        ancestors.clear();
        allNodes.clear();
        topoOrder.clear();
        for (int i = 1; i <= rows; i++)
            for (int j = 1; j <= columns; j++)
                matrix[i][j] = '.', hashMap[{i, j}] = id++;
        for (int i = 1; i <= rows * columns; i++)
            graph[i].clear(), subGraph[i].clear(), distances[i] = INF, dp[i] = 0;
        cin.ignore();
        for (int i = 0; i < rows; i++)
        {
            getline(cin, line);
            istringstream ss(line);
            ss >> row;
            while (ss >> column)
            {
                matrix[row][column] = '#';
            }
        }
        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= columns; j++)
            {
                for (int l = 0; l < 2; l++)
                {
                    int r = i, c = j;

                    r += di[l], c += dj[l];

                    if (matrix[r][c] != '#' && r >= 1 && c >= 1 && r <= rows && c <= columns && matrix[i][j] != '#')
                    {
                        graph[hashMap[{i, j}]].push_back({ hashMap[{r, c}], 1 });
                    }
                }
            }
        }
        dijkstra(1);
        for (auto it = ancestors.begin(); it != ancestors.end(); ++it)
        {
            for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
            {
                subGraph[*jt].push_back(it->first);
                allNodes[*jt];
                allNodes[it->first]++;
            }
        }
        topoSort();
        cout << countPaths(1, rows * columns) << endl;
        if (t != 0)
            cout << endl;
    }
    return 0;
}