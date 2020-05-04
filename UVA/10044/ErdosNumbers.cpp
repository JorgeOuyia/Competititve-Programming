#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_map>
#include <sstream>

#define INF 0x3f3f3f3f

using namespace std;

int papers, names, erdos, id = 1;
string line, name;
unordered_map<string, int> hashMap;
vector<int> graph[50000];
int distances[50000];

int bfs(int source, int destiny)
{
    for (int i = 0; i <= id; i++)
        distances[i] = INF;
    distances[source] = 0;
    queue<int> q;
    q.push(source);
    int current;
    while (!q.empty())
    {
        current = q.front(), q.pop();

        if (current == destiny)
            return distances[current];

        for (int v : graph[current])
        {
            if (distances[v] > distances[current] + 1)
                distances[v] = distances[current] + 1, q.push(v);
        }
    }
    return -1;
}

int main()
{
    id = 1;
    int scenario = 1;
    int t;
    cin >> t;
    while (t--)
    {
        cin >> papers >> names;
        for (int i = 0; i <= id; i++)
            graph[i].clear();
        id = 1;
        hashMap.clear();
        cin.ignore();
        for (int i = 0; i < papers; i++)
        {
            getline(cin, line);
            vector<int> res;
            string name;
            int j = 0;
            int comas = 0;
            while (j < line.length())
            {
                if (comas != 1)
                    while (line[j] == ' ')
                        j++;
                if (line[j] == ',' || line[j] == ':')
                    comas++;
                name.push_back(line[j]);
                if (comas == 2)
                {
                    name.pop_back();
                    while (name[name.length() - 1] == ' ')
                        name.pop_back();
                    if (hashMap.find(name) == hashMap.end())
                        hashMap[name] = id++;
                    if (name == "Erdos, P.")
                        erdos = hashMap[name];
                    res.push_back(hashMap[name]);
                    name.clear();
                    comas = 0;
                    if (line[j] == ':')
                        break;
                    else
                        j++;
                }
                j++;
            }
            for (int i = 0; i < res.size(); i++)
            {
                for (int j = i + 1; j < res.size(); j++)
                {
                    graph[res[i]].push_back(res[j]);
                    graph[res[j]].push_back(res[i]);
                }
            }
        }
        cout << "Scenario " << scenario++ << endl;
        while (names--)
        {
            getline(cin, line);
            name.clear();
            int j = 0;
            while (line[j] == ' ')
                j++;
            while (line[line.length() - 1] == ' ')
                line.pop_back();
            for (; j < line.length(); j++)
                name.push_back(line[j]);
            if (hashMap.find("Erdos, P.") == hashMap.end())
                cout << line << " infinity" << endl;
            else
            {
                int dist;
                if (hashMap.find(name) == hashMap.end())
                    dist = -1;
                else
                    dist = bfs(hashMap[name], erdos);
                cout << line << " ";
                if (dist == -1)
                    cout << "infinity" << endl;
                else
                    cout << dist << endl;
            }
        }
    }
    return 0;
}