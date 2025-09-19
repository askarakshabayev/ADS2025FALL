#include <iostream>
#include <vector>

using namespace std;

double eps = 1e-8;

bool ok(vector<double> &a, int n, double t) {
    int p = 0;
    for (int i = 0; i < a.size(); i++)
        p += (int) (a[i] / t);
    return p >= n;
}

double solve(vector<double> &a, int n) {
    double l = 0, r = 1e9;
    while (r - l > eps) {
        double mid = (l + r) / 2.0;
        if (!ok(a, n, mid)) 
            r = mid;
        else
            l = mid;
    }
    return l;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<double> a;
    for (int i = 0; i < n; i++) {
        double q;
        cin >> q;
        a.push_back(q);
    }
    cout << solve(a, k);
    return 0;
}