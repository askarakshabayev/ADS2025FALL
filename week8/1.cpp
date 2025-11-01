#include <iostream>

using namespace std;
int n, x;
int a[1000000];

int main() {
    cin >> n >> x;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int l = -1;
    int r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[m] >= x)
            r = m;
        else 
            l = m;
//        cout << l << " " << r << endl;
    }
    if (a[r] >= x)
        cout << r + 1;
    else
        cout << -1;
        
    return 0;
}