#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <map>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge
{
    int from, to, years;
};

int starSystems, wormholes, from, to, year;
vector<Edge> graph;
int years[1005];

bool bellmanFord(int start)
{
    years[start] = 0;
    int relaxation = starSystems - 1;
    for (int i = 0; i < relaxation; i++)
    {
        for (Edge v : graph)
        {
            if (years[v.to] > years[v.from] + v.years)
                years[v.to] = years[v.from] + v.years;
        }
    }
    for (Edge v : graph)
    {
        if (years[v.to] > years[v.from] + v.years)
            return true;
    }
    return false;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> starSystems >> wormholes;
        graph.clear();
        for (int i = 0; i < starSystems; i++)
            years[i] = INF;
        for (int i = 0; i < wormholes; i++)
        {
            cin >> from >> to >> year;
            graph.push_back({ from, to, year });
        }
        if (bellmanFord(0))
            cout << "possible" << endl;
        else
            cout << "not possible" << endl;
    }
    return 0;
}