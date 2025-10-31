#include <iostream>

using namespace std;
int n, m, x;
int a[1000000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int k = 0; k < m; k++) {
        cin >> x;
        int l = -1, r = n;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (a[m] >= x)
                r = m;
            else
                l = m;
            //cout << l << " " << r << endl;
        }
        if (a[r] == x)
            cout << r + 1 << endl;
        else 
            cout << -1 << endl;
    }
    return 0;
}