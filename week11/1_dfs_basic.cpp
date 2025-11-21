// Basic DFS implementation - recursive and iterative
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
int n, m;

void DFS_recursive(int v) {
    visited[v] = true;
    cout << v << " ";

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u]) {
            DFS_recursive(u);
        }
    }
}

void DFS_iterative(int start) {
    stack<int> s;

    for (int i = 0; i < n; i++)
        visited[i] = false;

    s.push(start);

    while (!s.empty()) {
        int v = s.top();
        s.pop();

        if (visited[v])
            continue;

        visited[v] = true;
        cout << v << " ";

        for (int i = adj[v].size() - 1; i >= 0; i--) {
            int u = adj[v][i];
            if (!visited[u]) {
                s.push(u);
            }
        }
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

    // Initialize visited
    for (int i = 0; i < n; i++)
        visited[i] = false;

    cout << "DFS recursive: ";
    DFS_recursive(0);
    cout << endl;

    cout << "DFS iterative: ";
    DFS_iterative(0);
    cout << endl;

    return 0;
}
