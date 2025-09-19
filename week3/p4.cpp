#include <iostream>
#include <vector>

using namespace std;

int index_(vector<int> &a, int x) {
    int l = -1, r = a.size(); 
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (a[mid] >= x)
            r = mid;
        else
            l = mid;
        // cout << l << " " << r << " " << mid << endl;
    }
    return r;
}

int main() {
    int n, k, t;
    vector<int> a;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> t;
        a.push_back(t);
    }
    for (int i = 0; i < k; i++) {
        cin >> t;
        cout << index_(a, t) + 1 << endl;
    }
    return 0;
}