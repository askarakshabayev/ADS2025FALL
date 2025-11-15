#include <iostream>
#include <vector>

using namespace std;
vector<pair<int, int> > g[100];
int n, m, x, y, w, k;

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        x--;
        y--;
        g[x].push_back(make_pair(y, w));
        g[y].push_back(make_pair(x, w));
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
        cout << g[k][i].first + 1 << " " << g[k][i].second << endl;
    return 0;
}