#include <iostream>
#include <vector>

using namespace std;

bool exists(vector<int> &a, int x) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] == x)
            return true;
        if (a[mid] > x) 
            r = mid - 1;
        else
            l = mid + 1;
    }
    return false;
}

int main() {
    int n, k, t;
    cin >> n >> k;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        cin >> t;
        a.push_back(t);
    }
    for (int i = 0; i < k; i++) {
        cin >> t;
        if (exists(a, t))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}