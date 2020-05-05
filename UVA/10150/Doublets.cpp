#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <sstream>

using namespace std;

string line, from, to;
unordered_set<string> dictionary;
unordered_map<string, string> ancestors;
unordered_set<string> visited;

bool bfs(string source, string destiny)
{
    visited.clear();
    ancestors.clear();
    visited.insert(source);
    queue<string> q;
    q.push(source);
    string current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current == destiny)
            return true;

        string parent = current;

        for (int i = 0; i < current.length(); i++)
        {
            char original = current[i];
            for (char j = 'a'; j <= 'z'; j++)
            {
                if (j == original)
                    continue;
                current[i] = j;
                if (visited.find(current) == visited.end() && dictionary.find(current) != dictionary.end())
                    q.push(current), visited.insert(current), ancestors[current] = parent;
            }
            current[i] = original;
        }
    }
    return false;
}

int main()
{
    int first = true;
    while (getline(cin, line))
    {
        if (line != "")
            dictionary.insert(line);
        else
        {
            while (cin >> from >> to)
            {
                if (first)
                    first = false;
                else
                    cout << endl;
                if (bfs(from, to))
                {
                    string current = to;
                    stack<string> res;
                    while (current != from)
                    {
                        res.push(current);
                        current = ancestors[current];
                    }
                    res.push(from);
                    while (!res.empty())
                    {
                        cout << res.top() << endl;
                        res.pop();
                    }
                }
                else
                    cout << "No solution." << endl;
            }
        }
    }
    return 0;
}