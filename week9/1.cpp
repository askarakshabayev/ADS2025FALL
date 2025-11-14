#include <iostream>
#include <vector>

using namespace std;

vector<int> prefix_function(string s) {
    int n = s.size();
    vector<int> p(n);
    p[0] = 0;
    for (int i = 1; i < n; i++) {
        for (int len = 1; len <= i; len++)
            if (s.substr(0, len) == s.substr(i - len + 1, len))
                p[i] = len;
    }
    return p;
}

int main() {
    string s;
    cin >> s;
    vector<int> p = prefix_function(s);
    for (int i = 0; i < s.size(); i++)
        cout << p[i] << " ";
    return 0;
}