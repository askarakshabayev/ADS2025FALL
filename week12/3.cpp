#include <iostream>
#include <vector>
#define pb push_back
#define mp make_pair
#define f first
#define s second 

using namespace std;
vector<pair<int, int> > g[100];
int INF = 100000;
int d[100];
int p[100];
int u[100];
int n, m, x, y, w, s;

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
        d[i] = INF;
    cin >> s; 
    cout << s << endl;
    s--;
    d[s] = 0;
    p[s] = s;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++)
            if (u[j] == 0)
                if (v == -1 || d[v] > d[j])
                    v = j;
        u[v] = true; // S ------> V (d[v]) ---W-- to (d[to])
                     // S ----------------------> to (d[to])
        for (int j = 0; j < g[v].size(); j++) {
            int to = g[v][j].f;
            int w = g[v][j].s;
            if (u[to] == 0 && d[to] > d[v] + w) {
                d[to] = d[v] + w;
                p[to] = v;
            }
        }
    }
    // for (int i = 0; i < n; i++) {
    //     cout << d[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < n; i++) {
    //     cout << p[i] + 1 << " ";
    // }
    int f;
    cin >> f;
    f--;
    int old_f = f;
    vector<int> result;
    while (p[f] != f) {
        result.pb(f);
        f = p[f];
    }
    result.pb(s);
    for (int i = result.size() - 1; i >= 0; i--) 
        cout << result[i] + 1 << " ";
    cout << endl;
    cout << d[old_f];
    return 0;
}