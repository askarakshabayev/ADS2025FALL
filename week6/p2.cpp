#include <iostream>

using namespace std;
int a[100];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swapped = true;
                swap(a[j], a[j + 1]);
            }
        }
        if (swapped == false)
            break;
    }

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    return 0;
}