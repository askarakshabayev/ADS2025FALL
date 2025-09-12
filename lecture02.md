# Lecture 2: Linear Data Structures

## Node Implementation

**Basic Node Structure:**

```cpp
#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node *next;

    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};
```

**Template Node for Generic Types:**

```cpp
template<typename T>
class Node {
    public:
    T data;
    Node<T> *next;

    Node(T data) {
        this->data = data;
        this->next = NULL;
    }
};

int main() {
    Node<string> *n1 = new Node<string>("hello");
    Node<string> *n2 = new Node<string>("world");
    Node<string> *n3 = new Node<string>("test");
    n1->next = n2;
    n2->next = n3;
    cout << n1->next->next->data;
    return 0;
}
```

## Stack - LIFO (Last In, First Out)

**Concept:** Think of a stack of plates - you can only add or remove from the top.

**Core Operations:**
- `push(item)` - add item to top - O(1)
- `pop()` - remove and return top item - O(1)
- `top()/peek()` - view top item without removing - O(1)
- `empty()` - check if stack is empty - O(1)
- `size()` - get number of elements - O(1)

**C++ Implementation using STL:**

```cpp
// C++ built-in stack
#include <iostream>
#include <stack>
using namespace std;

int main() {
   stack<int> st;
   st.push(10);
   st.push(20);
   st.push(15);
   st.push(1);

   cout << st.top() << endl; // 1
   st.pop();
   st.pop();
   cout << st.top() << endl; // 20
   cout << st.size() << endl;
   cout << st.empty();
   return 0;
}
```

**Custom Stack Implementation:**

```cpp
class Stack {
    public:
    Node *top;
    int sz;

    Stack() {
        top = NULL;
        sz = 0;
    }

    void push(int data) {
        Node *node = new Node(data);
        node->next = top;
        top = node;
        sz++;
    }

    void pop() {
        if (top != NULL) {
            top = top->next;
            sz--;
        }
    }

    int size() {
        return this->sz;
    }

    bool empty() {
        return (sz == 0);
    }
};
```

### Stack Problems

**Simple Problem: Basic Parentheses Balance**
Check if only `()` brackets are properly balanced.

**Try solving without stack first:**

```cpp
#include <iostream>
using namespace std;

// Simple counter approach - works only for () brackets
bool simple_balance(string s) {
    int counter = 0;
    
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            counter++;
        } else if (s[i] == ')') {
            counter--;
            // If counter goes negative, we have ')' before '('
            if (counter < 0) {
                return false;
            }
        }
    }
    
    // Should end with counter = 0
    return (counter == 0);
}

int main() {
    string s;
    cin >> s;
    if (simple_balance(s))
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
```

**Examples:**
- "()" → True
- "(())" → True  
- "(((" → False
- ")))" → False
- "()(" → False

**Why this approach fails for multiple bracket types?**
- Counter can't distinguish between different bracket types
- "(]" would incorrectly return true with counter approach
- We need to remember which opening bracket we saw

**Classic Problem: Balanced Brackets**
Check if brackets are properly balanced: (), [], {}

```cpp
#include <iostream>
#include <stack>
using namespace std;

bool is_ok(string s) {
    stack<char> st;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            st.push(s[i]);
        else {
            if (st.empty())
                return false;
            if (s[i] == '}' && st.top() != '{')
                return false;
            if (s[i] == ']' && st.top() != '[')
                return false;
            if (s[i] == ')' && st.top() != '(')
                return false;
            st.pop();                
        }
    }
    return (st.empty());
}

int main() {
    string s;
    cin >> s;
    if (is_ok(s))
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
```

**Examples:**
- "()" → True
- "([{}])" → True
- "([)]" → False
- "(((" → False

**Applications:** Function call management, expression evaluation, undo operations, browser history

## Queue - FIFO (First In, First Out)

**Concept:** Like a line at a store - first person in line is first to be served.

**Core Operations:**
- `push()/enqueue(item)` - add item to rear - O(1)
- `pop()/dequeue()` - remove front item - O(1)
- `front()` - view front item without removing - O(1)
- `empty()` - check if queue is empty - O(1)
- `size()` - get number of elements - O(1)

**C++ Implementation using STL:**

```cpp
#include <queue>
#include <iostream>
using namespace std;

void demo_stl_queue() {
    queue<int> q;
    
    // Add elements
    q.push(10);
    q.push(20);
    q.push(30);
    
    cout << "Queue size: " << q.size() << endl;
    cout << "Front element: " << q.front() << endl;
    
    // Remove elements
    while (!q.empty()) {
        cout << "Removing: " << q.front() << endl;
        q.pop();
    }
}
```

**Applications:**
- Task scheduling in operating systems
- Breadth-First Search (BFS) in graphs
- Print job management
- Buffer for data streams

## Deque - Double-Ended Queue

**Concept:** Combination of stack and queue - can add/remove from both ends efficiently.

**Core Operations:**
- `push_back(item)` - add item to back - O(1)
- `push_front(item)` - add item to front - O(1)
- `pop_back()` - remove back item - O(1)
- `pop_front()` - remove front item - O(1)

```cpp
deque<int> q;
q.push_back(10); 
q.push_back(20);
q.push_front(30);
q.push_front(40);
```

## Problem: Minimum Operations to Transform Number

**Problem Statement:** Given two positive integers a and b, find the minimum number of operations needed to transform a into b using the following allowed operations:
- Add 1: x → x + 1
- Multiply by 2: x → x * 2
- Divide by 2: x → x / 2 (integer division)
- Subtract 1: x → x - 1 (if result ≥ 0)

**Example:**
Input: a = 2, b = 12
Output: 3 operations
Path: 2 → 3 → 6 → 12

**Algorithm:** Uses BFS to guarantee minimum operations

```cpp
#include <iostream>
#include <queue>
using namespace std;

queue<pair<int, int> > q;
int used[1000]; 

int f(int a, int b) {
    q.push(make_pair(a, 0));
    used[a] = a;

    while (!q.empty()) {
        int x = q.front().first;
        int d = q.front().second;

        if (x == b) {
            return d;
        }

        if (used[x + 1] == 0) {
            q.push(make_pair(x + 1, d + 1));
            used[x + 1] = x;
        }

        if (used[x * 2] == 0) {
            q.push(make_pair(x * 2, d + 1));
            used[x * 2] = x;
        }

        if (used[x / 2] == 0) {
            q.push(make_pair(x / 2, d + 1));
            used[x / 2] = x;
        }

        if (x - 1 >= 0 && used[x - 1] == 0) {
            q.push(make_pair(x - 1, d + 1));
            used[x - 1] = x;
        }
        q.pop();
    }
    return 0;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << f(a, b) << endl;

    vector<int> result;
    result.push_back(b);
    int t = b;
    while (used[t] != t) {
        t = used[t];
        result.push_back(t);
    }

    for (int i = result.size() - 1; i >= 0; i--)
        cout << result[i] << " ";

    return 0;
}
```

## Problem: Knight's Shortest Path on Chessboard

**Problem Statement:** Given a standard 8×8 chessboard, find the minimum number of moves for a knight to travel from position (x1, y1) to position (x2, y2).

```cpp
#include <iostream>
#include <queue>
using namespace std;

int a[10][10];
pair<int, int> c[10][10];
queue<pair<int, int> > q;

int dx[8] = {2,  2, -2, -2,  1, 1, -1, -1};
int dy[8] = {1, -1,  1, -1, -2, 2, -2,  2};

bool check(int x, int y) {
    return (x >= 1 && x <= 8 && y >= 1 && y <= 8 && a[x][y] == 0);
}

int main() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    a[x1][y1] = 1;
    q.push(make_pair(x1, y1));
    c[x1][y1] = make_pair(x1, y1);

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;

        for (int i = 0; i < 8; i++) {
            if (check(x + dx[i], y + dy[i])) {
                q.push(make_pair(x + dx[i], y + dy[i]));
                a[x + dx[i]][y + dy[i]] = a[x][y] + 1;
                c[x + dx[i]][y + dy[i]] = make_pair(x, y);
            }
        }
        q.pop();
    }

    cout << a[x2][y2] - 1 << endl;

    vector<pair<int, int> > result;
    result.push_back(make_pair(x2, y2));
    int x = x2;
    int y = y2;
    while (c[x][y] != make_pair(x, y)) {
        int x_temp = c[x][y].first;
        int y_temp = c[x][y].second; 
        result.push_back(make_pair(x_temp, y_temp));
        x = x_temp;
        y = y_temp;
    }

    for (int i = result.size() - 1; i >= 0; i--)
        cout << result[i].first << " " << result[i].second << endl;
    return 0;
}
```

## Linked List

**Doubly Linked List Implementation:**

```cpp
#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node *next, *prev;

    Node(int data) {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};

class LinkedList {
    public:
    Node *tail, *front;
    
    LinkedList() {
        tail = NULL;
        front = NULL;
    }

    void push_back(int data) {
        Node *node = new Node(data);
        if (tail == NULL) {
            tail = node;
            front = node;
        } else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
    }

    void push_front(int data) {
        Node *node = new Node(data);
        if (front == NULL) {
            tail = node;
            front = node;
        } else {
            front->prev = node;
            node->next = front;
            front = node;
        }
    }

    void pop_back() {
        if (tail != NULL) {
            tail = tail->prev;
            if (tail != NULL)
                tail->next = NULL;
            else 
                front = NULL;
        }
    }

    void pop_front() {
        if (front != NULL) {
            front = front->next;
            if (front != NULL)
                front->prev = NULL;
            else
                tail = NULL;
        }
    }

    void del_node(Node *node) {
        if (node == tail)
            pop_back();
        else if (node == front) 
            pop_front();
        else {
            Node *a = node->prev;
            Node *b = node->next;
            a->next = b;
            b->prev = a;
        }
    }

    void print() {
        Node *node = front;
        while (node != NULL) {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }

    Node* find_node(int data) {
        Node *node = front;
        while (node != NULL) {
            if (node->data == data)
                return node;
            node = node->next; 
        }
        return NULL;
    }

    void insert_node(Node *node1, int data) {
        Node *node = new Node(data);
        if (node1 == tail) 
            push_back(data);
        else {
            Node *node2 = node1->next;
            node1->next = node;
            node->prev = node1;
            node->next = node2;
            node2->prev = node;
        }
    }
};

int main() {
    LinkedList *ll = new LinkedList();
    ll->push_back(5);
    ll->push_back(6);
    ll->push_back(7);
    ll->push_back(8);
    ll->push_back(9);
    ll->push_back(10);
    ll->push_front(11);
    ll->push_front(12);
    ll->push_front(13);
    ll->push_front(14);
    ll->push_front(15);
    ll->print();
    cout << ll->front->data << " " << ll->tail->data << endl;
    ll->pop_back(); 
    ll->pop_back();
    ll->pop_front(); 
    ll->pop_front();
    ll->print();
    cout << ll->front->data << " " << ll->tail->data << endl;

    Node *node = ll->find_node(11);
    if (node != NULL) {
        ll->del_node(node);
    }

    ll->print();

    node = ll->find_node(6);
    ll->insert_node(node, 100);
    ll->print();
    return 0;
}
```

## Data Structures Summary

| Data Structure | Access | Insert | Delete | Search | Space |
|----------------|--------|--------|---------|--------|-------|
| **Stack** | O(1) top only | O(1) | O(1) | O(n) | O(n) |
| **Queue** | O(1) front/rear | O(1) | O(1) | O(n) | O(n) |
| **Deque** | O(1) both ends | O(1) | O(1) | O(n) | O(n) |
| **Linked List** | O(n) | O(1) with pointer | O(1) with pointer | O(n) | O(n) |

## Key Takeaways

1. **Choose the right data structure** based on your access patterns
2. **Stack**: Use when you need LIFO behavior (undo operations, function calls)
3. **Queue**: Use when you need FIFO behavior (BFS, task scheduling)
4. **Deque**: Use when you need both stack and queue operations
5. **Linked List**: Use when frequent insertions/deletions and dynamic size is important
6. **Understanding pointers and memory management** is crucial for implementing these structures