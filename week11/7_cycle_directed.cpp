// Cycle detection in directed graph using DFS
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
bool recStack[MAXN];
int n, m;

bool DFS_cycle_directed(int v) {
    visited[v] = true;
    recStack[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];

        if (!visited[u]) {
            if (DFS_cycle_directed(u))
                return true;
        }
        else if (recStack[u]) {
            return true;
        }
    }

    recStack[v] = false;
    return false;
}

bool hasCycleDirected() {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (DFS_cycle_directed(i))
                return true;
        }
    }

    return false;
}

int main() {
    cin >> n >> m;

    // Directed edges
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
    }

    if (hasCycleDirected())
        cout << "Cycle found" << endl;
    else
        cout << "No cycle (DAG)" << endl;

    return 0;
}
