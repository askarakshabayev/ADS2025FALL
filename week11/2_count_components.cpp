// Count connected components using DFS
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
int n, m;

void DFS(int v) {
    visited[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u]) {
            DFS(u);
        }
    }
}

int countComponents() {
    for (int i = 0; i < n; i++)
        visited[i] = false;

    int components = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS(i);
            components++;
        }
    }

    return components;
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

    cout << countComponents() << endl;

    return 0;
}
