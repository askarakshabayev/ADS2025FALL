#include <iostream>

using namespace std;

int gcd(int a, int b) {
    for (int i = min(a, b); i >= 1; --i) {
        if (a % i == 0 && b % i == 0) {
            return i;
        }
    }
    return 1;
}

int gcd2(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd2(b, a % b);
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << gcd2(a, b) << endl;
    return 0;
}