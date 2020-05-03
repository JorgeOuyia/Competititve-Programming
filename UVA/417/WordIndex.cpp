#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

string line;

int bfs()
{
    int res = 0;
    queue<string> q;
    q.push("");
    string current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current == line)
            return res;

        res++;

        if (current == "")
        {
            for (char i = 'a'; i <= 'z'; i++)
            {
                string s;
                s.push_back(i);
                q.push(s);
            }
        }
        else
        {
            for (char i = current[current.length() - 1] + 1; i <= 'z'; i++)
                q.push(current + i);
        }
    }
    return 0;
}

int main()
{
    while (cin >> line)
    {
        int possible = true;
        for (int i = 1; i < line.length(); i++)
            if (line[i - 1] >= line[i])
                possible = false;
        if (!possible)
        {
            cout << 0 << endl;
            continue;
        }
        cout << bfs() << endl;
    }
    return 0;
}