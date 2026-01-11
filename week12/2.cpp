#include <iostream>
#include <vector>
#define pb push_back
#define mp make_pair
#define f first
#define s second 

using namespace std;
vector<pair<int, pair<int, int> > > g;
int p[100];
int r[100];
int n, m, x, y, w;

int find(int v) {
    if (p[v] == v)
        return v;
    p[v] = find(p[v]);
    return p[v];
}

void union_set(int v, int u) {
    v = find(v);
    u = find(u);
    if (r[v] < r[u])
        p[v] = u;
    else if (r[u] < r[v])
        p[u] = v;
    else {
        p[u] = v;
        r[v]++;
    }
}

int main() {
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
    // for (int i = 0; i < m; i++) 
    //     cout << g[i].s.f << " " << g[i].s.s << " " << g[i].f << endl;
    int sum = 0;
    for (int i = 0; i < m; i++) {
        int v = g[i].s.f;
        int u = g[i].s.s;

        if (find(v) != find(u)) {
            union_set(u, v);
            sum += g[i].f;
            cout << g[i].s.f + 1 << " " << g[i].s.s + 1 << endl;
        }
    }
    cout << sum;
    return 0;
}