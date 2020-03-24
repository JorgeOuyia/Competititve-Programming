#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <stack>
#include <queue>
#include <unordered_set>

using namespace std;

int n, aux, q;
string line, a, b;
unordered_map<string, int> trad;
unordered_map<int, string> reverseTrad;
vector<int> graph[105];
bool visited[105];
int inDegree[105];
priority_queue<int, vector<int>, greater<int>> c;
vector<int> order;

int main()
{
    int scenario = 1;
    while (cin >> n)
    {
        aux = 1;
        trad.clear();
        reverseTrad.clear();
        order.clear();
        for (int i = 1; i <= n; i++)
            visited[i] = false, graph[i].clear(), inDegree[i] = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> line;
            trad[line] = aux;
            reverseTrad[aux++] = line;
        }
        cin >> q;
        for (int i = 0; i < q; i++)
        {
            cin >> a >> b;
            graph[trad[a]].push_back(trad[b]);
            inDegree[trad[b]]++;
        }
        for (int i = 1; i <= n; i++)
        {
            if (inDegree[i] == 0)
                c.push(i);
        }
        while (!c.empty())
        {
            int current = c.top();
            c.pop();
            order.push_back(current);
            for (int v : graph[current])
            {
                if (!visited[v])
                {
                    inDegree[v]--;
                    if (inDegree[v] == 0)
                    {
                        visited[v] = true;
                        c.push(v);
                    }
                }
            }
        }
        cout << "Case #" << scenario << ": Dilbert should drink beverages in this order:";
        for (int n : order)
            cout << " " << reverseTrad[n];
        cout << "." << endl;
        cout << endl;
        scenario++;
    }
    return 0;
}