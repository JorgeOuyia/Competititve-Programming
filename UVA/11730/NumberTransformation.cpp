#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

struct Edge
{
    int num, transformations;
};

int from, to;
vector<int> allPrimes;
unordered_set<int> visited;
unordered_map<int, vector<int>> primeFactors;
bool prime[1005];

void erastothenes(int n)
{
    for (int i = 0; i <= n; i++)
        prime[i] = true;

    for (int p = 2; p * p <= n; p++)
    {
        if (prime[p])
        {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    for (int i = 2; i <= n; i++)
        if (prime[i])
            allPrimes.push_back(i);
}

void extractAllPrimeFactors()
{
    for (int num : allPrimes)
    {
        for (int i = num + num; i <= 1000; i += num)
            primeFactors[i].push_back(num);
    }
}

int bfs(int source, int destiny)
{
    visited.insert(source);
    queue<Edge> q;
    q.push({source, 0});
    Edge current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current.num == destiny)
            return current.transformations;

        for (int prime : primeFactors[current.num])
        {
            int next = current.num + prime;
            if (next <= destiny && visited.find(next) == visited.end())
                visited.insert(next), q.push({next, current.transformations + 1});
        }
    }
    return -1;
}

int main()
{
    erastothenes(1000);
    extractAllPrimeFactors();
    int scenario = 1;
    while (cin >> from >> to && (from || to))
    {
        visited.clear();
        cout << "Case " << scenario++ << ": " << bfs(from, to) << endl;
        ;
    }
    return 0;
}