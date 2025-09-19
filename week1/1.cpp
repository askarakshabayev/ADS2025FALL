#include <iostream>
#define ll long long

using namespace std;

ll gcd1(ll a, ll b) {
    for (ll i = min(a, b); i >= 1; --i) {
        if (a % i == 0 && b % i == 0) {
            return i;
        }
    }
    return 1;
}

ll gcd2(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd2(b, a % b);
}

ll gcd3(ll a, ll b) {
    while (a > 0 && b > 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    return a + b;
}

int main() {
    ll a, b;
    cin >> a >> b;
    cout << gcd1(a, b) << endl;
    return 0;
}
