// Check if graph is bipartite using DFS
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
int color[MAXN];
int n, m;

bool DFS_bipartite(int v, int c) {
    color[v] = c;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];

        if (color[u] == 0) {
            if (!DFS_bipartite(u, 3 - c))
                return false;
        }
        else if (color[u] == c) {
            return false;
        }
    }

    return true;
}

bool isBipartite() {
    for (int i = 0; i < n; i++)
        color[i] = 0;

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (!DFS_bipartite(i, 1))
                return false;
        }
    }

    return true;
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

    if (isBipartite())
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
