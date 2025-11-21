// Count number of islands in 2D grid using DFS
// An island is a group of connected 1s (horizontally or vertically)
#include <iostream>

using namespace std;

const int MAXN = 100;
int grid[MAXN][MAXN];
bool visited[MAXN][MAXN];
int n, m;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void DFS(int x, int y) {
    visited[x][y] = true;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 1) {
            DFS(nx, ny);
        }
    }
}

int countIslands() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            visited[i][j] = false;

    int islands = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                DFS(i, j);
                islands++;
            }
        }
    }

    return islands;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    cout << countIslands() << endl;

    return 0;
}
