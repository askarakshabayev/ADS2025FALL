#include <iostream>

using namespace std;
int n, m, k;

bool f(int x) {
    return (x / n) * (x / m) >= k;
}

int solve(int n, int m, int k) {
    int l = 0;
    int r = max(n, m) * k;
    while (l + 1 < r) {
        cout << l << " " << r << " " << (l + r) / 2 << endl;
        int x = (l + r) / 2;
        if (f(x) == true)
            r = x;
        else
            l = x;
    }
    return r;
}

int main() {
    cin >> n >> m >> k;
    cout << solve(n, m, k);
    return 0;
}