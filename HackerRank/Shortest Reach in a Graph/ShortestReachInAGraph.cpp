#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge
{
    int node, dist;
};

class Graph {
    public:
        vector<Edge> graph[1005];
        bool visited[1005];
        vector<int> res;
        Graph(int n) {
            res.clear();
            for (int i = 0; i < n; i++)
                graph[i].clear(), visited[i] = false, res.push_back(-1);
        }
    
        void add_edge(int u, int v) {
            graph[u].push_back({v, 6});
            graph[v].push_back({u, 6});
        }
    
        vector<int> shortest_reach(int start) {
            queue<Edge> q;
            q.push({start, 0});
            visited[start] = true;
            Edge current;
            while (!q.empty())
            {
                current = q.front();
                q.pop();
                for (Edge to : graph[current.node])
                {
                    if (!visited[to.node])
                    {
                        visited[to.node] = true;
                        q.push({to.node, current.dist + 6});
                        res[to.node] = current.dist + 6;
                    }
                }
            }
            return res;
        }
    
};

int main() {
    int queries;
    cin >> queries;
        
    for (int t = 0; t < queries; t++) {
      
		int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
		int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}