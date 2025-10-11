#include <iostream>

using namespace std;
int a[1000];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n - 1; i++) { 
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;
        if (swapped == false)
            break;
    }
    return 0;
}