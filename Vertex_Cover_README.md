# Vertex Cover Problem

This project provides an implementation of a greedy approximation algorithm for solving the **Vertex Cover Problem**. The Vertex Cover Problem is an NP-hard problem in graph theory, where the objective is to find a subset of vertices such that every edge in the graph is incident to at least one vertex in the subset.

## Features

- **Efficient Approximation**: Uses a greedy algorithm for quick, approximate solutions.
- **Graph Representation**: Built using the `networkx` library for easy graph handling.
- **Customizable**: Supports any undirected graph as input.

## Requirements

- Python 3.7+
- `networkx` library

To install the required library, run:
```bash
pip install networkx
```

## Usage

1. Clone the repository or copy the script to your local environment.
2. Define your graph using `networkx` or load it from an external source.
3. Use the `greedy_vertex_cover` function to compute the vertex cover.

## Example

```python
import networkx as nx
from vertex_cover import greedy_vertex_cover

# Create a graph
G = nx.Graph()
G.add_edges_from([
    (1, 2), (1, 3), (2, 4), (3, 4), (3, 5), (4, 5)
])

# Find the vertex cover
vertex_cover = greedy_vertex_cover(G)

print("Graph edges:", list(G.edges()))
print("Vertex cover:", vertex_cover)
```

### Output

```plaintext
Graph edges: [(1, 2), (1, 3), (2, 4), (3, 4), (3, 5), (4, 5)]
Vertex cover: {1, 3, 4}
```

## How It Works

1. **Input Graph**: An undirected graph is passed to the algorithm.
2. **Greedy Selection**: The algorithm iteratively selects edges and adds their endpoints to the vertex cover.
3. **Edge Removal**: All edges covered by the selected vertices are removed from the graph.
4. **Output**: The resulting set of vertices forms the vertex cover.

## Limitations

- This is a greedy approximation algorithm, so the solution may not be optimal for all graphs.
- Works only on undirected graphs.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

---

Feel free to contribute by submitting issues or pull requests to improve the implementation.
