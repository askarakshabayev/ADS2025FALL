#include <iostream>
#include <queue>

using namespace std;
int g[100][100];
queue<int> q;
int u[100];
int d[100];
int n, m, x, y;

void bfs(int x) {
    q.push(x);
    u[x] = 1;
    d[x] = 0;
    while (!q.empty()) {
        x = q.front();
        for (int y = 0; y < n; y++) {
            if (u[y] == 0 && g[x][y] == 1) {
                u[y] = 1;
                d[y] = d[x] + 1;
                q.push(y);
            }
        }
        q.pop();
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y; 
        x--; y--;
        g[x][y] = 1;
        g[y][x] = 1;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) // i = 10
        if (u[i] == 0) {
            bfs(i);
            cnt++;
        }
    cout << cnt;
    // for (int i = 0; i < n; i++)
    //     cout << d[i] << " ";

    return 0;
}