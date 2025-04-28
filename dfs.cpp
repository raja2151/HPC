#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int node) {
    stack<int> s;
    s.push(node);

    while (!s.empty()) {
        int curr_node = s.top();
        s.pop();

        if (!visited[curr_node]) {
            visited[curr_node] = true;
            cout << curr_node << " ";

            // Iterate over neighbors and push them onto the stack
            for (int adj_node : graph[curr_node]) {
                if (!visited[adj_node]) {
                    s.push(adj_node);
                }
            }
        }
    }
}

int main() {
    int n, m, start_node;
    cout << "Enter No of Nodes, Edges, and Start Node: ";
    cin >> n >> m >> start_node;
    
    // n: number of nodes, m: number of edges
    
    cout << "Enter pairs of edges (u v): \n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;  // u and v: Pair of edges
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Parallelize the initialization of the visited array
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Call DFS starting from the given start node
    cout << "DFS starting from node " << start_node << ": ";
    dfs(start_node);
    cout << endl;

    return 0;
}

