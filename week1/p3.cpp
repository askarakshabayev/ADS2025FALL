#include <iostream>
#include <vector>

using namespace std;

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<int> primes(int n) {
    vector<int> is_prime(n + 1, 0);
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i] == 0) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = 1;
            }
        }
    }
    return is_prime;
}

int main() {
    int n;
    cin >> n;
    // for (int i = 1; i <= n; i++) {
    //     if (is_prime(i)) {
    //         cout << i << " ";
    //     }
    // }
    vector<int> p = primes(n);
    for (int i = 2; i <= n; i++) {
        if (p[i] == 0) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}