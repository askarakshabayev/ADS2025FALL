#include <iostream>

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

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    cout << get_hash(s1) << " " << get_hash(s2) << " " << (get_hash(s1) == get_hash(s2));
    return 0;
}