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
