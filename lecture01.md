# Lecture 1: Course Introduction

## Course Overview
- Syllabus, covered topics, laboratory works
- Midterm, endterm, final examinations
- Ejudge.kz system, github, defence rules
- Labs - practice lessons to help solving labs


## Course Topics by Lecture

### Lecture 1: Complexity and Memory
- GCD, Binary Exponentiation
- Sieve of Eratosthenes
- Prime factorization
- Stack
- Queue
- Deque

### Lecture 2: Data Structures
- Stack
- Queue
- Deque
- Linked lists
- Doubly-Linked lists

### Lecture 3: Search Algorithms
- Binary search

### Lecture 4: Tree Structures
- Binary search tree

### Lecture 5: Priority Structures
- Priority queues, Heap

### Lecture 6: Sorting Algorithms I
- Heap sort
- Quick Sort

### Lecture 7: Sorting Algorithms II
- Merge sort
- **Midterm**

### Lecture 8: Hash Tables
- Hash tables
- Rabin-Karp algorithm based on hash calculation

### Lecture 9: String Algorithms
- Knuth-Morris-Pratt algorithm

### Lecture 10: Graph Representation and BFS
- Adjacency list and matrix
- Edge list
- BFS

### Lecture 11: Graph Traversal and Sorting
- DFS
- Topological Sort

### Lecture 12: Spanning Tree Algorithms
- Kruskal algorithm
- Prim algorithm

### Lecture 13: Shortest Path Algorithms
- Dijkstra
- Floyd-Warshall
- Bellman-Ford

## Laboratory Works

Access the laboratory assignments through the following links:

- [Lab 1](http://ejudge.kz/new-client?contest_id=201)
- [Lab 2](http://ejudge.kz/new-client?contest_id=202)
- [Lab 3](http://ejudge.kz/new-client?contest_id=203)
- [Lab 4](http://ejudge.kz/new-client?contest_id=204)
- [Lab 5](http://ejudge.kz/new-client?contest_id=205)
- [Lab 6](http://ejudge.kz/new-client?contest_id=206)
- [Lab 7](http://ejudge.kz/new-client?contest_id=207)
- [Lab 8](http://ejudge.kz/new-client?contest_id=208)
- [Lab 9](http://ejudge.kz/new-client?contest_id=209)
- [Lab 10](http://ejudge.kz/new-client?contest_id=210)
- [Lab 11](http://ejudge.kz/new-client?contest_id=211)
- [Lab 12](http://ejudge.kz/new-client?contest_id=212)

### Login Instructions

**For Students:**
- **Login:** `ADS25_[STUDENT_ID]`
- **Password:** `[STUDENT_ID]`

**Example:**
If your student ID is `09FSXX019`:
- Login: `ADS25_09FSXX019`
- Password: `09FSXX019`

## Assessment Structure

### Laboratory Works
- Each lab = 1 point
- 12 labs total

### Quizzes
- 4 quizzes throughout the semester
- Each quiz = 12 points
- Schedule: weeks 4, 8, 12, 16
- One quiz will be a contest format

**Quiz Format** *(Not finalized):*
- 12 Multiple Choice questions = 6 points
- 2 Open questions = 3 points  
- 2 Code questions = 3 points

## Lecture 1 Details: Complexity and Memory

### Greatest Common Divisor (GCD)

**Simple solution and why we need more effective algorithms like Euclidean Algorithm**

**Problem:** Find the largest positive integer that divides both numbers a and b.

**Naive Approach:**
- Check all numbers from min(a,b) down to 1
- Time complexity: O(min(a,b))
- Inefficient for large numbers

**Example:** 
- For small numbers like GCD(12, 18): works fine, checks 12 numbers maximum
- For large prime numbers like GCD(1000000007, 1000000009): would need to check ~1 billion numbers!
- With large numbers, this approach will take an extremely long time to calculate

**Euclidean Algorithm - The Elegant Solution:**
- GCD(a, b) = GCD(b, a mod b)  if b ≠ 0
- GCD(a, 0) = a

**Implementation:**

```cpp
#include <iostream>

using namespace std;

int gcd(int a, int b) {
    for (int i = min(a, b); i >= 1; --i) {
        if (a % i == 0 && b % i == 0) {
            return i;
        }
    }
    return 1;
}

int gcd2(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd2(b, a % b);
}

// Iterative version
int gcd1(int a, int b) {
    while (a > 0 && b > 0) {
        if (a > b)
            a = a % b;
        else
            b = b % a;        
    }

    // if (a > 0)
    //     return b;
    // return a;
    return a + b;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << gcd2(a, b) << endl;
    return 0;
}
```

### Binary Exponentiation (Binpow)

**Problem:** Calculate a^n efficiently

**Naive Approach:**
- Multiply a by itself n times
- Time complexity: O(n)
- Inefficient for large exponents

**Binary Exponentiation - The Efficient Solution:**
- Based on the property: a<sup>n</sup> = (a<sup>n/2</sup>)<sup>2</sup> if n is even
- If n is odd: a<sup>n</sup> = a × a<sup>n-1</sup>
- Time complexity: O(log n)

**Algorithm:**
1. If n = 0, return 1
2. If n is even: result = (a<sup>n/2</sup>)<sup>2</sup>
3. If n is odd: result = a × a<sup>n-1</sup>
4. Use recursion or iteration

**Example:** Calculate 2<sup>10</sup>
- 2<sup>10</sup> = (2<sup>5</sup>)<sup>2</sup> = (2 × 2<sup>4</sup>)<sup>2</sup> = (2 × (2<sup>2</sup>)<sup>2</sup>)<sup>2</sup> = (2 × 4<sup>2</sup>)<sup>2</sup> = (2 × 16)<sup>2</sup> = 32<sup>2</sup> = 1024
- Only 4 multiplications instead of 10!

**Implementation:**

```cpp
// Recursive version
long long binpow(long long a, long long n) {
    if (n == 0)
        return 1;
    if (n % 2 == 0) {
        long long half = binpow(a, n / 2);
        return half * half;
    } else {
        return a * binpow(a, n - 1);
    }
}

// Iterative version
long long binpow_iter(long long a, long long n) {
    long long result = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            result *= a;
        }
        a *= a;
        n /= 2;
    }
    return result;
}

// Example usage
int main() {
    long long base, exp;
    cin >> base >> exp;
    cout << "Result: " << binpow(base, exp) << endl;
    cout << "Result (iterative): " << binpow_iter(base, exp) << endl;
    return 0;
}
```

### Prime Numbers - Sieve of Eratosthenes

**Problem:** Find all prime numbers up to n efficiently.

**Naive Approach:**
- Check each number for primality individually  
- Time complexity: O(n√n)

**Sieve of Eratosthenes - The Ancient Optimization:**

**Example:** Finding primes up to 30
1. Start with [2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30]
2. Cross out multiples of 2: [2,3,5,7,9,11,13,15,17,19,21,23,25,27,29]  
3. Cross out multiples of 3: [2,3,5,7,11,13,17,19,23,25,29]
4. Continue...
5. Result: [2,3,5,7,11,13,17,19,23,29]

**Complexity:**
- Time Complexity: O(n log log n) - much better than naive approach!
- Space Complexity: O(n)

**Algorithm:**
1. Create boolean array is_prime[0..n], initialize all as true
2. Set is_prime[0] = is_prime[1] = false  
3. For each number i from 2 to √n:
   - If is_prime[i] is true:
     - Mark all multiples of i (starting from i²) as false
4. Remaining true values are primes

### Prime Factorization

**Prime factorization** is the process of breaking a number into a product of prime numbers.

**Examples:**
- 60 = 2 × 2 × 3 × 5
  - Explanation: 60 ÷ 2 = 30 → ÷ 2 = 15 → ÷ 3 = 5 → prime.
- 210 = 2 × 3 × 5 × 7
  - Explanation: Sequentially divide by primes until 1.

**Basic Implementation:**

```cpp
#include <iostream>
using namespace std;

void primeFactorization(int n) {
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }
    }
    if (n > 1) cout << n; // remaining prime
    cout << endl;
}

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;
    cout << "Prime factors: ";
    primeFactorization(num);
    return 0;
}
```

**Worst case:** O(√n) (trial division).

**Faster methods:** Sieve of Eratosthenes + precomputed primes

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Generate primes up to limit using Sieve of Eratosthenes
vector<int> sieve(int limit) {
    vector<bool> isPrime(limit + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }

    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) primes.push_back(i);
    }
    return primes;
}

// Prime factorization using precomputed primes
void primeFactorization(int n, const vector<int>& primes) {
    int temp = n;
    for (int p : primes) {
        if (p * p > n) break; // stop when p > sqrt(n)
        while (n % p == 0) {
            cout << p << " ";
            n /= p;
        }
    }
    if (n > 1) cout << n; // remaining prime factor
    cout << endl;
}

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    // Precompute primes up to sqrt(num)
    int limit = (int)(sqrt(num)) + 1;
    vector<int> primes = sieve(limit);

    cout << "Prime factors of " << num << ": ";
    primeFactorization(num, primes);

    return 0;
}
```

**Efficiency:**
- Sieve: O(n log log n) (once).
- Factorization: O(π(√n)), where π(x) is number of primes ≤ √n (much fewer than √n divisions).

## Time Complexity and Memory

**Why complexity matters:**
- Sorting 10 numbers → both good and bad algorithms finish instantly.
- Sorting 10 million numbers → slow algorithms take hours, fast ones finish in seconds.
- We use complexity analysis to predict how runtime and memory grow as n increases.

**Big-O** describes the upper bound on the growth rate — how fast runtime or memory usage can grow in the worst case.

**Key principles:**
- Ignore constant factors (doesn't matter if it's 2n or 5n, it's still O(n))
- Ignore less significant terms (e.g., n² + n → O(n²) because n² dominates for large n)

### Common Time Complexities:

| Complexity | Name | Example |
|------------|------|---------|
| O(1) | Constant | Access array element |
| O(log n) | Logarithmic | Binary search |
| O(n) | Linear | Loop over array |
| O(n log n) | Linearithmic | Merge sort, quicksort average |
| O(n²) | Quadratic | Nested loops |
| O(2ⁿ) | Exponential | Naive Fibonacci recursion |
| O(n!) | Factorial | Traveling Salesman brute force |

**Example of O(2ⁿ) - Very inefficient:**
```cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2); // Very slow for large n
}
```

### Space (Memory) Complexity

Memory complexity measures extra memory your algorithm needs beyond the input.

- **O(1)** → constant extra space (variables, counters)
- **O(n)** → needs memory proportional to n (arrays, hashmaps)
- **O(n²)** → large 2D matrices, graph adjacency matrices

### Practical Takeaways

- **Time complexity** tells you how fast runtime grows.
- **Space complexity** tells you how much extra memory grows.
- Use Big-O for worst-case analysis, but know there's also:
  - **Big-Θ (Theta)** → tight bound (exact growth rate)
  - **Big-Ω (Omega)** → best case bound.

**For competitive programming and large-scale apps, aim for:**
- Sorting: O(n log n)
- Searching: O(log n) or better
- Graph: BFS/DFS O(V+E)
- Precomputation (like a sieve) can trade memory for speed.

## Linear Data Structures

### Stack - LIFO (Last In, First Out)

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

**Node Implementation:**

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

**Template Node:**

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

### Queue - FIFO (First In, First Out)

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

### Deque - Double-Ended Queue

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

### Problem: Minimum Operations to Transform Number

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

### Problem: Knight's Shortest Path on Chessboard

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

### Linked List

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
```
