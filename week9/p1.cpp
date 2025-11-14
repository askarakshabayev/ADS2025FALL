#include <iostream>
#include <vector>

using namespace std;

vector<int> prefix_function(string s) {
    int n = s.size();
    vector<int> pi(n);
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        for (int l = 1; l <= i; l++) {
            if (s.substr(0, l) == s.substr(i - l + 1, l))
                pi[i] = l;
        }
    }
    return pi;
}

vector<int> prefix_functionv2(string s) {
    int n = s.size();
    vector<int> pi(n);
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    string s;
    cin >> s;
    vector<int> pi = prefix_functionv2(s);
    for (int i = 0; i < s.size(); i++)
        cout << pi[i] << " ";
    return 0;
}