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


int main() {
    return 0;
}