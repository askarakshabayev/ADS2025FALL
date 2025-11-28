# Lecture 13: Single-Source and All-Pairs Shortest Paths

## Shortest Path Problem Overview
Given a weighted graph \(G = (V, E)\) with edge weights \(w(u, v)\):
- **Single-source shortest path (SSSP):** find the minimum-cost path from one source vertex \(s\) to all other vertices.
- **All-pairs shortest path (APSP):** find the minimum-cost path between every pair of vertices.
- Negative-weight edges are allowed in some algorithms, but negative cycles make shortest paths undefined.

---

## Dijkstra's Algorithm (Non-Negative Weights)
**Goal:** Single-source shortest paths when all edge weights are non-negative.

### Idea
Repeatedly pick the unvisited vertex with the smallest current distance, then relax all outgoing edges. This is the straightforward \(O(V^2)\) version that is easy to read and matches the classical exposition.

### Steps
1. Initialize `dist[v] = INF` for all vertices and mark all as unvisited; set `dist[s] = 0`.
2. Repeat `n` times:
   - Choose the unvisited vertex `v` with the smallest `dist[v]`; if it is unreachable (`INF`), stop.
   - Mark `v` visited.
   - For every edge `(v, to, w)`, if `dist[v] + w < dist[to]`, update `dist[to]` and record `p[to] = v` for path reconstruction.
3. After processing, `dist` holds shortest distances from `s`.

### Complexity
- With a simple linear scan for the next vertex: \(O(V^2 + E)\), often shown for clarity or dense graphs.

### Use Cases
- Routing with non-negative costs (road networks, network latency).
- As a subroutine in A* search (with heuristics).

### C++ Implementation (Straightforward Version)
Selects the next vertex with a linear scan instead of priority queues or sets.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int main() {
    int n, m, s; // vertices are 0..n-1
    cin >> n >> m >> s;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        // add g[v].push_back({u, w}); for an undirected graph
    }

    vector<int> d(n, INF), p(n, -1);
    vector<char> used(n, false);
    d[s] = 0;

    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j)
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (v == -1 || d[v] == INF)
            break;
        used[v] = true;

        for (auto [to, len] : g[v]) {
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }

    // d now holds shortest paths from s; p stores the tree for reconstruction
}
```

---

### Visual Walkthrough on a Small Graph
Below is a 5-vertex directed graph with non-negative weights. We run Dijkstra from source `0`.

```
      (2)         (2)
 0 --------> 1 --------> 3
 |           \          |
 |(5)         \(1)      |(1)
 v             v         v
 2 ----------> 3 ------> 4
       (3)
```

**Initialization**
- `dist = [0, INF, INF, INF, INF]`, `used = [F, F, F, F, F]`.

**Iteration details** (select the unused vertex with the smallest distance, then relax its edges):

| Step | Picked vertex | Relaxations performed | Updated `dist` |
| --- | --- | --- | --- |
| 1 | `0` (dist = 0) | `(0→1, +2)`, `(0→2, +5)` | `[0, 2, 5, INF, INF]` |
| 2 | `1` (dist = 2) | `(1→3, +2)`, `(1→2, +1)` | `[0, 2, 3, 4, INF]` (better path to `2`) |
| 3 | `2` (dist = 3) | `(2→3, +3)` | `[0, 2, 3, 4, INF]` (no improvement vs. 4) |
| 4 | `3` (dist = 4) | `(3→4, +1)` | `[0, 2, 3, 4, 5]` |
| 5 | `4` (dist = 5) | No outgoing edges | `[0, 2, 3, 4, 5]` |

All vertices become visited, and the final distances `[0, 2, 3, 4, 5]` match the shortest paths from `0`.

---

## Bellman-Ford Algorithm (Handles Negative Weights)
**Goal:** Single-source shortest paths that allow negative weights and detect negative cycles reachable from the source.

### Idea
Relax every edge \(V - 1\) times; if an edge can still be relaxed once more, a negative cycle exists.

### Steps
1. Initialize `dist[s] = 0`, others to `INF`.
2. Repeat \(V - 1\) times:
   - For each edge `(u, v, w)`, if `dist[u] + w < dist[v]`, update `dist[v]`.
3. To detect negative cycles reachable from `s`, run one more relaxation pass; any improvement means a negative cycle.

### Complexity
- Time: \(O(V \cdot E)\).
- Space: \(O(V)\).

### Use Cases
- Graphs with negative edges (currency arbitrage detection, balancing flows).
- Preprocessing step before reweighting edges in Johnson's algorithm.

### C++ Implementation (Edge List)
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Edge { int u, v, w; };

int main() {
    const long long INF = 4e18;
    int n, m, s; // vertices 0..n-1
    cin >> n >> m >> s;
    vector<Edge> edges(m);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;

    vector<long long> dist(n, INF);
    dist[s] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool changed = false;
        for (auto [u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if (!changed) break; // early exit if no updates
    }

    bool has_neg_cycle = false;
    for (auto [u, v, w] : edges) {
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            has_neg_cycle = true;
            break;
        }
    }

    // dist holds shortest paths unless a reachable negative cycle exists
}
```

---

### Visual Walkthrough (Negative Edges Allowed)
We use a 4-vertex directed graph with a negative edge but no negative cycles. Source is `0`.

```
      (4)
 0 --------> 1
 |           ^ \
 |(5)        |  \ (1)
 v           |   v
 2 --------> 3 --+ 
      (-2)
```

**Initialization**: `dist = [0, INF, INF, INF]`.

**Iteration (up to V-1 = 3 passes)** — relax every edge each pass:

| Pass | Edge relaxed | Change | dist after pass |
| --- | --- | --- | --- |
| 1 | `0→1 (+4)`, `0→2 (+5)`, `2→3 (-2)`, `3→1 (+1)` | `dist[1]` improves twice (`∞→4→3`), `dist[2]=5`, `dist[3]=3` | `[0, 3, 5, 3]` |
| 2 | same edges | No distances improve | `[0, 3, 5, 3]` |
| 3 | same edges | No distances improve | `[0, 3, 5, 3]` |

Because the third pass makes no changes, the algorithm could stop early. A fourth (cycle-detection) pass would find no improvements, confirming there is no reachable negative cycle.

---

## Floyd–Warshall Algorithm (All-Pairs Shortest Paths)
**Goal:** Compute shortest paths between all pairs of vertices; supports negative edges but not negative cycles.

### Idea
Dynamic programming over intermediate vertices: after processing vertices \(0..k\), `dist[i][j]` stores the shortest path from `i` to `j` using only those intermediates.

### Steps
1. Initialize `dist[i][j]` with edge weights (\(\infty\) if no edge), and `dist[i][i] = 0`.
2. For each intermediate vertex `k` from 0 to \(V-1\):
   - For each pair `(i, j)`, set `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`.
3. After the loops, `dist` holds all-pairs shortest-path distances. Negative cycles can be detected if any `dist[i][i] < 0`.

### Complexity
- Time: \(O(V^3)\).
- Space: \(O(V^2)\).

### Use Cases
- Dense graphs where \(V^3\) is acceptable.
- Computing transitive closure (replace sums with boolean OR/AND).
- Building routing tables or minimum distances in DP over subsets (e.g., TSP optimizations).

### C++ Implementation (Adjacency Matrix)
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long INF = 4e18;
    int n; // vertices 0..n-1
    cin >> n;
    vector<vector<long long>> dist(n, vector<long long>(n, INF));

    for (int i = 0; i < n; i++) dist[i][i] = 0;
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], 1LL * w); // handle multi-edges
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    // dist[i][j] now holds APSP results
}
```

---

### Visual Walkthrough (All-Pairs Updates)
Consider three vertices with the weighted directed edges shown; `INF` means no direct edge. The initial distance matrix is built from the edges and zeros on the diagonal.

```
0 --(3)--> 1
 \        ^
 (8)\     |(1)
     v    |
      2 --+
```

Initial `dist`:

|   | 0 | 1 | 2 |
| - | - | - | - |
| 0 | 0 | 3 | 8 |
| 1 | INF | 0 | 1 |
| 2 | INF | INF | 0 |

Run Floyd–Warshall for `k = 0, 1, 2` (intermediate vertices):

- **k = 0**: Update paths that go through vertex 0. No improvements for this graph.
- **k = 1**: Path `0 → 1 → 2` improves `dist[0][2]` from 8 to `3 + 1 = 4`. Matrix becomes:

  |   | 0 | 1 | 2 |
  | - | - | - | - |
  | 0 | 0 | 3 | 4 |
  | 1 | INF | 0 | 1 |
  | 2 | INF | INF | 0 |

- **k = 2**: No further updates; the matrix above is final. If any `dist[i][i]` became negative, that would indicate a negative cycle.

This table-based update view shows how each intermediate vertex can tighten paths between every pair.

---

## Choosing the Right Algorithm
- **Dijkstra:** Fast for non-negative weights and large sparse graphs.
- **Bellman-Ford:** Works with negative weights and detects negative cycles but is slower.
- **Floyd–Warshall:** All-pairs results for dense graphs; easy to adapt for path reconstruction or transitive closure.

