#include <iostream>
#include <queue>

using namespace std;
int a[100][100];
int n;

void modify(int x, int y) {
    a[x][y] = 2;
    queue<pair<int, int> > q;
    q.push(make_pair(x, y));
    while (!q.empty()) {
        // x + 1, y
        x = q.front().first;
        y = q.front().second;
        // cout << x << " " << y << endl;
        q.pop();
        if (x + 1 < n && a[x + 1][y] == 0) {
            q.push(make_pair(x + 1, y));
            a[x + 1][y] = a[x][y] + 1;
        }
        if (x - 1 >= 0 && a[x - 1][y] == 0) {
            q.push(make_pair(x - 1, y));
            a[x - 1][y] = a[x][y] + 1;
        }
        if (y - 1 >= 0 && a[x][y - 1] == 0) {
            q.push(make_pair(x, y - 1));
            a[x][y - 1] = a[x][y] + 1;
        }
        if (y + 1 < n && a[x][y + 1] == 0) {
            q.push(make_pair(x, y + 1));
            a[x][y + 1] = a[x][y] + 1;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    int x, y;
    cin >> x >> y;
    modify(x, y);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j];
        }
        cout << endl;
    }
    return 0;
}