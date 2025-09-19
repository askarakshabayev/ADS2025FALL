#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int> &a, int x) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] == x)
            return mid;
        else if (a[mid] > x)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

int main() {
    vector<int> a = {3, 5, 8, 13, 18, 19, 21, 27, 32};
    int ind = binary_search(a, 13);
    cout << ind;
    return 0;
}