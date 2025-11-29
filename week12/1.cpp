#include <iostream>
#include <vector>
#define mp make_pair
#define pb push_back

using namespace std;

vector<pair<int, int > > g[100];
int n, m, x, y, w;
int d[100];
int u[100];
int p[100];

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        x--;
        y--;
        g[x].pb(mp(y, w));
        g[y].pb(mp(x, w));
    }
    int INF = 1000000;
    for (int i = 0; i < n; i++)
        d[i] = INF;
    d[0] = 0;

    for (int i = 0; i < n; i++) {
        // step 1
        int v = -1;
        for (int j = 0; j < n; j++)
            if (u[j] == 0) 
                if (v == -1 || d[v] > d[j])
                    v = j;
        u[v] = true;
        // step 2
        for (int j = 0; j < g[v].size(); j++) {
            int k = g[v][j].first;
            int l = g[v][j].second;
            if (u[k] == false && d[k] > l) {
                d[k] = l;
                p[k] = v;
            }
        }

        // for (int j = 0; j < n; j++)
        //     cout << u[j] << " ";
        // cout << endl;
        // for (int j = 0; j < n; j++) 
        //     cout << d[j] << " ";
        // cout << endl;
        // for (int j = 0; j < n; j++) 
        //     cout << p[j] << " ";
        // cout << endl;
        // cout << endl;
    }
    for (int j = 0; j < n; j++)
        if (p[j] != j)
            cout << j + 1 << " " << p[j] + 1 << endl;
    return 0;
}