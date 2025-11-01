#include <iostream>
#include <queue>

using namespace std;
int n, x;

int main() {
    cin >> n;
    string s;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s == "arrive") {
            cin >> x;
            q.push(x);
        }
        if (s == "serve") {
            if (q.empty())
                cout << "error" << endl;
            else {
                cout << q.front() << endl;
                q.pop();
            }
        }
        if (s == "first") {
            if (q.empty())
                cout << "error" << endl;
            else 
                cout << q.front() << endl;
        }
        if (s == "size")
            cout << q.size() << endl;
        if (s == "empty") {
            if (q.empty())
                cout << 1 << endl;
            else 
                cout << 0 << endl;
        }
        if (s == "reset") {
            //q = queue<int>();
            while (q.empty() == false)
                q.pop();
        }
    }
    return 0;
}