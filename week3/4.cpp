#include <iostream>

using namespace std;
double x;
double eps = 1e-3;

double f(double y) {
    return y * y * y;
}

double solve(double x) {
    double l = 0, r = x;
    while (r - l > eps) {
        cout << l << " " << r << " " << (l + r) / 2.0 << endl;
        double y = (l + r) / 2;
        cout << f(y) << endl;
        if (f(y) >= x)
            r = y;
        else
            l = y;
    }
    return l;
}

int main() {
    cin >> x;
    cout << solve(x);
    return 0;
}