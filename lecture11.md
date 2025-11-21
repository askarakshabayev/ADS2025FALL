# Lecture 11: Depth-First Search and Its Applications

## Introduction to Depth-First Search (DFS)

**Depth-First Search (DFS)** is a fundamental graph traversal algorithm that explores as far as possible along each branch before backtracking.

Unlike BFS which explores level by level, DFS goes **deep** into the graph before exploring neighbors.

### DFS vs BFS

| Feature | DFS | BFS |
|---------|-----|-----|
| **Data Structure** | Stack (or recursion) | Queue |
| **Traversal** | Depth first | Level by level |
| **Implementation** | Recursion or explicit stack | Queue |
| **Space** | O(H) where H is height | O(W) where W is width |
| **Shortest Path** | No | Yes (unweighted) |
| **Use Cases** | Cycle detection, topological sort, path finding | Shortest path, level order |

### DFS Visualization

Graph:
```
        0
       / \
      1   2
     / \   \
    3   4   5
```

DFS starting from vertex 0:
```
Visit order: 0 → 1 → 3 → 4 → 2 → 5

Path taken:
1. Start at 0
2. Go to 1 (first neighbor of 0)
3. Go to 3 (first neighbor of 1)
4. Backtrack to 1
5. Go to 4 (second neighbor of 1)
6. Backtrack to 0
7. Go to 2 (second neighbor of 0)
8. Go to 5 (first neighbor of 2)
```

## DFS Algorithm

### Recursive Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
int n;

void DFS(int v) {
    // Mark current vertex as visited
    visited[v] = true;
    cout << v << " ";

    // Visit all neighbors
    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u]) {
            DFS(u);
        }
    }
}

int main() {
    n = 6;

    // Initialize visited array
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Add edges
    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[0].push_back(2);
    adj[2].push_back(0);

    adj[1].push_back(3);
    adj[3].push_back(1);

    adj[1].push_back(4);
    adj[4].push_back(1);

    adj[2].push_back(5);
    adj[5].push_back(2);

    cout << "DFS traversal: ";
    DFS(0);
    cout << endl;

    return 0;
}
```

## DFS Step-by-Step Example

**Graph:**
```
    0 --- 1 --- 3
    |     |
    2 --- 4
```

**DFS from vertex 0:**

```
Initial:
  visited = [false, false, false, false, false]
  stack (call stack) = []

Step 1: Visit 0
  visited = [true, false, false, false, false]
  Output: 0
  Neighbors of 0: [1, 2]
  Call DFS(1)

Step 2: Visit 1
  visited = [true, true, false, false, false]
  Output: 0 1
  Neighbors of 1: [0, 3, 4]
  0 is visited, skip
  Call DFS(3)

Step 3: Visit 3
  visited = [true, true, false, true, false]
  Output: 0 1 3
  Neighbors of 3: [1]
  1 is visited, return

Step 4: Back to 1, next neighbor is 4
  Call DFS(4)

Step 5: Visit 4
  visited = [true, true, false, true, true]
  Output: 0 1 3 4
  Neighbors of 4: [1, 2]
  1 is visited
  Call DFS(2)

Step 6: Visit 2
  visited = [true, true, true, true, true]
  Output: 0 1 3 4 2
  Neighbors of 2: [0, 4]
  Both visited, return

Final output: 0 1 3 4 2
```

## Application 1: Counting Connected Components

A **connected component** is a maximal set of vertices where each pair is connected by a path.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
int n;

void DFS(int v) {
    visited[v] = true;
    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u]) {
            DFS(u);
        }
    }
}

int countComponents() {
    // Initialize visited array
    for (int i = 0; i < n; i++)
        visited[i] = false;

    int components = 0;

    // Try to start DFS from each unvisited vertex
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS(i);
            components++;
        }
    }

    return components;
}

int main() {
    n = 7;

    // Component 1: 0-1-2
    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    // Component 2: 3-4
    adj[3].push_back(4);
    adj[4].push_back(3);

    // Component 3: 5-6
    adj[5].push_back(6);
    adj[6].push_back(5);

    cout << "Number of connected components: " << countComponents() << endl;

    return 0;
}
```

**Example:**
```
Graph:
    0 --- 1 --- 2     3 --- 4     5 --- 6

Component 1: {0, 1, 2}
Component 2: {3, 4}
Component 3: {5, 6}

Output: 3 components
```

## Application 2: Checking if Graph is Bipartite

A **bipartite graph** can be colored with 2 colors such that no two adjacent vertices have the same color.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
int color[MAXN];  // 0 = uncolored, 1 = color1, 2 = color2
int n;

bool DFS_bipartite(int v, int c) {
    color[v] = c;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];

        if (color[u] == 0) {
            // Not colored yet, color with opposite color
            if (!DFS_bipartite(u, 3 - c))  // 3-1=2, 3-2=1
                return false;
        }
        else if (color[u] == c) {
            // Same color as current vertex - not bipartite
            return false;
        }
    }

    return true;
}

bool isBipartite() {
    // Initialize color array
    for (int i = 0; i < n; i++)
        color[i] = 0;

    // Check all components
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (!DFS_bipartite(i, 1))
                return false;
        }
    }

    return true;
}

int main() {
    // Example 1: Bipartite graph
    n = 4;
    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[0].push_back(3);
    adj[3].push_back(0);

    adj[2].push_back(1);
    adj[1].push_back(2);

    adj[2].push_back(3);
    adj[3].push_back(2);

    cout << "Graph 1 is ";
    if (isBipartite())
        cout << "bipartite" << endl;
    else
        cout << "NOT bipartite" << endl;

    // Example 2: Not bipartite (triangle)
    for (int i = 0; i < MAXN; i++)
        adj[i].clear();

    n = 3;
    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[2].push_back(0);
    adj[0].push_back(2);

    cout << "Graph 2 (triangle) is ";
    if (isBipartite())
        cout << "bipartite" << endl;
    else
        cout << "NOT bipartite" << endl;

    return 0;
}
```

**Key Idea:**
- Try to color graph with 2 colors using DFS
- If we can color the entire graph without conflicts, it's bipartite
- If we find two adjacent vertices with same color, it's NOT bipartite

## Application 3: Cycle Detection

### Cycle Detection in Undirected Graph

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
int n;

bool DFS_cycle(int v, int parent) {
    visited[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];

        if (!visited[u]) {
            if (DFS_cycle(u, v))
                return true;
        }
        else if (u != parent) {
            // Visited vertex that is not parent = cycle found
            return true;
        }
    }

    return false;
}

bool hasCycle() {
    // Initialize visited array
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Check all components
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (DFS_cycle(i, -1))
                return true;
        }
    }

    return false;
}

int main() {
    // Example 1: Graph with cycle
    n = 4;
    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[2].push_back(3);
    adj[3].push_back(2);

    adj[3].push_back(0);
    adj[0].push_back(3);

    cout << "Graph ";
    if (hasCycle())
        cout << "has a cycle" << endl;
    else
        cout << "does NOT have a cycle" << endl;

    return 0;
}
```

### Cycle Detection in Directed Graph

For directed graphs, we need to track vertices in current path:

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
bool recStack[MAXN];  // Vertices in current recursion stack
int n;

bool DFS_cycle_directed(int v) {
    visited[v] = true;
    recStack[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];

        if (!visited[u]) {
            if (DFS_cycle_directed(u))
                return true;
        }
        else if (recStack[u]) {
            // Found back edge to vertex in current path
            return true;
        }
    }

    recStack[v] = false;
    return false;
}

bool hasCycleDirected() {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (DFS_cycle_directed(i))
                return true;
        }
    }

    return false;
}

int main() {
    n = 4;

    // Directed edges
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(3);
    adj[3].push_back(1);  // Creates cycle: 1 -> 2 -> 3 -> 1

    cout << "Directed graph ";
    if (hasCycleDirected())
        cout << "has a cycle" << endl;
    else
        cout << "does NOT have a cycle" << endl;

    return 0;
}
```

## Application 4: Topological Sort

**Topological sorting** of a Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge (u, v), vertex u comes before v in the ordering.

### Applications of Topological Sort

- **Task scheduling** with dependencies
- **Course prerequisites**
- **Build systems** (compile order)
- **Package dependency resolution**

### Example

```
Task dependencies:
A → B (A must be done before B)
A → C
B → D
C → D

One valid topological order: A, B, C, D
Another valid order: A, C, B, D
```

### DFS-based Topological Sort

**Key Idea:** Use DFS and add vertex to result when all its descendants are processed (post-order).

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
stack<int> result;
int n;

void DFS_topo(int v) {
    visited[v] = true;

    // Visit all neighbors first
    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u]) {
            DFS_topo(u);
        }
    }

    // Add current vertex to stack after visiting all descendants
    result.push(v);
}

void topologicalSort() {
    // Initialize
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Process all vertices
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS_topo(i);
        }
    }

    // Print result
    cout << "Topological order: ";
    while (!result.empty()) {
        cout << result.top() << " ";
        result.pop();
    }
    cout << endl;
}

int main() {
    n = 6;

    // DAG example
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    cout << "Graph (directed):" << endl;
    cout << "5 -> 2, 0" << endl;
    cout << "4 -> 0, 1" << endl;
    cout << "2 -> 3" << endl;
    cout << "3 -> 1" << endl;
    cout << endl;

    topologicalSort();

    return 0;
}
```

**Output:** `5 4 2 3 1 0` (one possible topological order)

### Topological Sort Algorithm Steps

```
1. Initialize all vertices as unvisited
2. For each unvisited vertex v:
   a. Call DFS(v)
   b. In DFS, visit all descendants first (recursively)
   c. After visiting all descendants, push v to stack
3. The stack contains topological order (top to bottom)
```

### Important Notes

- Topological sort only works on **Directed Acyclic Graphs (DAG)**
- If graph has a cycle, topological sort is not possible
- There can be **multiple valid** topological orderings
- Time complexity: **O(V + E)**

## Application 5: Finding Paths

### Find if Path Exists

```cpp
bool hasPath(int start, int end) {
    // Initialize visited array
    for (int i = 0; i < n; i++)
        visited[i] = false;

    return DFS_path(start, end);
}

bool DFS_path(int v, int target) {
    if (v == target)
        return true;

    visited[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u]) {
            if (DFS_path(u, target))
                return true;
        }
    }

    return false;
}
```

### Find and Print Path

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
vector<int> path;
int n;

bool DFS_printPath(int v, int target) {
    visited[v] = true;
    path.push_back(v);

    if (v == target) {
        return true;
    }

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u]) {
            if (DFS_printPath(u, target))
                return true;
        }
    }

    // Backtrack
    path.pop_back();
    return false;
}

void findPath(int start, int end) {
    for (int i = 0; i < n; i++)
        visited[i] = false;

    path.clear();

    if (DFS_printPath(start, end)) {
        cout << "Path from " << start << " to " << end << ": ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path exists" << endl;
    }
}

int main() {
    n = 6;

    // Add edges
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[0].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[1].push_back(4);
    adj[4].push_back(1);
    adj[2].push_back(5);
    adj[5].push_back(2);

    findPath(0, 5);
    findPath(3, 5);

    return 0;
}
```

## Application 6: Finding Strongly Connected Components (SCC)

A **strongly connected component** in a directed graph is a maximal set of vertices where every vertex is reachable from every other vertex.

### Kosaraju's Algorithm

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
vector<int> adj_rev[MAXN];  // Reversed graph
bool visited[MAXN];
stack<int> finishOrder;
int n;

void DFS1(int v) {
    visited[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u])
            DFS1(u);
    }

    finishOrder.push(v);
}

void DFS2(int v, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);

    for (int i = 0; i < adj_rev[v].size(); i++) {
        int u = adj_rev[v][i];
        if (!visited[u])
            DFS2(u, component);
    }
}

void findSCC() {
    // Step 1: Do DFS and fill finish order
    for (int i = 0; i < n; i++)
        visited[i] = false;

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            DFS1(i);
    }

    // Step 2: Do DFS on reversed graph in order of finish time
    for (int i = 0; i < n; i++)
        visited[i] = false;

    int sccCount = 0;
    while (!finishOrder.empty()) {
        int v = finishOrder.top();
        finishOrder.pop();

        if (!visited[v]) {
            vector<int> component;
            DFS2(v, component);

            sccCount++;
            cout << "SCC " << sccCount << ": ";
            for (int i = 0; i < component.size(); i++) {
                cout << component[i] << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    n = 5;

    // Add directed edges
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(4);

    // Create reversed graph
    for (int v = 0; v < n; v++) {
        for (int i = 0; i < adj[v].size(); i++) {
            int u = adj[v][i];
            adj_rev[u].push_back(v);
        }
    }

    findSCC();

    return 0;
}
```

## Application 7: Bridges and Articulation Points

### Bridge (Cut Edge)

An edge whose removal increases the number of connected components.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
int disc[MAXN];  // Discovery time
int low[MAXN];   // Lowest discovery time reachable
int timer = 0;
int n;

void DFS_bridge(int v, int parent) {
    visited[v] = true;
    disc[v] = low[v] = timer++;

    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];

        if (u == parent)
            continue;

        if (visited[u]) {
            low[v] = min(low[v], disc[u]);
        } else {
            DFS_bridge(u, v);
            low[v] = min(low[v], low[u]);

            // If lowest reachable from u is higher than disc[v],
            // then v-u is a bridge
            if (low[u] > disc[v]) {
                cout << "Bridge: " << v << " - " << u << endl;
            }
        }
    }
}

void findBridges() {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        disc[i] = -1;
        low[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            DFS_bridge(i, -1);
    }
}

int main() {
    n = 5;

    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[2].push_back(0);
    adj[0].push_back(2);

    adj[1].push_back(3);
    adj[3].push_back(1);

    adj[3].push_back(4);
    adj[4].push_back(3);

    findBridges();

    return 0;
}
```

## DFS Time and Space Complexity

**Time Complexity:**
- **Adjacency List**: O(V + E)
  - Visit each vertex once: O(V)
  - Explore each edge once: O(E)
- **Adjacency Matrix**: O(V²)

**Space Complexity:**
- **Recursive**: O(V) for recursion stack + O(V) for visited array = O(V)
- **Iterative**: O(V) for explicit stack + O(V) for visited array = O(V)

## Summary of DFS Applications

| Application | Use Case | Time Complexity |
|-------------|----------|-----------------|
| **Traversal** | Visit all vertices | O(V + E) |
| **Connected Components** | Count/find components | O(V + E) |
| **Bipartite Check** | 2-coloring | O(V + E) |
| **Cycle Detection** | Find cycles | O(V + E) |
| **Topological Sort** | Order tasks with dependencies | O(V + E) |
| **Path Finding** | Check if path exists | O(V + E) |
| **SCC** | Strongly connected components | O(V + E) |
| **Bridges** | Find critical edges | O(V + E) |
| **Articulation Points** | Find critical vertices | O(V + E) |

## When to Use DFS vs BFS

**Use DFS when:**
- Finding cycles
- Topological sorting
- Finding strongly connected components
- Solving puzzles with backtracking
- Memory is limited (DFS uses less space for wide graphs)
- Exploring all paths

**Use BFS when:**
- Finding shortest path (unweighted)
- Level-order traversal
- Finding distance from source
- Finding if two vertices are connected in minimum steps
- Graph is very deep

## Key Takeaways

1. **DFS explores depth-first** using stack or recursion
2. **DFS is versatile** - many graph problems can be solved with DFS
3. **Topological sort requires DFS** on a DAG
4. **Cycle detection** is different for directed and undirected graphs
5. **Bipartite check** can be done with DFS or BFS
6. **DFS complexity is O(V + E)** with adjacency list
7. **DFS is perfect for** path finding, cycle detection, and topological sorting

## Practice Problems

1. Implement DFS recursively and iteratively
2. Count connected components using DFS
3. Check if a graph is bipartite
4. Detect cycle in undirected graph
5. Detect cycle in directed graph
6. Implement topological sort
7. Find all paths between two vertices
8. Find bridges in a graph
9. Find articulation points
10. Check if a directed graph is a DAG
11. Find strongly connected components (Kosaraju's algorithm)
12. Find the number of islands (2D grid DFS)
13. Solve a maze using DFS
14. Clone a graph
15. Find if there's a path with given sum in a tree
