// Cycle detection in undirected graph using DFS
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
int n, m;

bool DFS_cycle(int v, int parent) {
    visited[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];

        if (!visited[u]) {
            if (DFS_cycle(u, v))
                return true;
        }
        else if (u != parent) {
            return true;
        }
    }

    return false;
}

bool hasCycle() {
    for (int i = 0; i < n; i++)
        visited[i] = false;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (DFS_cycle(i, -1))
                return true;
        }
    }

    return false;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    if (hasCycle())
        cout << "Cycle found" << endl;
    else
        cout << "No cycle" << endl;

    return 0;
}
