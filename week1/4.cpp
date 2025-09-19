#include <iostream>

using namespace std;

vector<int> prime_numbers(int n) {
    int a[n + 1];
    for (int i = 0; i <= n; i++)
        a[i] = 0;
    for (int i = 2; i * i <= n; i++) {
        if (a[i] == 0) {
            for (int j = i * i; j <= n; j+=i)
                a[j] = 1;
        }
    }
    vector<int> result;
    for (int i = 2; i <=n; i++)
        if (a[i] == 0)
            result.push_back(i);
    return result;

}

int main() {
    int n;
    cin >> n;
    vector<int> primes = prime_numbers(n);
    for (int i = 0; i < primes.size(); i++)
        cout << primes[i] << " ";
    return 0;
}