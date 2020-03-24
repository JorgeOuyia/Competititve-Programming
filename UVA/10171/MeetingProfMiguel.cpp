#include <iostream>
#include <string>
#include <cstring>
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

int streets;
int distancesYoung[30], distancesOld[30];
vector<Edge> young[30];
vector<Edge> old[30];
char who, sense, from, to, me, miguel;
int dist;

void dijkstra(int start, vector<Edge> graph[30], int* distances)
{
    distances[start] = 0;
    priority_queue<Edge> pq;
    pq.push({ start, 0 });
    Edge current;
    while (!pq.empty())
    {
        current = pq.top();
        pq.pop();

        if (current.dist <= distances[current.node])
        {
            for (Edge to : graph[current.node])
            {
                int p = to.dist + current.dist;
                if (distances[to.node] > p)
                {
                    distances[to.node] = p;
                    pq.push({ to.node, p });
                }
            }
        }
    }
    return;
}

int main()
{
    while (cin >> streets && streets != 0)
    {
        for (int i = 0; i < 30; i++)
            distancesYoung[i] = INF, distancesOld[i] = INF, young[i].clear(), old[i].clear();
        for (int i = 0; i < streets; i++)
        {
            cin >> who >> sense >> from >> to >> dist;

            if (who == 'Y')
            {
                young[from - 'A'].push_back({ to - 'A', dist });
                if (sense == 'B')
                    young[to - 'A'].push_back({ from - 'A', dist });
            }
            else
            {
                old[from - 'A'].push_back({ to - 'A', dist });
                if (sense == 'B')
                    old[to - 'A'].push_back({ from - 'A', dist });
            }
        }
        cin >> me >> miguel;
        dijkstra(me - 'A', young, distancesYoung);
        dijkstra(miguel - 'A', old, distancesOld);
        int minimum = 0x3f3f3f3f;
        for (int i = 0; i < 30; i++)
        {
            if (distancesYoung[i] + distancesOld[i] < minimum && distancesYoung[i] + distancesOld[i] >= 0)
                minimum = distancesOld[i] + distancesYoung[i];
        }
        vector<char> res;
        if (minimum != 0x3f3f3f3f)
        {
            for (int i = 0; i < 30; i++)
                if (distancesYoung[i] + distancesOld[i] == minimum)
                    res.push_back(i + 'A');
            cout << minimum;
            for (char c : res)
                cout << " " << c;
            cout << endl;
        }            
        else
            cout << "You will never meet." << endl;
    }
    return 0;
}