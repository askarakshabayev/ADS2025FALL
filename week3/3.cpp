#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int> &a, int x) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        cout << l << " " << r << endl;
        int m = (l + r) / 2;
        if (a[m] == x)
            return m;
        if (a[m] > x)
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

int main() {
    int n;
    vector<int> a;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        a.push_back(t);
    }
    int x;
    cin >> x;
    int ind = binary_search(a, x);
    cout << ind;
        
    return 0;
}