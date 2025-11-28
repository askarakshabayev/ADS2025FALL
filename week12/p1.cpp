#include <iostream>
#include <vector>
#define mp make_pair
#define pb push_back

using namespace std;
int n, m, x, y, w;
vector<pair<int, int> > g[100];
int d[100];
int u[100];


int main() {
    cin >> n >> m; 
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        x--;
        y--;
        g[x].pb(mp(y, w));
        g[y].pb(mp(x, w));
    }
    for (int i = 0; i < n; i++)
        d[i] = -1;
    d[0] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (u[j] == 0 && (v == -1 || (d[v] > d[j] && d[j] != -1)))
                v = j;
        }
        u[v] = 1;
        for (int j = 0; j < g[v].size(); j++) {
            int x = g[v][j].first;
            int w = g[v][j].second;
            if (u[x] == 0 && (d[x] == -1 || d[x] > w))
                d[x] = w;
        }
    }

    for (int i = 0; i < n; i++)
        cout << d[i] << " ";

    return 0;
}