# Lecture 8: Hashing and Rabin-Karp Algorithm

## Introduction to Hashing

**Hashing** is a technique to convert data (strings, numbers, objects) into a fixed-size numerical value called a **hash value** or **hash code**. This hash value acts as a unique "fingerprint" for the data.

### What is a Hash Function?

A **hash function** takes an input (string, number, etc.) and produces a numerical value:

```
hash("hello") → 99162322
hash("world") → 113318802
hash("abc")   → 96354
```

### Properties of Good Hash Functions

1. **Deterministic**: Same input always produces same output
2. **Fast to compute**: O(n) for string of length n
3. **Uniform distribution**: Hash values spread evenly
4. **Minimizes collisions**: Different inputs should produce different hashes (ideally)

### Why Do We Need Hashing?

**Without hashing:**
- Comparing two strings: O(n) - need to check each character
- Finding duplicates in array of strings: O(n² × m) where m is string length

**With hashing:**
- Compare hash values: O(1) - just compare integers
- Finding duplicates: O(n × m) - compute hash once per string

### Basic Hash Function for Strings

**Polynomial Rolling Hash:**

For string s = "abc":
```
hash(s) = s[0] × p^0 + s[1] × p^1 + s[2] × p^2 + ...
```

Where:
- `p` is a prime number (commonly 29 or 31 for lowercase letters)
- `s[i]` is the ASCII value of character at position i

**Example:** hash("abc") with p = 29
```
hash = 'a' × 29^0 + 'b' × 29^1 + 'c' × 29^2
     = 97 × 1 + 98 × 29 + 99 × 841
     = 97 + 2842 + 83259
     = 86198
```

### Simple Hash Implementation

```cpp
#include <iostream>
using namespace std;

int get_hash(string s) {
    int p = 29;
    int p_pow = 1;  // p^0
    int h = 0;

    for (int i = 0; i < s.size(); i++) {
        h += s[i] * p_pow;
        p_pow *= p;
    }

    return h;
}

int main() {
    cout << "hash('abc') = " << get_hash("abc") << endl;
    cout << "hash('hello') = " << get_hash("hello") << endl;
    cout << "hash('world') = " << get_hash("world") << endl;

    return 0;
}
```

## Problem 1: Finding Identical Strings

### Problem Statement

Given an array of n strings, find all pairs of identical strings.

### Naive Solution - O(n² × m)

```cpp
// Compare each pair of strings
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        if (strings[i] == strings[j]) {  // O(m) comparison
            cout << i << " " << j << endl;
        }
    }
}

// Time Complexity: O(n² × m)
// where n = number of strings, m = average string length
```

### Improved Solution with Hashing - O(n × m)

**Idea:**
1. Compute hash for each string - O(m) per string
2. Store hashes in map/array
3. Compare hash values instead of strings - O(1)

```cpp
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int get_hash(string s) {
    int p = 29;
    int p_pow = 1;
    int h = 0;
    for (int i = 0; i < s.size(); i++) {
        h += s[i] * p_pow;
        p_pow *= p;
    }
    return h;
}

int main() {
    int n;
    cin >> n;

    vector<string> strings(n);
    map<int, vector<int>> hash_map;  // hash -> indices

    // Compute hash for each string and group by hash
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
        int h = get_hash(strings[i]);
        hash_map[h].push_back(i);
    }

    // Find pairs with same hash
    cout << "Identical string pairs:" << endl;
    for (auto& pair : hash_map) {
        vector<int>& indices = pair.second;
        // All strings with same hash are potentially identical
        for (int i = 0; i < indices.size(); i++) {
            for (int j = i + 1; j < indices.size(); j++) {
                // Double-check actual strings to avoid hash collisions
                if (strings[indices[i]] == strings[indices[j]]) {
                    cout << indices[i] << " " << indices[j] << endl;
                }
            }
        }
    }

    return 0;
}
```

**Example:**
```
Input:
5
hello
world
hello
test
world

Output:
Identical string pairs:
0 2    (both "hello")
1 4    (both "world")
```

**Time Complexity:** O(n × m)
- Computing hashes: O(n × m)
- Grouping by hash: O(n)
- Finding pairs: O(n) if no collisions

**Improvement:** Instead of O(n² × m), we get O(n × m) - much faster!

## Prefix Hash Array - Fast Substring Hash

### The Problem

If we need to compute hashes of many substrings of a string, computing each hash from scratch is slow:
- For string of length n, there are O(n²) substrings
- Computing each hash takes O(m) time
- Total: O(n³) - too slow!

### Solution: Prefix Hash Array

**Key Idea:** Precompute prefix hashes to get any substring hash in O(1)!

**Prefix hash array** `h[i]` = hash of substring s[0...i]

```
h[i] = s[0] × p^0 + s[1] × p^1 + ... + s[i] × p^i
```

### Computing Prefix Hashes

```cpp
vector<int> get_h(string s) {
    int n = s.size();
    vector<int> h(n);

    h[0] = s[0];          // First character
    int p = 29;
    int p_pow = 29;       // p^1

    for (int i = 1; i < n; i++) {
        h[i] = h[i - 1] + s[i] * p_pow;
        p_pow *= p;
    }

    return h;
}
```

**Example:** s = "abcd"
```
h[0] = 'a' × p^0 = 97
h[1] = 'a' × p^0 + 'b' × p^1 = 97 + 98×29 = 2939
h[2] = 'a' × p^0 + 'b' × p^1 + 'c' × p^2 = 2939 + 99×841 = 86238
h[3] = 'a' × p^0 + 'b' × p^1 + 'c' × p^2 + 'd' × p^3 = ...
```

### Getting Hash of Any Substring

To get hash of substring s[l...r]:

```cpp
hash(s[l...r]) = (h[r] - h[l-1]) / p^l
```

But we can't divide! So we multiply the other side:
```cpp
hash(s[l...r]) × p^l = h[r] - h[l-1]
```

**Implementation:**
```cpp
// Precompute powers of p
vector<int> p(n);
p[0] = 1;
for (int i = 1; i < n; i++)
    p[i] = p[i - 1] * 29;

// Get hash of substring [l, r]
int substring_hash(int l, int r) {
    int hash = h[r];
    if (l > 0)
        hash = hash - h[l - 1];
    return hash;  // This equals original_hash × p^l
}
```

## Rabin-Karp Algorithm: Pattern Matching

### Problem Statement

Given:
- Text string `s1` (length n)
- Pattern string `s2` (length m)

Find all occurrences of `s2` in `s1`.

### Naive Approach - O(n × m)

```cpp
for (int i = 0; i <= n - m; i++) {
    bool match = true;
    for (int j = 0; j < m; j++) {
        if (s1[i + j] != s2[j]) {
            match = false;
            break;
        }
    }
    if (match)
        cout << "Found at position " << i << endl;
}
```

### Rabin-Karp Algorithm - O(n + m)

**Idea:**
1. Compute hash of pattern `s2`
2. Compute prefix hashes of text `s1`
3. For each position i, compare hash of substring with pattern hash
4. Only compare actual strings if hashes match (to handle collisions)

### Complete Implementation

```cpp
#include <iostream>
#include <vector>

using namespace std;

// Compute hash of entire string
int get_hash(string s) {
    int p = 29;
    int p_pow = 1;  // p^0
    int h = 0;

    for (int i = 0; i < s.size(); i++) {
        h += s[i] * p_pow;
        p_pow *= p;
    }

    return h;
}

// Compute prefix hash array
vector<int> get_h(string s) {
    int n = s.size();
    vector<int> h(n);

    h[0] = s[0];
    int p = 29;
    int p_pow = 29;  // p^1

    for (int i = 1; i < n; i++) {
        h[i] = h[i - 1] + s[i] * p_pow;
        p_pow *= p;
    }

    return h;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    // Precompute powers of p
    vector<int> p(s1.size());
    p[0] = 1;
    for (int i = 1; i < s1.size(); i++)
        p[i] = p[i - 1] * 29;

    // Hash of pattern
    int h_s2 = get_hash(s2);

    // Prefix hashes of text
    vector<int> h = get_h(s1);

    int n = s1.size();
    int m = s2.size();

    // Find all occurrences
    for (int i = 0; i < n - m + 1; i++) {
        int j = i + m - 1;  // End of current window

        // Get hash of substring s1[i...j]
        int hash = h[j];
        if (i > 0)
            hash = hash - h[i - 1];

        // Compare with pattern hash
        // hash = actual_hash × p^i, so compare with h_s2 × p^i
        if (hash == h_s2 * p[i])
            cout << i << " ";
    }

    return 0;
}
```

### Example Trace

**Input:**
```
s1 = "ababcab"
s2 = "ab"
```

**Step 1:** Compute h_s2 (hash of "ab")
```
h_s2 = 'a' × 29^0 + 'b' × 29^1
     = 97 × 1 + 98 × 29
     = 97 + 2842
     = 2939
```

**Step 2:** Compute prefix hashes of s1
```
h[0] = 97              (hash of "a")
h[1] = 2939            (hash of "ab")
h[2] = 86238           (hash of "aba")
h[3] = 2499954         (hash of "abab")
...
```

**Step 3:** Check each position
```
Position 0: substring "ab"
  hash = h[1] = 2939
  h_s2 × p[0] = 2939 × 1 = 2939
  Match! Output: 0

Position 1: substring "ba"
  hash = h[2] - h[0] = 86238 - 97 = 86141
  h_s2 × p[1] = 2939 × 29 = 85231
  No match

Position 2: substring "ab"
  hash = h[3] - h[1] = 2499954 - 2939 = 2497015
  h_s2 × p[2] = 2939 × 841 = 2471699
  Match! Output: 2
...
```

**Output:** `0 2 5` (positions where "ab" occurs)

### Time Complexity

| Operation | Time |
|-----------|------|
| Compute h_s2 | O(m) |
| Compute prefix hashes | O(n) |
| Precompute powers | O(n) |
| Check all positions | O(n) |
| **Total** | **O(n + m)** |

**Much better than naive O(n × m)!**

## Problem 2: Count Distinct Substrings

### Problem Statement

Given a string of length n, count the number of distinct substrings.

### Naive Solution - O(n³)

```cpp
set<string> distinct;
for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
        string sub = s.substr(i, j - i + 1);  // O(n)
        distinct.insert(sub);  // O(n log n) for set insertion
    }
}
cout << distinct.size() << endl;

// Time: O(n² × n) = O(n³)
```

### Improved Solution with Hashing - O(n² log n)

**Idea:** Use hash values instead of actual substrings!

```cpp
#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<long long> get_h(string s) {
    int n = s.size();
    vector<long long> h(n);

    h[0] = s[0];
    long long p = 29;
    long long p_pow = 29;

    for (int i = 1; i < n; i++) {
        h[i] = h[i - 1] + s[i] * p_pow;
        p_pow *= p;
    }

    return h;
}

int main() {
    string s;
    cin >> s;

    int n = s.size();

    // Precompute powers
    vector<long long> p(n);
    p[0] = 1;
    for (int i = 1; i < n; i++)
        p[i] = p[i - 1] * 29;

    // Compute prefix hashes
    vector<long long> h = get_h(s);

    // Use set to store unique hashes
    set<long long> distinct_hashes;

    // Generate all substrings
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Hash of substring [i, j]
            long long hash = h[j];
            if (i > 0)
                hash = hash - h[i - 1];

            distinct_hashes.insert(hash);  // O(log n)
        }
    }

    cout << "Number of distinct substrings: ";
    cout << distinct_hashes.size() << endl;

    return 0;
}
```

### Time Complexity Analysis

| Operation | Time |
|-----------|------|
| Compute prefix hashes | O(n) |
| Generate all substrings | O(n²) |
| Insert into set | O(log n) per insertion |
| **Total** | **O(n² log n)** |

**Improvement:** From O(n³) to O(n² log n)!

### Example

**Input:** s = "abab"

**All substrings:**
```
Length 1: a, b, a, b         → 2 distinct (a, b)
Length 2: ab, ba, ab         → 2 distinct (ab, ba)
Length 3: aba, bab           → 2 distinct (aba, bab)
Length 4: abab               → 1 distinct (abab)

Total distinct: 7
```

**With hashing:**
```cpp
Substrings and their hashes:
"a"    → hash1
"b"    → hash2
"a"    → hash1  (duplicate)
"b"    → hash2  (duplicate)
"ab"   → hash3
"ba"   → hash4
"ab"   → hash3  (duplicate)
"aba"  → hash5
"bab"  → hash6
"abab" → hash7

Set contains: {hash1, hash2, hash3, hash4, hash5, hash6, hash7}
Count = 7
```

## Hash Collisions

### What is a Collision?

A **collision** occurs when two different strings produce the same hash value.

```cpp
hash("abc") == hash("xyz")  // Collision!
```

### Why Do Collisions Happen?

- Hash values are integers (finite range)
- Strings are infinite in variety
- By **Pigeonhole Principle**, collisions are inevitable

### Handling Collisions

**1. Use larger hash values (long long, unsigned long long)**
```cpp
unsigned long long get_hash(string s) {
    unsigned long long p = 29;
    unsigned long long p_pow = 1;
    unsigned long long h = 0;
    for (int i = 0; i < s.size(); i++) {
        h += s[i] * p_pow;
        p_pow *= p;
    }
    return h;
}
```

**2. Use modulo with large prime**
```cpp
const long long MOD = 1e9 + 7;  // Large prime

int get_hash(string s) {
    long long h = 0;
    long long p_pow = 1;
    long long p = 29;

    for (int i = 0; i < s.size(); i++) {
        h = (h + s[i] * p_pow) % MOD;
        p_pow = (p_pow * p) % MOD;
    }

    return h;
}
```

**3. Double hashing (use two different hash functions)**
```cpp
pair<int, int> double_hash(string s) {
    int h1 = get_hash(s, 29, MOD1);
    int h2 = get_hash(s, 31, MOD2);
    return {h1, h2};
}
```

**4. Verify with actual string comparison when hashes match**
```cpp
if (hash1 == hash2) {
    // Don't assume strings are equal!
    if (s1 == s2) {
        // Actually equal
    }
}
```

## Applications of Hashing

### 1. Pattern Matching (Rabin-Karp)
- Find substring in text - O(n + m)
- Find multiple patterns simultaneously

### 2. Duplicate Detection
- Find duplicate files
- Find duplicate code
- Plagiarism detection

### 3. String Comparison
- Fast equality checks - O(1) instead of O(n)
- Useful in dynamic programming on strings

### 4. Substring Problems
- Longest common substring
- Longest repeated substring
- Count distinct substrings

### 5. Rolling Hash in Sliding Window
- Find longest substring with certain properties
- Compare substrings efficiently

### 6. Hash Tables / Hash Maps
- Fast insertion, deletion, lookup - O(1) average
- Used in dictionaries, caches, databases

## Advantages and Disadvantages

### Advantages:
- **Fast comparison**: O(1) instead of O(n)
- **Space efficient**: Store integer instead of string
- **Versatile**: Works for strings, arrays, objects
- **Simple to implement**: Basic version is straightforward

### Disadvantages:
- **Collisions possible**: Different inputs may have same hash
- **Not deterministic uniqueness**: Need verification for critical applications
- **Overflow issues**: Need careful handling of large values
- **Choice of parameters**: p and MOD affect collision rate

## Common Questions

### Q1: Why use prime numbers (29, 31) for p?
**Answer:** Prime numbers reduce the probability of collisions. They ensure better distribution of hash values across the range.

### Q2: What if hash values overflow?
**Answer:**
- Use `long long` or `unsigned long long`
- Use modulo with large prime: `hash = (hash + value) % MOD`
- Both approaches work, choose based on requirements

### Q3: Can we always trust hash equality?
**Answer:** No! Always verify with actual comparison when correctness is critical:
```cpp
if (hash1 == hash2 && str1 == str2) {
    // Strings are definitely equal
}
```

### Q4: Rabin-Karp vs KMP for pattern matching?
**Answer:**
- **Rabin-Karp**: Simpler to implement, works for multiple patterns, but has small collision probability
- **KMP**: More complex, but guarantees no false positives, better for single pattern

### Q5: Why O(n² log n) for counting distinct substrings?
**Answer:**
- O(n²) to generate all substrings
- O(log n) to insert each hash into set (balanced tree)
- Total: O(n² log n)

## Key Takeaways

1. **Hashing converts strings to integers** for fast comparison
2. **Polynomial rolling hash** is most common for strings: `hash = Σ s[i] × p^i`
3. **Prefix hash array** enables O(1) substring hash queries
4. **Rabin-Karp algorithm** finds patterns in O(n + m) time
5. **Hash collisions are possible** - verify when necessary
6. **Using hashing can improve complexity** from O(n³) to O(n² log n) or better
7. **Choose good parameters**: p = 29 or 31, MOD = large prime
8. **Trade-off**: Speed vs small collision probability

## Practice Problems

1. Find all occurrences of pattern in text using Rabin-Karp
2. Find longest duplicate substring
3. Count palindromic substrings using hashing
4. Find longest common substring of two strings
5. Group anagrams using hash values
6. Detect if two strings are rotations of each other
7. Find smallest window containing all characters
8. Implement efficient spell checker using hashing
