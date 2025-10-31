#include <iostream>

using namespace std;
int a[1000000];

int main() {
    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int l = -1; int r = n;
    while (r - l > 1) {
        int m = (r + l) / 2;
        if (a[m] >= x)
            r = m;
        else 
            l = m;
        // cout << l << " " << r << " " << m << endl;
    } 
    if (a[r] >= x)
        cout << r + 1;
    else 
        cout << -1;
    return 0;
}