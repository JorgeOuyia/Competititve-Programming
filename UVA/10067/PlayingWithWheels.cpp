#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Button
{
    string combination;
    int presses;
};

string source, destiny, restriction;
int restrictionsNumber;
unordered_set<string> forbidden;
unordered_set<string> visited;

int bfs(string start, string end)
{
    visited.insert(start);
    int presses = 0;
    queue<Button> q;
    q.push({start, 0});
    Button current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current.combination == end)
            return current.presses;

        string combination = current.combination;

        for (int i = 0; i < combination.length(); i++)
        {
            char original = combination[i];
            int next = (combination[i] - '0' + 1) % 10;
            int previous = (combination[i] - '0' - 1) >= 0 ? (combination[i] - '0' - 1) : 9;
            combination[i] = next + '0';
            if (visited.find(combination) == visited.end() && forbidden.find(combination) == forbidden.end())
                visited.insert(combination), q.push({combination, current.presses + 1});
            combination[i] = previous + '0';
            if (visited.find(combination) == visited.end() && forbidden.find(combination) == forbidden.end())
                visited.insert(combination), q.push({combination, current.presses + 1});
            combination[i] = original;
        }
    }
    return -1;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        source.clear(), destiny.clear(), forbidden.clear(), visited.clear();
        for (int i = 0; i < 4; i++)
        {
            int n;
            cin >> n;
            source.push_back(n + '0');
        }
        for (int i = 0; i < 4; i++)
        {
            int n;
            cin >> n;
            destiny.push_back(n + '0');
        }
        cin >> restrictionsNumber;
        while (restrictionsNumber--)
        {
            restriction.clear();
            for (int i = 0; i < 4; i++)
            {
                int n;
                cin >> n;
                restriction.push_back(n + '0');
            }
            forbidden.insert(restriction);
        }
        cout << bfs(source, destiny) << endl;
    }
    return 0;
}