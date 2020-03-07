#include <iostream>
#include <map>
#include <vector>

using namespace std;

int t, nodes, k, from, to, edges, oddNum, flag;
map<int, int> edgesVertex;
int inDegree[105];

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> nodes;
        for (int i = 1; i <= nodes; i++)
            inDegree[i] = 0;
        oddNum = 0;
        flag = 1;
        cin >> k;
        while (k--)
        {
            cin >> from >> to >> edges;
            inDegree[from] += edges;
            inDegree[to] += edges;
        }
        for (int i = 1; i <= nodes; i++)
            if (inDegree[i] % 2)
                oddNum++;
        if (oddNum == 0)
            cout << "YES 1" << endl;
        else if (oddNum == 2)
        {
            for (int i = 1; i <= nodes; i++)
            {
                if (inDegree[i] % 2)
                {
                    cout << "YES " << i << endl;
                    break;
                }
            }
        }
        else
            cout << "NO" << endl;
    }
    return 0;
}