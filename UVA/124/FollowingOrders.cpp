#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

string line;
vector<int> graph[30];
int inDegree[30];
bool visited[30];
vector<int> topoOrder;
set<int> letters;

void printVector()
{
    for (int i : topoOrder)
        cout << (char)(i + 'a');
    cout << endl;
}

void allPosibleTopoSorts()
{
    for (auto it = letters.begin(); it != letters.end(); ++it)
    {
        if (inDegree[*it]== 0 && !visited[*it])
        {
            for (int v : graph[*it])
                inDegree[v]--;
            topoOrder.push_back(*it);
            visited[*it] = true;
            allPosibleTopoSorts();
            for (int v : graph[*it])
                inDegree[v]++;
            topoOrder.pop_back();
            visited[*it] = false;
        }
    }
    if (topoOrder.size() == letters.size())
        printVector();
}

int main()
{
    getline(cin, line);
    while (true)
    {
        topoOrder.clear();
        letters.clear();
        for (int i = 0; i < 30; i++)
            visited[i] = false, graph[i].clear();

        for (int i = 0; i < line.length(); i++)
            if (line[i] != ' ')
                letters.insert(line[i] - 'a');
        getline(cin, line);
        for (int i = 0; i < line.length(); i += 4)
        {
            graph[line[i + 2] - 'a'].push_back(line[i] - 'a');
            inDegree[line[i] - 'a'];
        }
        allPosibleTopoSorts();
        getline(cin, line);
        if (cin)
            cout << endl;
        else
            break;
    }
    return 0;
}