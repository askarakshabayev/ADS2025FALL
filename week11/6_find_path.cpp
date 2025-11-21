// Find path between two vertices using DFS
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
vector<int> path;
int n, m;

bool DFS_path(int v, int target) {
    visited[v] = true;
    path.push_back(v);

    if (v == target) {
        return true;
    }

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u]) {
            if (DFS_path(u, target))
                return true;
        }
    }

    path.pop_back();
    return false;
}

void findPath(int start, int end) {
    for (int i = 0; i < n; i++)
        visited[i] = false;

    path.clear();

    if (DFS_path(start, end)) {
        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] + 1;
            if (i < path.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path" << endl;
    }
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

    int start, end;
    cin >> start >> end;
    start--; end--;

    findPath(start, end);

    return 0;
}
