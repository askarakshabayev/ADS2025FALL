# Lecture 5: Heap and Heap Sort

## Introduction to Heap

**A Heap** is a specialized tree-based data structure that satisfies the **heap property**. It is a complete binary tree where each node follows a specific ordering relationship with its children.

### Types of Heaps

1. **Max-Heap**: Every parent node has a value **greater than or equal to** its children
   - Root contains the **maximum** element

2. **Min-Heap**: Every parent node has a value **less than or equal to** its children
   - Root contains the **minimum** element

## Heap Properties

- **Complete Binary Tree**: All levels are completely filled except possibly the last level, which is filled from left to right
- **Heap Property**: Parent-child relationship follows max-heap or min-heap rule
- **Array Representation**: Heaps are typically implemented using arrays (vectors) for efficiency
- **Height**: O(log n) for n elements

## Array Representation of Heap

For a node at index `i`:
- **Parent**: `(i - 1) / 2`
- **Left Child**: `2 * i + 1`
- **Right Child**: `2 * i + 2`

Example Min-Heap:
```
        10
       /   \
      15    20
     / \    / \
    30 40  50  60

Array: [10, 15, 20, 30, 40, 50, 60]
Index:  0   1   2   3   4   5   6
```

## Min-Heap Implementation

```cpp
#include <iostream>

using namespace std;

class MinHeap {
    public:
    vector<int> a;

    // Get parent index
    int parent(int i) {
        return (i - 1) / 2;
    }

    // Get left child index
    int left(int i) {
        return 2 * i + 1;
    }

    // Get right child index
    int right(int i) {
        return 2 * i + 2;
    }

    // Get minimum element (root) - O(1)
    int getMin() {
        return a[0];
    }

    // Insert element - O(log n)
    void insert(int k) {
        // Add element at the end
        a.push_back(k);
        int ind = a.size() - 1;

        // Heapify up: bubble up the element
        while (ind > 0 && a[ind] < a[parent(ind)]) {
            swap(a[ind], a[parent(ind)]);
            ind = parent(ind);
        }
    }

    // Heapify down - O(log n)
    void heapify(int i) {
        if (left(i) > a.size() - 1)
            return;

        // Find smallest among node and its children
        int j = left(i);
        if (right(i) < a.size() && a[right(i)] < a[left(i)])
            j = right(i);

        // If parent is greater than smallest child, swap and continue
        if (a[i] > a[j]) {
            swap(a[i], a[j]);
            heapify(j);
        }
    }

    // Extract minimum element - O(log n)
    int extractMin() {
        int root_value = getMin();

        // Replace root with last element
        swap(a[0], a[a.size() - 1]);
        a.pop_back();

        // Heapify down from root
        if (a.size() > 0)
            heapify(0);

        return root_value;
    }
};

int main() {
    int n, x;
    cin >> n;
    MinHeap *heap = new MinHeap();

    // Insert n elements
    for (int i = 0; i < n; i++) {
        cin >> x;
        heap->insert(x);
    }

    // Extract all elements (sorted order)
    for (int i = 0; i < n; i++)
        cout << heap->extractMin() << " ";

    return 0;
}
```

## Heap Operations Explained

### 1. Insert Operation - O(log n)

**Process:**
1. Add element at the end of array
2. Compare with parent
3. If smaller than parent (for min-heap), swap
4. Continue until heap property is satisfied

**Example:** Insert 5 into [10, 15, 20, 30, 40]
```
Step 1: [10, 15, 20, 30, 40, 5]  - Add at end
Step 2: [10, 15, 20, 30, 5, 40]  - Swap with parent (40)
Step 3: [10, 5, 20, 30, 15, 40]  - Swap with parent (15)
Step 4: [5, 10, 20, 30, 15, 40]  - Swap with parent (10)
```

### 2. Extract Min Operation - O(log n)

**Process:**
1. Save root value (minimum)
2. Replace root with last element
3. Remove last element
4. Heapify down from root

**Example:** Extract min from [10, 15, 20, 30, 40, 50]
```
Step 1: Save 10 (minimum)
Step 2: [50, 15, 20, 30, 40]     - Replace root with last
Step 3: [15, 30, 20, 50, 40]     - Heapify: swap 50 with 15
Step 4: [15, 30, 20, 50, 40]     - Heapify: swap 50 with 40
Result: Return 10, heap is [15, 30, 20, 40, 50]
```

### 3. Heapify Operation - O(log n)

**Process:**
1. Compare node with its children
2. Find smallest among node and children
3. If node is not smallest, swap with smallest child
4. Recursively heapify the affected subtree

## Complete Example with Trace

**Input:** Insert elements: 50, 30, 20, 15, 10, 8, 16

```
Insert 50:  [50]

Insert 30:  [50, 30]
            [30, 50]  - 30 < 50, swap

Insert 20:  [30, 50, 20]
            [20, 50, 30]  - 20 < 30, swap

Insert 15:  [20, 50, 30, 15]
            [20, 15, 30, 50]  - 15 < 50, swap

Insert 10:  [20, 15, 30, 50, 10]
            [20, 10, 30, 50, 15]  - 10 < 15, swap
            [10, 20, 30, 50, 15]  - 10 < 20, swap

Insert 8:   [10, 20, 30, 50, 15, 8]
            [10, 20, 8, 50, 15, 30]  - 8 < 30, swap
            [8, 20, 10, 50, 15, 30]  - 8 < 10, swap

Insert 16:  [8, 20, 10, 50, 15, 30, 16]
            [8, 20, 10, 16, 15, 30, 50]  - 16 < 50, swap

Final Heap: [8, 15, 10, 20, 16, 30, 50]

Tree Structure:
        8
       / \
      15  10
     / \  / \
    20 16 30 50
```

## Heap Sort Using Min-Heap

The program effectively implements **Heap Sort**:

1. **Build heap**: Insert all elements - O(n log n)
2. **Extract all**: Extract min repeatedly - O(n log n)
3. **Result**: Sorted array in ascending order

**Example:**
```
Input:  [64, 34, 25, 12, 22, 11, 90]

After building heap: [11, 22, 25, 12, 34, 64, 90]

Extract operations:
Extract: 11 → Heap: [12, 22, 25, 90, 34, 64]
Extract: 12 → Heap: [22, 34, 25, 90, 64]
Extract: 22 → Heap: [25, 34, 64, 90]
Extract: 25 → Heap: [34, 90, 64]
Extract: 34 → Heap: [64, 90]
Extract: 64 → Heap: [90]
Extract: 90 → Heap: []

Sorted: [11, 12, 22, 25, 34, 64, 90]
```

## Time Complexity Analysis

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| **getMin()** | O(1) | Simply return root element |
| **insert()** | O(log n) | Add at end, bubble up |
| **extractMin()** | O(log n) | Remove root, heapify down |
| **heapify()** | O(log n) | Restore heap property |
| **Sorting n elements** | O(n log n) | n insertions + n extractions |

## Space Complexity

- **Vector storage**: O(n) for n elements
- **Recursion stack**: O(log n) for heapify operation
- **Total**: O(n)

## Practical Applications

### 1. Priority Queue
```cpp
MinHeap pq;
pq.insert(5);  // Add task with priority 5
pq.insert(1);  // Add task with priority 1
pq.insert(3);  // Add task with priority 3

// Process in priority order (1, 3, 5)
while (!pq.a.empty()) {
    cout << pq.extractMin() << " ";
}
```

### 2. Finding K Smallest Elements
```cpp
MinHeap heap;
// Insert all elements
for (int num : array)
    heap.insert(num);

// Extract k smallest
for (int i = 0; i < k; i++)
    cout << heap.extractMin() << " ";
```

### 3. Heap Sort Implementation
```cpp
MinHeap heap;
// Insert all elements
for (int num : unsorted_array)
    heap.insert(num);

// Extract all (sorted)
vector<int> sorted;
while (!heap.a.empty())
    sorted.push_back(heap.extractMin());
```

### 4. Merging K Sorted Arrays
- Insert first element from each array into min-heap
- Extract minimum, insert next element from same array
- Continue until all elements processed

## Advantages of This Implementation

1. **Simple and clean code**
2. **Using STL vector** for dynamic size
3. **Recursive heapify** is easy to understand
4. **Direct array access** for efficiency
5. **Compact implementation** with essential operations

## Potential Improvements

### 1. Add Size Check
```cpp
int getMin() {
    if (a.empty()) {
        throw runtime_error("Heap is empty");
    }
    return a[0];
}
```

### 2. Add Build Heap Method
```cpp
void buildHeap(vector<int> arr) {
    a = arr;
    // Start from last non-leaf node
    for (int i = a.size() / 2 - 1; i >= 0; i--) {
        heapify(i);
    }
}
```

### 3. Add Print Function
```cpp
void printHeap() {
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << " ";
    cout << endl;
}
```

## Max-Heap Implementation

For a **Max-Heap**, simply reverse the comparisons:

```cpp
class MaxHeap {
public:
    vector<int> a;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    int getMax() { return a[0]; }

    void insert(int k) {
        a.push_back(k);
        int ind = a.size() - 1;
        // Change: bubble up if GREATER than parent
        while (ind > 0 && a[ind] > a[parent(ind)]) {
            swap(a[ind], a[parent(ind)]);
            ind = parent(ind);
        }
    }

    void heapify(int i) {
        if (left(i) > a.size() - 1)
            return;
        int j = left(i);
        // Change: find LARGEST child
        if (right(i) < a.size() && a[right(i)] > a[left(i)])
            j = right(i);
        // Change: swap if parent is SMALLER
        if (a[i] < a[j]) {
            swap(a[i], a[j]);
            heapify(j);
        }
    }

    int extractMax() {
        int root_value = getMax();
        swap(a[0], a[a.size() - 1]);
        a.pop_back();
        if (a.size() > 0)
            heapify(0);
        return root_value;
    }
};
```

## Sample Run

**Input:**
```
7
64 34 25 12 22 11 90
```

**Process:**
```
Building heap:
Insert 64: [64]
Insert 34: [34, 64]
Insert 25: [25, 64, 34]
Insert 12: [25, 12, 34, 64]
Insert 22: [22, 12, 34, 64, 25]
Insert 11: [11, 12, 22, 64, 25, 34]
Insert 90: [11, 12, 22, 64, 25, 34, 90]

Heap structure:
        11
       /  \
      12   22
     / \   / \
    64 25 34 90

Extracting (sorted):
11 12 22 25 34 64 90
```

**Output:**
```
11 12 22 25 34 64 90
```

## Common Questions

### Q1: Why is heapify O(log n)?
**Answer:** At each step, we compare and potentially swap with one child, moving down one level. Since heap height is log n, maximum steps is log n.

### Q2: Build heap - O(n) vs O(n log n)?
**Answer:**
- **Inserting n elements one by one**: O(n log n)
- **Build heap from array (heapify from bottom)**: O(n) - more efficient

### Q3: Why use heap for sorting?
**Answer:**
- Guaranteed O(n log n) time
- In-place if implemented correctly
- No worst-case degradation like Quick Sort

### Q4: When to use Min-Heap vs Max-Heap?
**Answer:**
- **Min-Heap**: Find smallest elements, ascending order sort
- **Max-Heap**: Find largest elements, descending order sort

## Comparison with Other Data Structures

| Operation | Array | Sorted Array | Linked List | Min-Heap |
|-----------|-------|--------------|-------------|----------|
| **Find Min** | O(n) | O(1) | O(n) | **O(1)** |
| **Extract Min** | O(n) | O(n) | O(n) | **O(log n)** |
| **Insert** | O(1) | O(n) | O(1) | **O(log n)** |
| **Sort** | O(n log n) | - | O(n log n) | **O(n log n)** |

## Key Takeaways

1. **Min-Heap always has minimum element at root** - O(1) access
2. **Insert and extract operations are O(log n)** - efficient
3. **Heapify maintains heap property** by comparing with children
4. **Complete binary tree stored in array** - space efficient
5. **Heap sort achieves O(n log n)** by repeated extract operations
6. **Parent-child relationships** determined by simple formulas
7. **No pointer manipulation** needed - array indices handle structure
8. **Perfect for priority queue** implementation

## Practice Problems

1. Find the kth smallest element in an array
2. Merge k sorted arrays
3. Find median in a data stream
4. Sort a nearly sorted array
5. Connect n ropes with minimum cost
6. Find k largest elements in an array
7. Implement heap using only insert and extractMin operations
