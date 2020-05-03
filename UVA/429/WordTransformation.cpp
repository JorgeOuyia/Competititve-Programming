#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <sstream>

using namespace std;

struct Edge
{
    string word;
    int cost;
};

string line, source, destiny;
unordered_set<string> dictionary;
unordered_set<string> visited;

int bfs(string source, string destiny)
{
    visited.clear();
    visited.insert(source);
    queue<Edge> q;
    q.push({source, 0});
    Edge current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current.word == destiny)
            return current.cost;

        for (int i = 0; i < current.word.length(); i++)
        {
            char original = current.word[i];
            for (char c = 'a'; c <= 'z'; c++)
            {
                current.word[i] = c;
                if (visited.find(current.word) == visited.end() && dictionary.find(current.word) != dictionary.end())
                    visited.insert(current.word), q.push({current.word, current.cost + 1});
            }
            current.word[i] = original;
        }
    }
    return -1;
}

int main()
{
    int t, first = true;
    cin >> t;
    cin.ignore();
    while (t--)
    {
        dictionary.clear();
        visited.clear();
        if (first)
            cin.ignore(), first = false;
        while (getline(cin, line) && line != "*")
            dictionary.insert(line);
        while (getline(cin, line) && line != "")
        {
            istringstream ss(line);
            ss >> source;
            ss >> destiny;
            cout << source << " " << destiny << " " << bfs(source, destiny) << endl;
        }
        if (t)
            cout << endl;
    }
    return 0;
}