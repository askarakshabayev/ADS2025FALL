#include <iostream>
#include <queue>

using namespace std;

int n, m;
int a[100][100];


int dx[8] = {-2, -2,  2, 2, -1, -1,  1, 1};
int dy[8] = {-1,  1, -1, 1, -2,  2, -2, 2};

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

        for (int i = 0; i < 8; i++) {
            int x1 = x + dx[i];
            int y1 = y + dy[i];
            if (ok(x1, y1) && a[x1][y1] == 0) {
                a[x1][y1] = a[x][y] + 1;
                q.push(make_pair(x1, y1));
            }
        }
    }
}

int main() {
    n = 8;
    m = 8;
    int x, y, x1, y1;
    cin >> x >> y >> x1 >> y1;
    a[x][y] = 1;
    solve(x, y);

    for (int i = 0; i < n; i++) {
        for (int j = 0;j < m; j++) 
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << a[x1][y1] - 1;
    return 0;
}