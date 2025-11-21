// Topological sort using DFS
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
stack<int> result;
int n, m;

void DFS_topo(int v) {
    visited[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u]) {
            DFS_topo(u);
        }
    }

    result.push(v);
}

void topologicalSort() {
    for (int i = 0; i < n; i++)
        visited[i] = false;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS_topo(i);
        }
    }

    while (!result.empty()) {
        cout << result.top() + 1 << " ";
        result.pop();
    }
    cout << endl;
}

int main() {
    cin >> n >> m;

    // Directed graph
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
    }

    topologicalSort();

    return 0;
}
