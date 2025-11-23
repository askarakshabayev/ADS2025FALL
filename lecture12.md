# Lecture 12: Minimum Spanning Trees (Kruskal and Prim)

## What Is a Minimum Spanning Tree?

Given a connected, undirected, weighted graph \(G = (V, E)\), a **spanning tree** is a subgraph that:
- Includes all vertices in \(V\)
- Is a tree (no cycles)
- Has exactly \(|V| - 1\) edges

A **minimum spanning tree (MST)** is the spanning tree with the smallest possible total edge weight. MSTs are used in network design (roads, cables), clustering, image segmentation, and approximations for hard optimization problems.

### Example Graph
```
   (1)    4      (2)
 A ----- B ----- C
  \3   2 |     6/
   \    |5    /
    \   |   /
      D --- E
        1
```
Possible MST edges: AB(1), AD(3), BD(2), CE(6) with total cost 12.

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

### C++ Implementation (DSU + Kruskal)
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
    int n = 5; // vertices 0..4
    vector<Edge> edges = {
        {0, 1, 1}, {0, 3, 3}, {1, 3, 2}, {1, 2, 4}, {1, 4, 5}, {3, 4, 1}, {2, 4, 6}
    };

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
        cout << e.u << " - " << e.v << " (" << e.w << ")\n";
    }
    return 0;
}
```

### Kruskal Walkthrough
Edges sorted: (0,1,1), (3,4,1), (1,3,2), (0,3,3), (1,2,4), (1,4,5), (2,4,6)
```
Start: sets {0}, {1}, {2}, {3}, {4}
Add (0,1,1): merge {0},{1}
Add (3,4,1): merge {3},{4}
Add (1,3,2): merge {0,1} with {3,4} -> {0,1,3,4}
Skip (0,3,3): would create cycle
Add (1,2,4): merge {0,1,3,4} with {2} -> {0,1,2,3,4}
MST edges: (0,1), (3,4), (1,3), (1,2) with total cost 1+1+2+4 = 8
```

## Prim's Algorithm

### Idea
Grow the MST from an arbitrary start vertex by repeatedly picking the minimum weight edge that connects the current tree to a new vertex. A min-heap (priority queue) selects the next cheapest edge.

### Steps (heap-based)
1. Choose a start vertex `s`; push (0, s) into min-heap.
2. While heap not empty:
   - Pop the edge with minimum weight to vertex `v`.
   - If `v` is already in the tree, skip it.
   - Add `v` to the tree; add its edge weight to total cost.
   - For each neighbor `(to, w)` of `v`, push `(w, to)` into heap if `to` not yet in tree.
3. Stop when all vertices are included.

### Complexity
- Using adjacency list + binary heap: \(O(E \log V)\)
- Using adjacency matrix (no heap): \(O(V^2)\)

### C++ Implementation (Priority Queue Prim)
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5; // vertices 0..4
    vector<vector<pair<int,int>>> g(n);
    auto add_edge = [&](int u, int v, int w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };

    add_edge(0, 1, 1);
    add_edge(0, 3, 3);
    add_edge(1, 3, 2);
    add_edge(1, 2, 4);
    add_edge(1, 4, 5);
    add_edge(3, 4, 1);
    add_edge(2, 4, 6);

    vector<bool> in_mst(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    int start = 0;
    pq.push({0, start});
    int total = 0, chosen = 0;

    while (!pq.empty() && chosen < n) {
        auto [w, v] = pq.top(); pq.pop();
        if (in_mst[v]) continue;
        in_mst[v] = true;
        total += w;
        chosen++;

        for (auto [to, cost] : g[v]) {
            if (!in_mst[to]) pq.push({cost, to});
        }
    }

    cout << "MST cost: " << total << "\n";
    return 0;
}
```

### Prim Walkthrough (same graph)
```
Start at 0: heap = (0,0)
Pop (0,0): add 0, push edges (0,1,1), (0,3,3)
Pop (1,1): add 1, push (1,3,2), (1,2,4), (1,4,5)
Pop (2,3): add 3, push (3,4,1)
Pop (1,4): add 4, push (4,2,6)
Pop (4,2): add 2
Tree built with cost 0+1+2+1+4 = 8 (same as Kruskal)
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
