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
