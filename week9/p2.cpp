#include <iostream>
#include <vector>

using namespace std;

vector<int> prefix_function(string s) {
    int n = s.size();
    vector<int> pi(n);
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        for (int len = 1; len <= i; len++) {
            // if (s.substr(0, len) == s.substr(i - len + 1, len))
            //     pi[i] = len;
            bool match = true;
            for (int k = 0; k < len; k++) {
                if (s[k] != s[i - len + 1 + k]) {
                    match = false;
                    break;
                }
            }
            if (match)
                pi[i] = len;
        }
    }
}

int main() {
    return 0;
}