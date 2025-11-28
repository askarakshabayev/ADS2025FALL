#include <iostream>
#include <vector>
#define pb push_back
#define mp make_pair

using namespace std;
vector<pair<int, pair<int, int> > > g;
int n, m, x, y, w;
int p[100];
int r[100];

int find(int v) {
    if (v == p[v])
        return v;
    p[v] = find(p[v]);
    return p[v];
}

void union_set(int v, int u) {
    v = find(v);
    u = find(u);
    if (r[v] < r[u])
        p[v] = u;
    else if (r[v] > r[u])
        p[u] = v;
    else {
        p[u] = v;
        r[u]++;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        x--;
        y--;
        g.pb(mp(w, mp(x, y)));
    }
    sort(g.begin(), g.end());
    for (int i = 0; i < n; i++)
        p[i] = i;

    for (int i = 0; i < m; i++) {
        int x = g[i].second.first;
        int y = g[i].second.second;
        if (find(x) != find(y)) {
            union_set(x, y); 
            cout << x + 1 << " " << y + 1 << endl;
        }
    }
    return 0;
}