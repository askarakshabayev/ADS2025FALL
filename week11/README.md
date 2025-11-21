# Week 11 Examples: DFS and Its Applications

## Files Description

### Basic DFS
- **1_dfs_basic.cpp** - Basic DFS implementation (recursive and iterative)
  - Input: n (vertices), m (edges), followed by m edges
  - Example: `./1_dfs_basic < input1.txt`

### Component Counting
- **2_count_components.cpp** - Count connected components
  - Input: n (vertices), m (edges), followed by m edges
  - Example: `./2_count_components < input2.txt`
  - Expected output for input2.txt: 3 (three components)

### Bipartite Check
- **3_bipartite.cpp** - Check if graph is bipartite
  - Input: n (vertices), m (edges), followed by m edges
  - Example: `./3_bipartite < input_bipartite.txt`
  - Output: YES or NO

### Topological Sort
- **4_topological_sort.cpp** - Topological sorting for DAG
  - Input: n (vertices), m (directed edges), followed by m edges
  - Example: `./4_topological_sort < input_dag.txt`
  - Output: One valid topological order

### Cycle Detection
- **5_cycle_detection.cpp** - Detect cycle in undirected graph
  - Input: n (vertices), m (edges), followed by m edges
  - Output: "Cycle found" or "No cycle"

- **7_cycle_directed.cpp** - Detect cycle in directed graph
  - Input: n (vertices), m (directed edges), followed by m edges
  - Output: "Cycle found" or "No cycle (DAG)"

### Path Finding
- **6_find_path.cpp** - Find path between two vertices
  - Input: n (vertices), m (edges), followed by m edges, then start and end vertices
  - Output: Path from start to end or "No path"

### Island Counting
- **8_islands_count.cpp** - Count islands in 2D grid
  - Input: n (rows), m (columns), followed by n×m grid of 0s and 1s
  - Example: `./8_islands_count < input_islands.txt`
  - Expected output for input_islands.txt: 5 islands

## How to Compile and Run

```bash
# Compile
g++ -o program_name filename.cpp

# Run with input file
./program_name < input_file.txt

# Or run interactively
./program_name
```

## Example Usage

```bash
# Count components
g++ -o count 2_count_components.cpp
./count < input2.txt

# Check if bipartite
g++ -o bipartite 3_bipartite.cpp
./bipartite < input_bipartite.txt

# Topological sort
g++ -o topo 4_topological_sort.cpp
./topo < input_dag.txt

# Count islands
g++ -o islands 8_islands_count.cpp
./islands < input_islands.txt
```

## Key Concepts

1. **DFS Traversal**: Visit vertices depth-first
2. **Connected Components**: Groups of connected vertices
3. **Bipartite**: Can be colored with 2 colors
4. **Topological Sort**: Linear ordering of DAG vertices
5. **Cycle Detection**: Find if graph contains cycles
6. **Path Finding**: Find path between two vertices

## Time Complexity

All DFS-based algorithms: **O(V + E)** with adjacency list
