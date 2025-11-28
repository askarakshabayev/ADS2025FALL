# Lecture 12: Minimum Spanning Trees (Kruskal and Prim)

## What Is a Minimum Spanning Tree?

Given a connected, undirected, weighted graph \(G = (V, E)\), a **spanning tree** is a subgraph that:
- Includes all vertices in \(V\)
- Is a tree (no cycles)
- Has exactly \(|V| - 1\) edges

A **minimum spanning tree (MST)** is the spanning tree with the smallest possible total edge weight. MSTs are used in network design (roads, cables), clustering, image segmentation, and approximations for hard optimization problems.

### Example Graph (n = 6, m = 9)
Input format: `n m` followed by lines `x y w` (1-indexed vertices).
```
6 9
1 2 1
1 3 5
1 4 8
1 5 3
2 4 9
2 5 1
2 6 2
3 4 4
5 6 6
```
MST edges (weight): (1,2,1), (2,5,1), (2,6,2), (3,4,4), (1,3,5) with total cost 13.

## Key Properties of MSTs
- An MST has exactly \(|V| - 1\) edges and no cycles.
- Adding any edge to the MST creates a cycle; removing any MST edge disconnects the graph.
- **Cut property:** For any cut (partition of vertices), the lightest edge crossing the cut belongs to at least one MST.
- **Cycle property:** In any cycle, the heaviest edge cannot be in an MST.

## Kruskal's Algorithm

### Idea
Sort edges by weight and add them one by one, skipping edges that would create a cycle. A **Disjoint Set Union (DSU)** (also called Union-Find) quickly detects cycles.

### Steps
1. Sort all edges in non-decreasing order of weight.
2. Initialize DSU so each vertex is its own set.
3. For each edge (u, v, w) in order:
   - If `find(u) != find(v)`, add the edge to the MST and union the sets.
   - Stop when \(|V| - 1\) edges are chosen.

### Complexity
- Sorting edges: \(O(E \log E)\)
- DSU operations: almost \(O(1)\) (inverse Ackermann) per operation
- Total: \(O(E \log E)\)

### C++ Implementation (input-driven Kruskal)
```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find(parent[v]); // path compression
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;          // already in same set
        if (rank[a] < rank[b]) swap(a, b); // union by rank
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    edges.reserve(m);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        edges.push_back({x - 1, y - 1, w});
    }

    sort(edges.begin(), edges.end());
    DSU dsu(n);

    int mst_cost = 0;
    vector<Edge> mst;

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            mst_cost += e.w;
        }
        if ((int)mst.size() == n - 1) break;
    }

    cout << "MST cost: " << mst_cost << "\nEdges:\n";
    for (auto &e : mst) {
        cout << e.u + 1 << " - " << e.v + 1 << " (" << e.w << ")\n";
    }
    return 0;
}
```

### Kruskal Walkthrough
Edges sorted: (1,2,1), (2,5,1), (2,6,2), (1,5,3), (3,4,4), (1,3,5), (5,6,6), (1,4,8), (2,4,9)
```
Start: sets {1}, {2}, {3}, {4}, {5}, {6}
Add (1,2,1): merge {1},{2}
Add (2,5,1): merge {1,2} with {5}
Add (2,6,2): merge {1,2,5} with {6}
Skip (1,5,3): would create cycle
Add (3,4,4): merge {3},{4}
Add (1,3,5): merge {1,2,5,6} with {3,4}
MST edges: (1,2), (2,5), (2,6), (3,4), (1,3) with total cost 13
```

## Prim's Algorithm

### Idea
Grow the MST from an arbitrary start vertex by repeatedly picking the minimum weight edge that connects the current tree to a new vertex. Below is the dense \(O(V^2)\) version (scan all vertices to find the next minimum key). A min-heap version improves to \(O(E \log V)\).

### Steps (dense \(O(V^2)\))
1. Set `key[start] = 0`, others to infinity.
2. Repeat `n` times:
   - Pick unused vertex `v` with smallest `key[v]`.
   - Mark `v` used; for each neighbor `(to, w)`, if `w < key[to]`, update `key[to]` and record parent.
3. Keys of chosen edges and parents describe the MST.

### Complexity
- Dense scan (below): \(O(V^2)\)
- With a binary heap: \(O(E \log V)\)

### C++ Implementation (dense Prim on example input)
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        --x; --y;
        g[x].push_back({y, w});
        g[y].push_back({x, w});
    }

    const int INF = 1e9;
    vector<int> key(n, INF), parent(n, -1), used(n, 0);

    key[0] = 0; // start from vertex 0
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && (v == -1 || key[j] < key[v])) v = j;
        }
        used[v] = 1;
        for (auto [to, w] : g[v]) {
            if (!used[to] && w < key[to]) {
                key[to] = w;
                parent[to] = v;
            }
        }
    }

    int total = 0;
    for (int w : key) total += w;

    cout << "MST cost: " << total << "\nEdges:\n";
    for (int v = 1; v < n; v++) {
        cout << parent[v] + 1 << " - " << v + 1 << " (" << key[v] << ")\n";
    }
    return 0;
}
```

### Prim Walkthrough (example graph)
```
Start at 1 (vertex 0 internally): candidate edges (1,2,1), (1,3,5), (1,4,8), (1,5,3)
Pick 2 via (1,2,1); update candidates with edges from 2: (2,5,1), (2,6,2)
Pick 5 via (2,5,1); update edge to 6 remains weight 2
Pick 6 via (2,6,2)
Pick 3 via (1,3,5); update 3->4 edge weight 4
Pick 4 via (3,4,4)
MST edges: (1,2), (2,5), (2,6), (1,3), (3,4) with total cost 13
```

## Kruskal vs Prim
| Algorithm | Best For | Data Structures | Complexity |
|-----------|----------|-----------------|------------|
| Kruskal   | Sparse graphs, edge list input | Sort edges + DSU | \(O(E \log E)\) |
| Prim      | Dense graphs or adjacency list | Min-heap + visited set | \(O(E \log V)\) (or \(O(V^2)\)) |

## Takeaways
- MSTs connect all vertices with minimum total weight and no cycles.
- Kruskal: sort edges, add lightest non-cycle edges using DSU.
- Prim: grow from a start vertex, always choose the lightest outgoing edge.
- Both algorithms yield the same MST cost on connected undirected weighted graphs.
