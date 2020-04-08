#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

struct Edge
{
    int from, to, cost;

    bool operator<(const Edge& other) const
    {
        return other.cost < cost;
    }
};

int computerSites, from, to, cost, aditional, mstSumHighSpeed, mstSumOriginal, original;
priority_queue<Edge> highSpeed;
priority_queue<Edge> originalLines;
int parentsHighSpeed[1000005];
int parentsOriginal[1000005];
int szHighSpeed[1000005];
int szOriginal[1000005];

int find(int x, int* parents)
{
    if (x == parents[x])
        return x;
    return parents[x] = find(parents[x], parents);
}

void connect(int x, int y, int* parents, int* sz, int cost, int& mst)
{
    x = find(x, parents);
    y = find(y, parents);

    if (x != y)
    {
        if (sz[x] >= sz[y])
            parents[y] = x, sz[x] += sz[y];
        else
            parents[x] = y, sz[y] += sz[x];
        mst += cost;
    }
}

int main()
{
    cin >> computerSites;
    while (true)
    {
        mstSumHighSpeed = 0, mstSumOriginal = 0;
        for (int i = 1; i <= computerSites; i++)
            parentsHighSpeed[i] = i, parentsOriginal[i] = i, szHighSpeed[i] = 1, szOriginal[i] = 1;
        for (int i = 0; i < computerSites - 1; i++)
        {
            cin >> from >> to >> cost;
            highSpeed.push({ from, to, cost });
        }
        cin >> aditional;
        for (int i = 0; i < aditional; i++)
        {
            cin >> from >> to >> cost;
            originalLines.push({ from, to, cost });
        }
        cin >> original;
        for (int i = 0; i < original; i++)
        {
            cin >> from >> to >> cost;
            originalLines.push({ from, to, cost });
        }
        Edge current;
        while (!highSpeed.empty())
        {
            current = highSpeed.top(), highSpeed.pop();
            connect(current.from, current.to, parentsHighSpeed, szHighSpeed, current.cost, mstSumHighSpeed);
        }
        while (!originalLines.empty())
        {
            current = originalLines.top(), originalLines.pop();
            connect(current.from, current.to, parentsOriginal, szOriginal, current.cost, mstSumOriginal);
        }
        cout << mstSumHighSpeed << endl;
        cout << mstSumOriginal << endl;
        cin >> computerSites;
        if (cin)
            cout << endl;
        else
            break;
    }
    return 0;
}