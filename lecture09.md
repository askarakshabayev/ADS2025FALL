# Lecture 9: Prefix Function and Knuth-Morris-Pratt Algorithm

## Introduction

The **Knuth-Morris-Pratt (KMP)** algorithm is an efficient string matching algorithm that finds all occurrences of a pattern in a text in **O(n + m)** time, where n is the length of the text and m is the length of the pattern.

The key to KMP algorithm is the **prefix function**, which allows us to efficiently find patterns without redundant comparisons.

## Prefix Function

### Definition

For a string s of length n, the **prefix function** π[i] is defined as:

**π[i] = length of the longest proper prefix of substring s[0...i] that is also a suffix of s[0...i]**

**Proper prefix** means a prefix that is not equal to the entire substring.

### Examples

**Example 1:** s = "abcabcd"

```
i = 0: s[0...0] = "a"
       Proper prefixes: (none)
       Suffixes: (none)
       π[0] = 0

i = 1: s[0...1] = "ab"
       Proper prefixes: "a"
       Suffixes: "b"
       No match → π[1] = 0

i = 2: s[0...2] = "abc"
       Proper prefixes: "a", "ab"
       Suffixes: "c", "bc"
       No match → π[2] = 0

i = 3: s[0...3] = "abca"
       Proper prefixes: "a", "ab", "abc"
       Suffixes: "a", "ca", "bca"
       Match: "a" → π[3] = 1

i = 4: s[0...4] = "abcab"
       Proper prefixes: "a", "ab", "abc", "abca"
       Suffixes: "b", "ab", "cab", "bcab"
       Match: "ab" → π[4] = 2

i = 5: s[0...5] = "abcabc"
       Proper prefixes: "a", "ab", "abc", "abca", "abcab"
       Suffixes: "c", "bc", "abc", "cabc", "bcabc"
       Match: "abc" → π[5] = 3

i = 6: s[0...6] = "abcabcd"
       Proper prefixes: "a", "ab", "abc", "abca", "abcab", "abcabc"
       Suffixes: "d", "cd", "bcd", "abcd", "cabcd", "bcabcd"
       No match → π[6] = 0

Result: π = [0, 0, 0, 1, 2, 3, 0]
```

**Example 2:** s = "aabaaab"

```
i = 0: π[0] = 0
i = 1: "aa" → prefix "a" = suffix "a" → π[1] = 1
i = 2: "aab" → no match → π[2] = 0
i = 3: "aaba" → prefix "a" = suffix "a" → π[3] = 1
i = 4: "aabaa" → prefix "aa" = suffix "aa" → π[4] = 2
i = 5: "aabaaa" → prefix "aa" = suffix "aa" → π[5] = 2
i = 6: "aabaaab" → prefix "aab" = suffix "aab" → π[6] = 3

Result: π = [0, 1, 0, 1, 2, 2, 3]
```

**Example 3:** s = "aaaa"

```
i = 0: π[0] = 0
i = 1: "aa" → prefix "a" = suffix "a" → π[1] = 1
i = 2: "aaa" → prefix "aa" = suffix "aa" → π[2] = 2
i = 3: "aaaa" → prefix "aaa" = suffix "aaa" → π[3] = 3

Result: π = [0, 1, 2, 3]
```

### Computing Prefix Function - Naive Approach O(n³)

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> prefix_function_naive(string s) {
    int n = s.size();
    vector<int> pi(n);

    pi[0] = 0;  // By definition

    for (int i = 1; i < n; i++) {
        // Try all possible lengths from longest to shortest
        for (int len = i; len > 0; len--) {
            // Check if prefix of length len equals suffix of length len
            bool match = true;
            for (int j = 0; j < len; j++) {
                if (s[j] != s[i - len + 1 + j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                pi[i] = len;
                break;
            }
        }
    }

    return pi;
}

int main() {
    string s = "abcabcd";
    vector<int> pi = prefix_function_naive(s);

    cout << "String: " << s << endl;
    cout << "Prefix function: ";
    for (int i = 0; i < pi.size(); i++)
        cout << pi[i] << " ";
    cout << endl;

    return 0;
}
```

**Time Complexity:** O(n³) - too slow!

### Computing Prefix Function - Efficient Approach O(n)

**Key Observation:**
- If we know π[i-1], we can compute π[i] more efficiently
- We use the previously computed values to avoid redundant comparisons

**Algorithm:**
1. Start with π[0] = 0
2. For each position i, we look at the previous match length j = π[i-1]
3. If s[i] == s[j], then π[i] = j + 1
4. If s[i] != s[j], we "fall back" to π[j-1] and try again
5. Continue falling back until we find a match or reach 0

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> prefix_function(string s) {
    int n = s.size();
    vector<int> pi(n);

    pi[0] = 0;  // First element is always 0

    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];  // Previous prefix length

        // Fall back until we find a match or reach 0
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        // If characters match, increment the length
        if (s[i] == s[j]) {
            j++;
        }

        pi[i] = j;
    }

    return pi;
}

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;

    vector<int> pi = prefix_function(s);

    cout << "\nString:          ";
    for (int i = 0; i < s.size(); i++)
        cout << s[i] << " ";
    cout << endl;

    cout << "Index:           ";
    for (int i = 0; i < s.size(); i++)
        cout << i << " ";
    cout << endl;

    cout << "Prefix function: ";
    for (int i = 0; i < pi.size(); i++)
        cout << pi[i] << " ";
    cout << endl;

    return 0;
}
```

**Time Complexity:** O(n)
**Space Complexity:** O(n)

### Step-by-Step Trace

**Example:** s = "abcabcd"

```
i = 0: pi[0] = 0 (by definition)

i = 1:
  j = pi[0] = 0
  s[1] = 'b', s[0] = 'a' → no match
  pi[1] = 0

i = 2:
  j = pi[1] = 0
  s[2] = 'c', s[0] = 'a' → no match
  pi[2] = 0

i = 3:
  j = pi[2] = 0
  s[3] = 'a', s[0] = 'a' → match!
  pi[3] = 1

i = 4:
  j = pi[3] = 1
  s[4] = 'b', s[1] = 'b' → match!
  pi[4] = 2

i = 5:
  j = pi[4] = 2
  s[5] = 'c', s[2] = 'c' → match!
  pi[5] = 3

i = 6:
  j = pi[5] = 3
  s[6] = 'd', s[3] = 'a' → no match
  Fall back: j = pi[2] = 0
  s[6] = 'd', s[0] = 'a' → no match
  pi[6] = 0

Result: π = [0, 0, 0, 1, 2, 3, 0]
```

## Knuth-Morris-Pratt (KMP) Algorithm

### Problem Statement

Given:
- Text string `text` (length n)
- Pattern string `pattern` (length m)

Find all occurrences of `pattern` in `text`.

### KMP Approach - O(n + m)

**Key Idea:** Create a combined string: `pattern + '#' + text`

Where `#` is a separator character that doesn't appear in pattern or text.

**Why this works:**
- Compute prefix function for the combined string
- When π[i] equals pattern length, we found a match
- The separator ensures pattern doesn't match across the boundary

### KMP Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> prefix_function(string s) {
    int n = s.size();
    vector<int> pi(n);
    pi[0] = 0;

    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            j++;
        }

        pi[i] = j;
    }

    return pi;
}

void KMP(string text, string pattern) {
    // Create combined string: pattern + '#' + text
    string s = pattern + "#" + text;

    int n = s.size();
    int m = pattern.size();

    // Compute prefix function
    vector<int> pi = prefix_function(s);

    // Find all occurrences
    for (int i = m + 1; i < n; i++) {
        // If prefix length equals pattern length, we found a match
        if (pi[i] == m) {
            // Position in text = i - m - m
            int pos = i - 2 * m;
            cout << "Pattern found at index " << pos << endl;
        }
    }
}

int main() {
    string text, pattern;

    cout << "Enter text: ";
    cin >> text;

    cout << "Enter pattern: ";
    cin >> pattern;

    cout << "\nSearching for pattern in text...\n" << endl;
    KMP(text, pattern);

    return 0;
}
```

### KMP Step-by-Step Example

**Input:**
```
text = "ababcabcabababd"
pattern = "ababd"
```

**Step 1:** Create combined string
```
s = "ababd#ababcabcabababd"
     01234 5 6789012345678901
```

**Step 2:** Compute prefix function
```
Index:  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
String: a b a b d # a b a b c  a  b  c  a  b  a  b  a  b  d
π:      0 0 1 2 0 0 1 2 3 4 0  1  2  0  1  2  3  4  5  4  5

Explanation:
- π[0] = 0
- π[1] = 0 (b ≠ a)
- π[2] = 1 (a = a)
- π[3] = 2 (ab = ab)
- π[4] = 0 (d ≠ a)
- π[5] = 0 (# doesn't match anything)
- π[6] = 1 (a = a)
- π[7] = 2 (ab = ab)
- π[8] = 3 (aba = aba)
- π[9] = 4 (abab = abab)
- π[10] = 0 (c ≠ d)
...
- π[20] = 5 (ababd = ababd) → MATCH FOUND!
```

**Step 3:** Find matches
```
When π[i] == 5 (pattern length):
  i = 20: position in text = 20 - 2*5 = 10
  Pattern found at index 10
```

**Verification:**
```
text = "ababcabcabababd"
index:  0123456789012345
                  ^^^^^ (index 10-14 is "ababd")
```

### Another Example

**Input:**
```
text = "aabaacaabaa"
pattern = "aaba"
```

**Combined string:**
```
s = "aaba#aabaacaabaa"
     0123 4 56789012345
```

**Prefix function:**
```
Index:  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
String: a a b a # a a b a a c  a  a  b  a  a
π:      0 1 0 1 0 1 2 3 4 2 0  1  2  3  4  2

Matches found when π[i] = 4:
- π[8] = 4  → position = 8 - 2*4 = 0
- π[13] = 4 → position = 13 - 2*4 = 5

Pattern found at index 0 and 5
```

**Verification:**
```
text = "aabaacaabaa"
        ^^^^        (index 0-3: "aaba")
           ^^^^     (index 5-8: "aaba")
```

### Time Complexity Analysis

| Operation | Time |
|-----------|------|
| Create combined string | O(n + m) |
| Compute prefix function | O(n + m) |
| Find matches | O(n + m) |
| **Total** | **O(n + m)** |

## Problems Solved Using Prefix Function and KMP

### 1. Pattern Matching (Direct Application)

**Problem:** Find all occurrences of pattern in text

**Solution:** Create `pattern + '#' + text` and compute prefix function

```cpp
void find_all_occurrences(string text, string pattern) {
    string s = pattern + "#" + text;
    vector<int> pi = prefix_function(s);
    int m = pattern.size();

    cout << "Pattern found at positions: ";
    for (int i = m + 1; i < s.size(); i++) {
        if (pi[i] == m) {
            cout << (i - 2 * m) << " ";
        }
    }
    cout << endl;
}
```

### 2. Counting Pattern Occurrences

**Problem:** Count how many times pattern appears in text (including overlapping)

**Solution:** Count how many times π[i] equals pattern length

```cpp
int count_occurrences(string text, string pattern) {
    string s = pattern + "#" + text;
    vector<int> pi = prefix_function(s);
    int m = pattern.size();
    int count = 0;

    for (int i = m + 1; i < s.size(); i++) {
        if (pi[i] == m) {
            count++;
        }
    }

    return count;
}

// Example: text = "aaaa", pattern = "aa"
// s = "aa#aaaa"
// Occurrences at: 0, 1, 2 → count = 3
```

### 3. Finding Shortest Period of String

**Problem:** Find the shortest repeating pattern in a string

**Example:** "abcabcabc" has period "abc" (length 3)

**Solution:** Use prefix function

```cpp
int shortest_period(string s) {
    int n = s.size();
    vector<int> pi = prefix_function(s);

    int len = n - pi[n - 1];  // Length of shortest period

    // Check if string is actually periodic
    if (n % len == 0) {
        return len;
    } else {
        return n;  // No period (entire string)
    }
}

// Example: s = "abcabcabc"
// pi[8] = 6 (prefix "abcabc" = suffix "abcabc")
// len = 9 - 6 = 3
// 9 % 3 == 0 → period length is 3
```

**Explanation:**
- If π[n-1] = k, then the first k characters match the last k characters
- The shortest period has length (n - k)
- If n is divisible by (n - k), the string is periodic

### 4. String Compression

**Problem:** Find if string can be represented as repeated pattern

**Solution:** Check if shortest period divides string length

```cpp
string compress(string s) {
    int n = s.size();
    int period_len = shortest_period(s);

    if (period_len < n) {
        int count = n / period_len;
        string pattern = s.substr(0, period_len);
        return pattern + " × " + to_string(count);
    }

    return s;  // Cannot compress
}

// Example: "abcabcabc" → "abc × 3"
// Example: "abcdef" → "abcdef" (no compression)
```

### 5. Finding Pattern in Cyclic String

**Problem:** Check if pattern exists in any rotation of text

**Solution:** Create `pattern + '#' + text + text`

```cpp
bool pattern_in_rotation(string text, string pattern) {
    string doubled = text + text;
    string s = pattern + "#" + doubled;
    vector<int> pi = prefix_function(s);
    int m = pattern.size();

    for (int i = m + 1; i < s.size(); i++) {
        if (pi[i] == m) {
            return true;
        }
    }

    return false;
}

// Example: text = "abcde", pattern = "dea"
// s = "dea#abcdeabcde"
// Pattern "dea" found → true
```

### 6. Palindrome Problems

**Problem:** Find longest prefix that is also a palindrome

**Solution:** Use prefix function on `s + '#' + reverse(s)`

```cpp
int longest_palindrome_prefix(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());

    string combined = s + "#" + rev;
    vector<int> pi = prefix_function(combined);

    return pi[combined.size() - 1];
}

// Example: s = "abacaba"
// rev = "abacaba"
// combined = "abacaba#abacaba"
// π[14] = 7 → entire string is palindrome
```

### 7. Finding All Borders

**Problem:** Find all lengths k such that prefix of length k equals suffix of length k

**Solution:** Use prefix function and backtrack

```cpp
vector<int> find_all_borders(string s) {
    int n = s.size();
    vector<int> pi = prefix_function(s);
    vector<int> borders;

    int k = pi[n - 1];
    while (k > 0) {
        borders.push_back(k);
        k = pi[k - 1];
    }

    reverse(borders.begin(), borders.end());
    return borders;
}

// Example: s = "abcabcab"
// Borders: lengths 2, 5 ("ab", "abcab")
```

### 8. Multiple Pattern Matching

**Problem:** Find if any of multiple patterns exist in text

**Solution:** For each pattern, create `pattern + '#' + text`

```cpp
void find_multiple_patterns(string text, vector<string> patterns) {
    for (int k = 0; k < patterns.size(); k++) {
        string s = patterns[k] + "#" + text;
        vector<int> pi = prefix_function(s);
        int m = patterns[k].size();

        for (int i = m + 1; i < s.size(); i++) {
            if (pi[i] == m) {
                cout << "Pattern " << k << " (\"" << patterns[k];
                cout << "\") found at index " << (i - 2 * m) << endl;
                break;  // Found first occurrence
            }
        }
    }
}
```

## Comparison: KMP vs Rabin-Karp

| Feature | KMP | Rabin-Karp |
|---------|-----|------------|
| **Time Complexity** | O(n + m) guaranteed | O(n + m) average, O(n×m) worst |
| **Space** | O(n + m) | O(n) for prefix hashes |
| **False Positives** | None | Possible (hash collisions) |
| **Implementation** | Prefix function | Hash function |
| **Multiple Patterns** | Need modification | Easy to extend |
| **Preprocessing** | Prefix function | Hash computation |

**When to use KMP:**
- Need guaranteed O(n + m) time
- No false positives acceptable
- Single pattern matching

**When to use Rabin-Karp:**
- Multiple pattern matching
- Simpler implementation preferred
- Small probability of collision acceptable

## Advantages and Disadvantages

### Advantages:
- **Guaranteed O(n + m) time** - no worst case degradation
- **No false positives** - always correct
- **Simple elegant approach** - using `pattern + '#' + text`
- **Prefix function is versatile** - solves many problems
- **No backtracking needed** - linear scan

### Disadvantages:
- **Extra space** - O(n + m) for combined string
- **Preprocessing required** - compute prefix function
- **Not practical for very long texts** - need to store entire combined string
- **Single pattern** - need to repeat for multiple patterns

## Common Questions

### Q1: Why do we need the separator '#'?
**Answer:** Without separator, the pattern could match across the boundary between pattern and text, giving incorrect results. For example:
```
pattern = "ab", text = "cab"
Without #: "abcab" → would match at position 0 (wrong!)
With #:    "ab#cab" → no match (correct!)
```

### Q2: What if '#' appears in the text or pattern?
**Answer:** Choose a separator that doesn't appear in either. Common choices:
- `'#'` if using only letters
- `'$'` if using printable ASCII
- Any character with value > max character in alphabet

### Q3: Why is this approach simpler than traditional KMP?
**Answer:** Traditional KMP requires careful handling of pattern pointer and text pointer. The combined string approach reduces it to a simple loop checking π[i] == m.

### Q4: Can we save space?
**Answer:** Yes! We can compute prefix function on-the-fly without storing the entire combined string, but the implementation becomes more complex.

### Q5: How does prefix function take O(n) time?
**Answer:** Although there's a while loop inside the for loop, the variable j can only increase n times total (once per iteration max), so it can decrease at most n times total. Total operations: O(n).

## Key Takeaways

1. **Prefix function is key** - computes longest proper prefix that equals suffix
2. **Pattern matching using `pattern + '#' + text`** - elegant and simple
3. **O(n + m) guaranteed** - no worst case degradation
4. **When π[i] = m, pattern found** - match at position i - 2*m
5. **Separator '#' is essential** - prevents false matches
6. **Prefix function is O(n)** - linear time computation
7. **Many applications** - period finding, compression, palindromes
8. **No false positives** - unlike hashing methods

## Practice Problems

1. Implement KMP to find all occurrences of pattern in text
2. Find shortest period of a string
3. Count overlapping pattern occurrences
4. Check if string is concatenation of repeated substring
5. Find longest palindrome prefix using prefix function
6. Find if pattern exists in any rotation of string
7. Compress string using repeating pattern
8. Find all borders of a string (prefixes that are also suffixes)
9. Count number of times each pattern appears in text
10. Find lexicographically smallest rotation of string
