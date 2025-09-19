#include <iostream>
#define ll long long

using namespace std;

ll can_fit(ll n, ll w, ll h) {
    return (n / w) * (n / h);
}

ll solve(ll w, ll h, ll n) {
    ll l = 0; ll r = max(w, h) * n;
    while (l + 1 < r) {
        ll mid = (l + r) / 2;
        if (can_fit(mid, w, h) >= n)
            r = mid;
        else
            l = mid;
    }
    return r;
}


int main() {
    ll w, h, n;
    cin >> w >> h >> n;
    cout << solve(w, h, n);
    return 0;
}