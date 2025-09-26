#include <iostream>
#include <queue>

using namespace std;

int n, m;
int a[100][100];

int dx[4] = {1, -1, 0,  0};
int dy[4] = {0,  0, 1, -1};

bool ok(int x, int y) {
    return (x >= 0) && (x < n) && (y >= 0) && (y < m);
}

void solve(int x, int y) {
    queue<pair<int, int> > q;
    q.push(make_pair(x, y));
    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int x1 = x + dx[i];
            int y1 = y + dy[i];
            if (ok(x1, y1) && a[x1][y1] == 0) {
                a[x1][y1] = a[x][y] + 1;
                q.push(make_pair(x1, y1));
            }
        }
        // if (x + 1 < n && a[x + 1][y] == 0) {
        //     a[x + 1][y] = a[x][y] + 1;
        //     q.push(make_pair(x + 1, y));
        // }
        // if (x - 1 >= 0 && a[x - 1][y] == 0) {
        //     a[x - 1][y] = a[x][y] + 1;
        //     q.push(make_pair(x - 1, y));
        // }

        // if (y + 1 < m && a[x][y + 1] == 0) {
        //     a[x][y + 1] = a[x][y] + 1;
        //     q.push(make_pair(x, y + 1));
        // }
        // if (y - 1 >= 0 && a[x][y - 1] == 0) {
        //     a[x][y - 1] = a[x][y] + 1;
        //     q.push(make_pair(x, y - 1));
        // }
    }
}

int main() {
    int x, y;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    cin >> x >> y;
    a[x][y] = 2;
    solve(x, y);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) 
            cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}