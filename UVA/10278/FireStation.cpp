#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

int graph[505][505];
int maxShortestLength[505];
vector<int> stations;
int nFireStations, nIntersections;
string line;

void floydWarshall()
{
    for (int k = 1; k <= nIntersections; k++)
    {
        for (int i = 1; i <= nIntersections; i++)
        {
            for (int j = 1; j <= nIntersections; j++)
            {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        stations.clear();
        cin >> nFireStations >> nIntersections;
        for (int i = 1; i <= nIntersections; i++)
        {
            for (int j = 1; j <= nIntersections; j++)
            {
                if (i != j)
                    graph[i][j] = INF;
                else
                    graph[i][j] = 0;
            }
        }
        for (int i = 1; i <= nIntersections; i++)
            maxShortestLength[i] = INF;
        for (int i = 0; i < nFireStations; i++)
        {
            int n;
            cin >> n;
            stations.push_back(n);
        }
        cin.ignore();
        while (getline(cin, line) && line != "")
        {
            istringstream ss(line);
            int from, to, dist;
            ss >> from >> to >> dist;
            graph[from][to] = dist;
            graph[to][from] = dist;
        }

        floydWarshall();

        int maxLength = -1;
        for (int i = 1; i <= nIntersections; i++)
        {
            maxShortestLength[i] = INF;
            for (int j : stations)
                maxShortestLength[i] = min(maxShortestLength[i], graph[i][j]);
            maxLength = max(maxLength, maxShortestLength[i]);
        }

        int selected = 1;
        for (int i = 1; i <= nIntersections; i++)
        {
            int maxMinLength = 0;
            for (int j = 1; j <= nIntersections; j++)
                maxMinLength = max(maxMinLength, min(graph[i][j], maxShortestLength[j]));
            if (maxMinLength < maxLength)
                maxLength = maxMinLength, selected = i;
        }
        cout << selected << endl;
        if (t)
            cout << endl;
    }
    return 0;
}