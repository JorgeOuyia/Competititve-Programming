#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int t, aux, flag = 0, first;
string line;
unordered_map<char, int> trad;
unordered_map<int, char> reverseTrad;
unordered_set<int> graph[30];
int inDegree[30];
bool visited[30];
vector<int> topoOrder;

void printVector(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (i == 0)
            cout << reverseTrad[vec[i]];
        else
            cout << " " << reverseTrad[vec[i]];
    }
}

void dfs()
{
    for (auto it = trad.begin(); it != trad.end(); ++it)
    {
        if (inDegree[it->second] == 0 && !visited[it->second])
        {
            for (int v : graph[it->second])
                inDegree[v]--;
            topoOrder.push_back(it->second);
            visited[it->second] = true;
            dfs();
            for (int v : graph[it->second])
                inDegree[v]++;
            topoOrder.pop_back();
            visited[it->second] = false;
        }
    }
    if (topoOrder.size() == trad.size())
    {
        flag = 1;
        printVector(topoOrder);
        cout << endl;
    }
}

int main()
{
    cin >> t;
    first = true;
    while (t--)
    {
        aux = 1;
        flag = 0;
        trad.clear(), reverseTrad.clear(), topoOrder.clear();
        if (first)
            cin.ignore(), cin.ignore(), first = false;
        else
            cin.ignore();
        getline(cin, line);
        for (int i = 1; i < 30; i++)
            graph[i].clear(), visited[i] = false, inDegree[i] = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] != ' ')
            {
                trad[line[i]] = aux;
                reverseTrad[aux++] = line[i];
            }
        }
        getline(cin, line);
        for (int i = 0; i < line.length(); i += 3)
        {
            if (line[i] == ' ')
                i++;
            char a, sign, b;
            a = line[i], sign = line[i + 1], b = line[i + 2];
            if (sign == '<')
                graph[trad[a]].insert(trad[b]), inDegree[trad[b]]++;
            else
                graph[trad[b]].insert(trad[a]), inDegree[trad[a]]++;
        }
        dfs();
        if (!flag)
            cout << "NO" << endl;
    }
    return 0;
}