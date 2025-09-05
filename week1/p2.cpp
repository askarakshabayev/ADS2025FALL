#include <iostream>
#define ll long long
using namespace std;

ll bin_pow(ll a, ll b, ll m) {
    if (b == 0) 
        return 1;
    if (b % 2 == 0) {
        ll half = bin_pow(a, b / 2, m);
        return (half * half) % m;
    } else {
        return (a * bin_pow(a, b - 1, m)) % m;
    }
}

ll pow_a_b(ll a, ll b) {
    if (b == 0) 
        return 1;
    ll result = 1;
    for (ll i = 0; i < b; ++i) 
        result *= a;
    return result;
}

int main() {
    ll a, b, m;
    cin >> a >> b >> m;
    cout << bin_pow(a, b, m) << endl;
    return 0;
}