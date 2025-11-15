#include <iostream>
#include <vector>

using namespace std;
vector<int> g[100];
int n, m, x, y, k;

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        x--;
        y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    // for (int i = 0; i < n; i++) {
    //     cout << i + 1 << " --- ";
    //     for (int j = 0; j < g[i].size(); j++)
    //         cout << g[i][j] + 1 << " ";
    //     cout << endl;
    // }
    cin >> k;
    k--;
    for (int i = 0; i < g[k].size(); i++)
        cout << g[k][i] + 1 << " ";
    return 0;
}