#include <iostream>
#include <vector>

using namespace std;

int get_hash(string s) {
    int h = 0;
    int p = 31;
    int p_pow = 1;
    for (int i = 0; i < s.size(); i++) {
        h += s[i] * p_pow;
        p_pow *= p;
    }
    return h;
} 

vector<int> get_h(string s) {
    int n = s.size();
    vector<int> h(n);
    h[0] = s[0];
    int p = 31;
    int p_pow = 31;
    for (int i = 1; i < n; i++) {
        h[i] = h[i - 1] + s[i] * p_pow;
        p_pow *= p;
    }
    return h;
}

int main() {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
    int h_t = get_hash(t);
    vector<int> h = get_h(s);
    vector<int> p(n);
    p[0] = 1;
    for (int i = 1; i < n; i++)
        p[i] = p[i - 1] * 31;
    // cout << h_t << endl;
    // for (int i = 0; i < n; i++)
    //     cout << h[i] << " ";
    for (int i = 0; i < n - m + 1; i++) {
        int j = i + m - 1;
        int h_i_j = h[j];
        if (i > 0) 
            h_i_j -= h[i - 1];
        if (h_i_j == h_t * p[i])
            cout << i << " ";
    }
    return 0;
}