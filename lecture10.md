# Lecture 10: Introduction to Graphs and BFS

## Introduction to Graphs

A **graph** is a data structure that consists of:
- A set of **vertices** (or **nodes**)
- A set of **edges** connecting pairs of vertices

**Notation:** G = (V, E)
- V = set of vertices
- E = set of edges

**Example:**
```
Vertices: {A, B, C, D}
Edges: {(A,B), (B,C), (C,D), (A,D)}

Visual representation:
    A --- B
    |     |
    D --- C
```

### Why Use Graphs?

Graphs are used to represent relationships and connections in real-world problems:

- **Social networks**: People are vertices, friendships are edges
- **Maps and navigation**: Cities are vertices, roads are edges
- **Computer networks**: Computers are vertices, connections are edges
- **Web pages**: Pages are vertices, hyperlinks are edges
- **Dependencies**: Tasks are vertices, dependencies are edges

## Types of Graphs

### 1. Directed Graph (Digraph)

Edges have a **direction** (from one vertex to another).

**Example:**
```
    A --> B
    ↑     ↓
    D <-- C

Edges: (A,B), (B,C), (C,D), (D,A)
```

**Applications:**
- Web page links (one-way)
- Task dependencies
- State transitions

### 2. Undirected Graph

Edges have **no direction** (bidirectional connection).

**Example:**
```
    A --- B
    |     |
    D --- C

Edges: (A,B), (B,C), (C,D), (A,D)
```

**Applications:**
- Social networks (friendship is mutual)
- Road networks (roads are two-way)

### 3. Weighted Graph

Edges have **weights** (costs, distances, capacities).

**Example:**
```
    A --5-- B
    |       |
    3       7
    |       |
    D --2-- C

Edges: (A,B,5), (A,D,3), (B,C,7), (C,D,2)
```

**Applications:**
- Road networks (distances)
- Network routing (latency)
- Flight routes (costs)

### 4. Unweighted Graph

All edges have **equal weight** (or weight = 1).

**Example:**
```
    A --- B
    |     |
    D --- C
```

### 5. Cyclic Graph

Contains at least one **cycle** (path from a vertex back to itself).

**Example:**
```
    A --- B
    |     |
    D --- C

Cycle: A → B → C → D → A
```

### 6. Acyclic Graph

Contains **no cycles**.

**Example:**
```
    A --- B --- C
          |
          D
```

**DAG (Directed Acyclic Graph)**: Directed graph with no cycles
- Used in task scheduling
- Dependency resolution
- Topological sorting

### 7. Connected Graph

There is a **path** between every pair of vertices.

**Example:**
```
    A --- B
    |     |
    D --- C
```

### 8. Disconnected Graph

Some vertices are **not reachable** from others.

**Example:**
```
    A --- B     E --- F
    |     |
    D --- C
```

### 9. Complete Graph

Every pair of vertices is **directly connected**.

**Example:**
```
    A --- B
    |\   /|
    | \ / |
    |  X  |
    | / \ |
    |/   \|
    D --- C

Edges: (A,B), (A,C), (A,D), (B,C), (B,D), (C,D)
```

### 10. Tree

A **connected acyclic graph**.

**Example:**
```
        A
       / \
      B   C
     / \
    D   E
```

**Properties:**
- N vertices have exactly N-1 edges
- Exactly one path between any two vertices
- Removing any edge disconnects the graph

### 11. Bipartite Graph

Vertices can be divided into **two sets** such that edges only connect vertices from different sets.

**Example:**
```
Set 1: A, C
Set 2: B, D

    A     B
     \   / \
      \ /   \
       X     E
      / \   /
     /   \ /
    C     D
```

**Applications:**
- Matching problems
- Job assignments

## Graph Terminology

- **Vertex (Node)**: A point in the graph
- **Edge**: A connection between two vertices
- **Adjacent vertices**: Two vertices connected by an edge
- **Degree**: Number of edges connected to a vertex
  - **In-degree**: Number of incoming edges (directed graph)
  - **Out-degree**: Number of outgoing edges (directed graph)
- **Path**: Sequence of vertices connected by edges
- **Cycle**: Path that starts and ends at the same vertex
- **Connected**: Path exists between every pair of vertices
- **Component**: Maximal connected subgraph

## Graph Representations

### 1. Adjacency Matrix

A **2D array** where `matrix[i][j]` indicates if there's an edge from vertex i to vertex j.

**For unweighted graph:**
- `matrix[i][j] = 1` if edge exists
- `matrix[i][j] = 0` if no edge

**For weighted graph:**
- `matrix[i][j] = weight` if edge exists
- `matrix[i][j] = ∞` or `0` if no edge

**Example:**

Graph:
```
    0 --- 1
    |     |
    3 --- 2
```

Adjacency Matrix (undirected):
```
     0  1  2  3
  0 [0, 1, 0, 1]
  1 [1, 0, 1, 0]
  2 [0, 1, 0, 1]
  3 [1, 0, 1, 0]
```

**Implementation:**

```cpp
#include <iostream>
using namespace std;

const int MAXN = 100;  // Maximum number of vertices
int adj[MAXN][MAXN];   // Adjacency matrix
int n;                 // Number of vertices

// Add edge (undirected)
void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

// Add directed edge
void addDirectedEdge(int u, int v) {
    adj[u][v] = 1;
}

// Add weighted edge
void addWeightedEdge(int u, int v, int weight) {
    adj[u][v] = weight;
    adj[v][u] = weight;
}

// Check if edge exists
bool hasEdge(int u, int v) {
    return adj[u][v] != 0;
}

// Print adjacency matrix
void printMatrix() {
    cout << "Adjacency Matrix:" << endl;
    cout << "   ";
    for (int i = 0; i < n; i++)
        cout << i << " ";
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << i << " [";
        for (int j = 0; j < n; j++) {
            cout << adj[i][j];
            if (j < n - 1) cout << " ";
        }
        cout << "]" << endl;
    }
}

int main() {
    n = 4;  // Number of vertices

    // Initialize matrix with zeros
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    // Add edges
    addEdge(0, 1);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(2, 3);

    printMatrix();

    // Print neighbors of vertex 0
    cout << "\nNeighbors of vertex 0: ";
    for (int i = 0; i < n; i++) {
        if (adj[0][i] != 0) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}
```

**Complexity:**
- **Space**: O(V²)
- **Add edge**: O(1)
- **Check edge**: O(1)
- **Get all neighbors**: O(V)
- **Iterate all edges**: O(V²)

**Advantages:**
- Fast edge lookup - O(1)
- Simple to implement
- Good for dense graphs

**Disadvantages:**
- Wastes space for sparse graphs
- O(V²) space even if few edges
- Iterating all edges takes O(V²)

### 2. Adjacency List

An **array of lists** where `adj[i]` contains all neighbors of vertex i.

**Example:**

Graph:
```
    0 --- 1
    |     |
    3 --- 2
```

Adjacency List:
```
0: [1, 3]
1: [0, 2]
2: [1, 3]
3: [0, 2]
```

**Implementation:**

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;     // Maximum number of vertices
vector<int> adj[MAXN];    // Adjacency list
int n;                    // Number of vertices

// Add edge (undirected)
void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Add directed edge
void addDirectedEdge(int u, int v) {
    adj[u].push_back(v);
}

// Check if edge exists
bool hasEdge(int u, int v) {
    for (int i = 0; i < adj[u].size(); i++) {
        if (adj[u][i] == v)
            return true;
    }
    return false;
}

// Print adjacency list
void printList() {
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": [";
        for (int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j];
            if (j < adj[i].size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }
}

int main() {
    n = 4;  // Number of vertices

    // Add edges
    addEdge(0, 1);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(2, 3);

    printList();

    // Print neighbors of vertex 0
    cout << "\nNeighbors of vertex 0: ";
    for (int i = 0; i < adj[0].size(); i++) {
        cout << adj[0][i] << " ";
    }
    cout << endl;

    return 0;
}
```

**For weighted graphs:**

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;
vector<pair<int, int>> adj[MAXN];  // {neighbor, weight}
int n;

void addWeightedEdge(int u, int v, int weight) {
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight});
}

void printWeightedList() {
    cout << "Weighted Adjacency List:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": [";
        for (int j = 0; j < adj[i].size(); j++) {
            cout << "(" << adj[i][j].first << "," << adj[i][j].second << ")";
            if (j < adj[i].size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }
}

int main() {
    n = 4;

    addWeightedEdge(0, 1, 5);
    addWeightedEdge(0, 3, 3);
    addWeightedEdge(1, 2, 7);
    addWeightedEdge(2, 3, 2);

    printWeightedList();

    return 0;
}
```

**Complexity:**
- **Space**: O(V + E)
- **Add edge**: O(1)
- **Check edge**: O(degree(v))
- **Get all neighbors**: O(degree(v))
- **Iterate all edges**: O(V + E)

**Advantages:**
- Space efficient for sparse graphs
- Fast iteration over neighbors
- Most common representation

**Disadvantages:**
- Slower edge lookup than matrix
- More complex to implement

### 3. Edge List

A **list of edges**, where each edge is represented as a pair (or triple for weighted graphs).

**Example:**

Graph:
```
    0 --- 1
    |     |
    3 --- 2
```

Edge List:
```
[(0, 1), (0, 3), (1, 2), (2, 3)]
```

**Implementation:**

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v;
    int weight;
};

const int MAXE = 1000;  // Maximum number of edges
Edge edges[MAXE];
int edgeCount = 0;
int n;  // Number of vertices

// Add edge
void addEdge(int u, int v, int weight = 1) {
    edges[edgeCount].u = u;
    edges[edgeCount].v = v;
    edges[edgeCount].weight = weight;
    edgeCount++;
}

// Print edge list
void printEdges() {
    cout << "Edge List:" << endl;
    for (int i = 0; i < edgeCount; i++) {
        cout << "(" << edges[i].u << ", " << edges[i].v;
        if (edges[i].weight != 1)
            cout << ", " << edges[i].weight;
        cout << ")" << endl;
    }
}

int main() {
    n = 4;  // Number of vertices

    // Add edges
    addEdge(0, 1);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(2, 3);

    printEdges();

    cout << "\nTotal edges: " << edgeCount << endl;

    return 0;
}
```

**Complexity:**
- **Space**: O(E)
- **Add edge**: O(1)
- **Check edge**: O(E)
- **Iterate all edges**: O(E)

**Advantages:**
- Very simple
- Space efficient
- Good for edge-focused algorithms (Kruskal's MST)

**Disadvantages:**
- Slow neighbor lookup
- Slow edge existence check
- Not good for traversal algorithms

### Comparison of Representations

| Operation | Adjacency Matrix | Adjacency List | Edge List |
|-----------|-----------------|----------------|-----------|
| **Space** | O(V²) | O(V + E) | O(E) |
| **Add edge** | O(1) | O(1) | O(1) |
| **Check edge** | O(1) | O(degree) | O(E) |
| **Get neighbors** | O(V) | O(degree) | O(E) |
| **Iterate edges** | O(V²) | O(V + E) | O(E) |
| **Best for** | Dense graphs | Sparse graphs | Edge algorithms |

**When to use:**
- **Adjacency Matrix**: Dense graphs, frequent edge queries
- **Adjacency List**: Sparse graphs, traversal algorithms (most common)
- **Edge List**: Simple storage, edge-based algorithms

## Breadth-First Search (BFS)

**BFS** is a graph traversal algorithm that explores vertices **level by level**, starting from a source vertex.

### BFS Algorithm

1. Start from source vertex
2. Visit all neighbors (level 1)
3. Visit all neighbors of neighbors (level 2)
4. Continue until all reachable vertices are visited

**Uses a queue** (FIFO - First In First Out)

### BFS Visualization

Graph:
```
        0
       / \
      1   2
     / \   \
    3   4   5
```

BFS starting from vertex 0:
```
Level 0: [0]
Level 1: [1, 2]
Level 2: [3, 4, 5]

Visit order: 0 → 1 → 2 → 3 → 4 → 5
```

### BFS Algorithm Steps

```
1. Create a queue Q
2. Mark source vertex as visited
3. Enqueue source vertex
4. While Q is not empty:
   a. Dequeue vertex v from Q
   b. Process vertex v
   c. For each neighbor u of v:
      - If u is not visited:
        * Mark u as visited
        * Enqueue u
```

### BFS Implementation

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100;
vector<int> adj[MAXN];
bool visited[MAXN];
int n;

// BFS from source vertex
void BFS(int source) {
    queue<int> q;

    // Initialize visited array
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Start from source
    visited[source] = true;
    q.push(source);

    cout << "BFS traversal: ";

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        cout << v << " ";

        // Visit all neighbors
        for (int i = 0; i < adj[v].size(); i++) {
            int u = adj[v][i];
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }

    cout << endl;
}

// BFS with distance tracking
void BFS_with_distance(int source) {
    queue<int> q;
    int distance[MAXN];

    // Initialize
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        distance[i] = -1;
    }

    visited[source] = true;
    distance[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < adj[v].size(); i++) {
            int u = adj[v][i];
            if (!visited[u]) {
                visited[u] = true;
                distance[u] = distance[v] + 1;
                q.push(u);
            }
        }
    }

    cout << "Distances from vertex " << source << ":" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << ": ";
        if (distance[i] == -1)
            cout << "unreachable" << endl;
        else
            cout << distance[i] << endl;
    }
}

// BFS with parent tracking (for shortest path)
void BFS_with_path(int source, int target) {
    queue<int> q;
    int parent[MAXN];

    // Initialize
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    visited[source] = true;
    q.push(source);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (v == target)
            break;

        for (int i = 0; i < adj[v].size(); i++) {
            int u = adj[v][i];
            if (!visited[u]) {
                visited[u] = true;
                parent[u] = v;
                q.push(u);
            }
        }
    }

    // Reconstruct path
    if (!visited[target]) {
        cout << "No path exists" << endl;
        return;
    }

    vector<int> path;
    int current = target;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    cout << "Shortest path from " << source << " to " << target << ": ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}

int main() {
    n = 6;  // Number of vertices

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

    cout << "Graph structure:" << endl;
    cout << "    0" << endl;
    cout << "   / \\" << endl;
    cout << "  1   2" << endl;
    cout << " / \\   \\" << endl;
    cout << "3   4   5" << endl;
    cout << endl;

    BFS(0);
    cout << endl;

    BFS_with_distance(0);
    cout << endl;

    BFS_with_path(0, 5);

    return 0;
}
```

### BFS Step-by-Step Example

**Graph:**
```
    0 --- 1 --- 3
    |     |
    2 --- 4
```

**BFS from vertex 0:**

```
Initial:
  visited = [false, false, false, false, false]
  queue = []

Step 1: Start from vertex 0
  visited = [true, false, false, false, false]
  queue = [0]

Step 2: Dequeue 0, visit neighbors 1 and 2
  visited = [true, true, true, false, false]
  queue = [1, 2]
  Output: 0

Step 3: Dequeue 1, visit neighbors 3 and 4
  visited = [true, true, true, true, true]
  queue = [2, 3, 4]
  Output: 0 1

Step 4: Dequeue 2, no new neighbors
  queue = [3, 4]
  Output: 0 1 2

Step 5: Dequeue 3, no new neighbors
  queue = [4]
  Output: 0 1 2 3

Step 6: Dequeue 4, no new neighbors
  queue = []
  Output: 0 1 2 3 4

Final output: 0 1 2 3 4
```

### BFS Applications

#### 1. Shortest Path in Unweighted Graph

BFS finds the shortest path (minimum number of edges) from source to all other vertices.

```cpp
int shortestPath(Graph& g, int source, int target) {
    vector<bool> visited(n, false);
    vector<int> distance(n, -1);
    queue<int> q;

    visited[source] = true;
    distance[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (v == target)
            return distance[target];

        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                distance[u] = distance[v] + 1;
                q.push(u);
            }
        }
    }

    return -1;  // No path exists
}
```

#### 2. Check if Graph is Connected

```cpp
bool isConnected(Graph& g) {
    vector<bool> visited(n, false);
    queue<int> q;

    visited[0] = true;
    q.push(0);
    int count = 1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
                count++;
            }
        }
    }

    return count == n;
}
```

#### 3. Find Connected Components

```cpp
int countComponents(Graph& g) {
    vector<bool> visited(n, false);
    int components = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            components++;

            // BFS from vertex i
            queue<int> q;
            visited[i] = true;
            q.push(i);

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (int u : adj[v]) {
                    if (!visited[u]) {
                        visited[u] = true;
                        q.push(u);
                    }
                }
            }
        }
    }

    return components;
}
```

#### 4. Bipartite Graph Check

Check if graph can be colored with 2 colors.

```cpp
bool isBipartite(Graph& g) {
    vector<int> color(n, -1);
    queue<int> q;

    color[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : adj[v]) {
            if (color[u] == -1) {
                color[u] = 1 - color[v];
                q.push(u);
            } else if (color[u] == color[v]) {
                return false;  // Same color as neighbor
            }
        }
    }

    return true;
}
```

#### 5. Level Order Traversal

Print vertices level by level.

```cpp
void levelOrder(Graph& g, int source) {
    vector<bool> visited(n, false);
    queue<int> q;

    visited[source] = true;
    q.push(source);

    int level = 0;

    while (!q.empty()) {
        int size = q.size();
        cout << "Level " << level << ": ";

        for (int i = 0; i < size; i++) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int u : adj[v]) {
                if (!visited[u]) {
                    visited[u] = true;
                    q.push(u);
                }
            }
        }

        cout << endl;
        level++;
    }
}
```

### BFS Time and Space Complexity

**Time Complexity:**
- **Adjacency List**: O(V + E)
  - Visit each vertex once: O(V)
  - Explore each edge once: O(E)
- **Adjacency Matrix**: O(V²)
  - Visit each vertex once: O(V)
  - Check all possible edges: O(V²)

**Space Complexity:**
- Queue: O(V) in worst case
- Visited array: O(V)
- **Total**: O(V)

### BFS vs DFS

| Feature | BFS | DFS |
|---------|-----|-----|
| **Data Structure** | Queue (FIFO) | Stack (LIFO) or recursion |
| **Traversal** | Level by level | Depth first |
| **Shortest Path** | Yes (unweighted) | No |
| **Space** | O(V) | O(V) |
| **Time** | O(V + E) | O(V + E) |
| **Use Cases** | Shortest path, level order | Cycle detection, topological sort |

## Common Questions

### Q1: When should I use adjacency list vs adjacency matrix?
**Answer:**
- **Adjacency List**: Sparse graphs (few edges), most graph algorithms
- **Adjacency Matrix**: Dense graphs, when you need O(1) edge lookup

### Q2: Why does BFS find shortest path?
**Answer:** BFS explores vertices level by level. It visits all vertices at distance k before visiting any vertex at distance k+1. Therefore, the first time it reaches a vertex is guaranteed to be via the shortest path.

### Q3: Can BFS work on weighted graphs?
**Answer:** BFS finds shortest path in terms of number of edges. For weighted graphs, use Dijkstra's algorithm or Bellman-Ford instead.

### Q4: What's the difference between BFS and level order traversal?
**Answer:** They're essentially the same. Level order traversal is BFS that explicitly tracks levels.

### Q5: How to handle disconnected graphs in BFS?
**Answer:** Run BFS from each unvisited vertex to explore all components.

## Key Takeaways

1. **Graphs represent relationships** - vertices and edges
2. **Many types of graphs** - directed, undirected, weighted, cyclic, etc.
3. **Three main representations** - adjacency matrix, adjacency list, edge list
4. **Adjacency list is most common** - space efficient for sparse graphs
5. **BFS uses queue** - explores level by level
6. **BFS finds shortest path** - in unweighted graphs
7. **BFS complexity is O(V + E)** - with adjacency list
8. **BFS has many applications** - shortest path, connectivity, bipartite check

## Practice Problems

1. Implement all three graph representations
2. Find shortest path using BFS
3. Check if graph is connected
4. Count connected components
5. Check if graph is bipartite
6. Find distance between two vertices
7. Print all vertices at distance k from source
8. Find if path exists between two vertices
9. Find diameter of graph (longest shortest path)
10. Clone a graph using BFS
