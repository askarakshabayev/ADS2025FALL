#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int n, x;
    stack<int> st;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (st.empty() || (st.top() + x) % 2 != 0)
            st.push(x);
        else    
            st.pop();
    }
    vector<int> a;
    while (!st.empty()) {
        a.push_back(st.top());
        st.pop();
    }
    cout << a.size() << endl;
    for (int i = a.size() - 1; i >= 0; i--)
        cout << a[i] << " ";
    return 0;
}