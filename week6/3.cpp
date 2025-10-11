#include <iostream>

using namespace std;
int a[11];

int main() {
    int n, x;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        a[x]++;
    }
    for (int i = 1; i <= 10; i++)
        cout << i << " " << a[i] << endl;
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < a[i]; j++)
            cout << i << " ";
    }
    return 0;
}