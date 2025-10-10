# Lecture 6: Quick Sort and Merge Sort

## Introduction to Sorting

Sorting is one of the most fundamental operations in computer science. It arranges data in a particular order (ascending or descending), making searching and data manipulation more efficient.

## Why Do We Need Multiple Sorting Algorithms?

Different sorting algorithms have different characteristics that make them suitable for different scenarios:

- **Time Complexity**: Some are faster for large datasets
- **Space Complexity**: Some use less memory
- **Stability**: Some preserve the relative order of equal elements
- **Adaptivity**: Some perform better on partially sorted data
- **Online**: Some can sort data as it arrives
- **In-place**: Some require minimal extra memory

**No single sorting algorithm is best for all situations!**

## Bubble Sort: The Simple Algorithm

**Bubble Sort** is the simplest sorting algorithm. It repeatedly steps through the list, compares adjacent elements, and swaps them if they are in wrong order.

### How Bubble Sort Works

1. Compare adjacent elements
2. Swap if they are in wrong order
3. Repeat until no swaps are needed

### Bubble Sort Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        // Last i elements are already in place
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no swapping happened, array is sorted
        if (!swapped)
            break;
    }
}

void printArray(vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "Original array: ";
    printArray(arr);

    bubbleSort(arr);

    cout << "Sorted array:   ";
    printArray(arr);

    return 0;
}
```

### Bubble Sort Step-by-Step Example

**Input:** [64, 34, 25, 12, 22, 11, 90]

```
Pass 1:
[64, 34, 25, 12, 22, 11, 90]
[34, 64, 25, 12, 22, 11, 90]  - swap 64, 34
[34, 25, 64, 12, 22, 11, 90]  - swap 64, 25
[34, 25, 12, 64, 22, 11, 90]  - swap 64, 12
[34, 25, 12, 22, 64, 11, 90]  - swap 64, 22
[34, 25, 12, 22, 11, 64, 90]  - swap 64, 11
[34, 25, 12, 22, 11, 64, 90]  - 64 < 90, no swap

Pass 2:
[25, 34, 12, 22, 11, 64, 90]  - swap 34, 25
[25, 12, 34, 22, 11, 64, 90]  - swap 34, 12
[25, 12, 22, 34, 11, 64, 90]  - swap 34, 22
[25, 12, 22, 11, 34, 64, 90]  - swap 34, 11
[25, 12, 22, 11, 34, 64, 90]  - 34 < 64, no swap

...continues until sorted...

Final: [11, 12, 22, 25, 34, 64, 90]
```

### Bubble Sort Complexity

| Case | Time Complexity | Description |
|------|----------------|-------------|
| **Best Case** | O(n) | Already sorted array |
| **Average Case** | O(n²) | Random order |
| **Worst Case** | O(n²) | Reverse sorted array |
| **Space** | O(1) | In-place sorting |

### Problems with Bubble Sort

1. **Inefficient for large datasets** - O(n²) is too slow
2. **Too many comparisons** - compares adjacent elements repeatedly
3. **Too many swaps** - moves elements one position at a time
4. **Not suitable for real-world applications** with large data

**Example:** Sorting 1,000,000 elements
- Bubble Sort: ~1,000,000,000,000 operations
- Quick Sort: ~20,000,000 operations
- **50,000 times slower!**

## Why We Need Quick Sort and Merge Sort

### Advantages of Advanced Algorithms

1. **Much Faster**: O(n log n) vs O(n²)
2. **Scalable**: Handle millions of elements efficiently
3. **Practical**: Used in real-world systems
4. **Divide and Conquer**: Break problem into smaller subproblems

### Performance Comparison

| Array Size | Bubble Sort | Quick Sort | Merge Sort |
|------------|-------------|------------|------------|
| 100 | 10,000 ops | 664 ops | 664 ops |
| 1,000 | 1,000,000 ops | 9,966 ops | 9,966 ops |
| 10,000 | 100,000,000 ops | 132,877 ops | 132,877 ops |
| 100,000 | 10,000,000,000 ops | 1,660,964 ops | 1,660,964 ops |

## Merge Sort

**Merge Sort** is a divide-and-conquer algorithm that divides the array into halves, recursively sorts them, and then merges the sorted halves.

### Merge Sort Algorithm

1. **Divide**: Split array into two halves
2. **Conquer**: Recursively sort both halves
3. **Combine**: Merge the two sorted halves

### Merge Sort Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Merge two sorted subarrays arr[left...mid] and arr[mid+1...right]
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;  // Size of left subarray
    int n2 = right - mid;      // Size of right subarray

    // Create temporary arrays
    vector<int> L(n1), R(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back
    int i = 0;     // Initial index of left subarray
    int j = 0;     // Initial index of right subarray
    int k = left;  // Initial index of merged array

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main merge sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void printArray(vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    cout << "Original array: ";
    printArray(arr);

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted array:   ";
    printArray(arr);

    return 0;
}
```

### Merge Sort Visualization

**Input:** [38, 27, 43, 3, 9, 82, 10]

```
                    [38, 27, 43, 3, 9, 82, 10]
                    /                        \
           [38, 27, 43, 3]                [9, 82, 10]
           /            \                  /         \
      [38, 27]        [43, 3]          [9, 82]      [10]
      /     \         /     \          /     \
    [38]   [27]    [43]    [3]      [9]    [82]
      \     /         \     /          \     /
      [27, 38]        [3, 43]          [9, 82]      [10]
           \            /                  \         /
           [3, 27, 38, 43]                [9, 10, 82]
                    \                        /
                    [3, 9, 10, 27, 38, 43, 82]
```

### Merge Sort Complexity

| Case | Time Complexity | Space Complexity |
|------|----------------|------------------|
| **Best Case** | O(n log n) | O(n) |
| **Average Case** | O(n log n) | O(n) |
| **Worst Case** | O(n log n) | O(n) |

### Merge Sort Characteristics

**Advantages:**
- **Guaranteed O(n log n)** performance
- **Stable**: Preserves order of equal elements
- **Predictable**: Always same time complexity
- **Good for linked lists**: No random access needed

**Disadvantages:**
- **Extra space**: Requires O(n) additional memory
- **Not in-place**: Uses auxiliary arrays
- **Slower for small arrays**: Overhead of recursion

## Quick Sort

**Quick Sort** is a divide-and-conquer algorithm that picks a pivot element and partitions the array around it, then recursively sorts the partitions.

### Quick Sort Algorithm

1. **Choose a pivot** element from array
2. **Partition**: Rearrange array so elements < pivot are on left, elements > pivot are on right
3. **Recursively** apply above steps to left and right partitions

### Quick Sort Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Partition function: places pivot in correct position
// and places smaller elements to left, larger to right
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Choose rightmost element as pivot
    int i = low - 1;        // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Main quick sort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now in right place
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    cout << "Original array: ";
    printArray(arr);

    quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted array:   ";
    printArray(arr);

    return 0;
}
```

### Quick Sort Step-by-Step Example

**Input:** [10, 7, 8, 9, 1, 5]

```
Initial array: [10, 7, 8, 9, 1, 5]
Pivot = 5 (last element)

Partitioning:
Compare 10 with 5: 10 > 5, no swap
Compare 7 with 5:  7 > 5, no swap
Compare 8 with 5:  8 > 5, no swap
Compare 9 with 5:  9 > 5, no swap
Compare 1 with 5:  1 <= 5, swap arr[0] and arr[4]
Result: [1, 7, 8, 9, 10, 5]

Place pivot in correct position: swap arr[1] and arr[5]
Result: [1, 5, 8, 9, 10, 7]

Now pivot 5 is in correct position (index 1)
Left partition: [1]  - already sorted
Right partition: [8, 9, 10, 7]

Recursively sort [8, 9, 10, 7]:
Pivot = 7
After partition: [7, 9, 10, 8]
Left: [] - empty
Right: [9, 10, 8]

Recursively sort [9, 10, 8]:
Pivot = 8
After partition: [8, 10, 9]
Left: [] - empty
Right: [10, 9]

Recursively sort [10, 9]:
Pivot = 9
After partition: [9, 10]
Done!

Final: [1, 5, 7, 8, 9, 10]
```

### Quick Sort Complexity

| Case | Time Complexity | Space Complexity |
|------|----------------|------------------|
| **Best Case** | O(n log n) | O(log n) |
| **Average Case** | O(n log n) | O(log n) |
| **Worst Case** | O(n²) | O(n) |

### Quick Sort Characteristics

**Advantages:**
- **Fastest in practice** for average case
- **In-place sorting**: Uses O(log n) stack space
- **Cache-friendly**: Good locality of reference
- **Simple to implement**

**Disadvantages:**
- **Worst case O(n²)**: When pivot is always smallest/largest
- **Not stable**: May change relative order of equal elements
- **Recursive**: Uses stack space

### Pivot Selection Strategies

1. **Last element**: Simple but can be slow on sorted arrays
2. **First element**: Same problem as last element
3. **Random element**: Better average case
4. **Median of three**: Choose median of first, middle, last
5. **Median of medians**: Guaranteed O(n log n) but complex

## Comparison: Merge Sort vs Quick Sort

| Feature | Merge Sort | Quick Sort |
|---------|------------|------------|
| **Time (Average)** | O(n log n) | O(n log n) |
| **Time (Worst)** | O(n log n) | O(n²) |
| **Space** | O(n) | O(log n) |
| **Stability** | Yes | No |
| **In-place** | No | Yes |
| **Cache Performance** | Poor | Good |
| **Best for** | Linked lists, guaranteed performance | Arrays, average case |

## Non-Sorting Problems Using Divide and Conquer

### 1. Finding Inversions in Array

**Problem:** Count pairs (i, j) where i < j but arr[i] > arr[j]

**Solution:** Modified merge sort can count inversions during merge

```cpp
long long mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    long long inv_count = 0;

    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            // All remaining elements in L are greater than R[j]
            inv_count += (L.size() - i);
        }
    }

    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];

    return inv_count;
}

long long countInversions(vector<int>& arr, int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv_count += countInversions(arr, left, mid);
        inv_count += countInversions(arr, mid + 1, right);
        inv_count += mergeAndCount(arr, left, mid, right);
    }
    return inv_count;
}

// Example: [8, 4, 2, 1]
// Inversions: (8,4), (8,2), (8,1), (4,2), (4,1), (2,1) = 6
```

### 2. Finding Kth Smallest Element

**Problem:** Find the kth smallest element without fully sorting

**Solution:** Quick select (modified quick sort)

```cpp
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int quickSelect(vector<int>& arr, int low, int high, int k) {
    if (low <= high) {
        int pi = partition(arr, low, high);

        if (pi == k)
            return arr[pi];
        else if (pi > k)
            return quickSelect(arr, low, pi - 1, k);
        else
            return quickSelect(arr, pi + 1, high, k);
    }
    return -1;
}

// Example: Find 3rd smallest in [7, 10, 4, 3, 20, 15]
// quickSelect(arr, 0, 5, 2) returns 7
// O(n) average time vs O(n log n) for sorting
```

### 3. Closest Pair of Points

**Problem:** Find two closest points in 2D plane

**Solution:** Divide and conquer approach similar to merge sort

```cpp
struct Point {
    int x, y;
};

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double closestPair(vector<Point>& points, int left, int right) {
    // Base case: brute force for small arrays
    if (right - left <= 3) {
        double minDist = INT_MAX;
        for (int i = left; i < right; i++)
            for (int j = i + 1; j <= right; j++)
                minDist = min(minDist, distance(points[i], points[j]));
        return minDist;
    }

    // Divide
    int mid = left + (right - left) / 2;
    double dl = closestPair(points, left, mid);
    double dr = closestPair(points, mid + 1, right);
    double d = min(dl, dr);

    // Check points near dividing line
    // ... (additional logic for strip)

    return d;
}
```

### 4. Maximum Subarray Sum

**Problem:** Find contiguous subarray with largest sum

**Solution:** Divide and conquer (Kadane's algorithm is simpler, but this shows the concept)

```cpp
int maxCrossingSum(vector<int>& arr, int left, int mid, int right) {
    int sum = 0;
    int leftSum = INT_MIN;

    // Find max sum from mid to left
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    sum = 0;
    int rightSum = INT_MIN;

    // Find max sum from mid+1 to right
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    return leftSum + rightSum;
}

int maxSubarraySum(vector<int>& arr, int left, int right) {
    if (left == right)
        return arr[left];

    int mid = left + (right - left) / 2;

    return max({maxSubarraySum(arr, left, mid),
                maxSubarraySum(arr, mid + 1, right),
                maxCrossingSum(arr, left, mid, right)});
}

// Example: [-2, 1, -3, 4, -1, 2, 1, -5, 4]
// Result: 6 (subarray [4, -1, 2, 1])
```

### 5. Binary Search

**Problem:** Search for element in sorted array

**Solution:** Divide and conquer approach

```cpp
int binarySearch(vector<int>& arr, int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] > target)
            return binarySearch(arr, left, mid - 1, target);

        return binarySearch(arr, mid + 1, right, target);
    }
    return -1;
}
```

### 6. Counting Smaller Elements to the Right

**Problem:** For each element, count how many elements to its right are smaller

**Solution:** Modified merge sort

```cpp
void mergeWithCount(vector<pair<int,int>>& arr, int left, int mid, int right,
                    vector<int>& count) {
    vector<pair<int,int>> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i].first <= arr[j].first) {
            // Elements from j to right are greater
            count[arr[i].second] += (j - mid - 1);
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        count[arr[i].second] += (right - mid);
        temp[k++] = arr[i++];
    }

    while (j <= right)
        temp[k++] = arr[j++];

    for (int i = 0; i < temp.size(); i++)
        arr[left + i] = temp[i];
}
```

## When to Use Which Algorithm

### Use Bubble Sort when:
- Array is very small (< 10 elements)
- Array is nearly sorted
- Simplicity is more important than efficiency
- Teaching/learning purposes

### Use Merge Sort when:
- **Stability is required**
- **Guaranteed O(n log n)** is needed
- Sorting **linked lists**
- **External sorting** (data doesn't fit in memory)
- **Parallel processing** (easily parallelizable)

### Use Quick Sort when:
- **Average case performance** matters most
- **Memory is limited** (in-place sorting)
- Sorting **arrays** (not linked lists)
- **Cache performance** is important
- Data is **randomly ordered**

## Key Takeaways

1. **Bubble Sort is O(n²)** - too slow for large datasets
2. **Merge Sort guarantees O(n log n)** but uses O(n) extra space
3. **Quick Sort is fastest in practice** but has O(n²) worst case
4. **Divide and conquer** is powerful for many problems beyond sorting
5. **Choose algorithm based on requirements**: stability, space, worst-case guarantees
6. **Quick select finds kth element** in O(n) average time
7. **Inversion counting** measures "sortedness" of array
8. **Both algorithms use recursion** and divide-and-conquer paradigm

## Common Questions

### Q1: Why is Quick Sort faster than Merge Sort in practice?
**Answer:** Quick Sort has better cache locality and fewer data movements. It partitions in-place, while Merge Sort copies data to temporary arrays. The constant factors in O(n log n) are smaller for Quick Sort.

### Q2: When would Merge Sort be better than Quick Sort?
**Answer:** When you need:
- Guaranteed O(n log n) performance (no worst case O(n²))
- Stable sorting (preserve order of equal elements)
- Sorting linked lists (no random access needed)
- External sorting (sorting data on disk)

### Q3: Can we avoid Quick Sort's O(n²) worst case?
**Answer:** Yes, by:
- Using random pivot selection
- Using median-of-three pivot selection
- Using introsort (switches to heap sort when recursion gets too deep)

### Q4: Why is finding inversions useful?
**Answer:** Inversions measure how "unsorted" an array is. Applications include:
- Collaborative filtering (recommendation systems)
- Measuring similarity between rankings
- Detecting anomalies in data

### Q5: Is recursion necessary for these algorithms?
**Answer:** No, both can be implemented iteratively using explicit stacks, but recursive versions are simpler and more intuitive.

## Practice Problems

1. Implement Quick Sort with random pivot selection
2. Count inversions in an array using merge sort
3. Find kth largest element using quick select
4. Sort an array of 0s, 1s, and 2s (Dutch National Flag problem)
5. Merge k sorted arrays using merge sort approach
6. Find median of two sorted arrays
7. Count of smaller elements after self
8. Sort array by increasing frequency
