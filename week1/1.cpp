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

int main() {
    ll a, b;
    cin >> a >> b;
    cout << gcd1(a, b) << endl;
    return 0;
}
