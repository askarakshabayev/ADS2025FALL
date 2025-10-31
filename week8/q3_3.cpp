#include <iostream>
#include <queue>

using namespace std;
queue<int> q;

int main() {
    int n, x;
    string s;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s == "arrive") {
            cin >> x;
            q.push(x);
        }
        if (s == "serve") {
            if (q.empty() == false) {
                cout << q.front() << endl;
                q.pop();
            } else 
                cout << "error" << endl;
        }
        if (s == "first") {
            if (!q.empty()) 
                cout << q.front() << endl;
            else
                cout << "error" << endl;
        }
        if (s == "size") 
            cout << q.size() << endl;
        if (s == "empty") {
            if (q.empty())
                cout << 1 << endl;
            else 
                cout << 0 << endl;
        }
        if (s == "reset")
            while (q.empty() == false)
                q.pop();

    }
    return 0;
}