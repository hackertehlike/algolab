# Solution

## Approach
Prim + Dijkstra

## Key Idea

This one is fairly straightforward, just implementation heavy.
The species private networks are their MSTs. Once we find these we can construct a supergraph that is the union of all these private networks and compute shortest paths from a to b.

## Implementation

This is where the question can go from very simple to a headache.
- **Reading the graph**:
    - It's actually a lot easier to construct separate graphs for each species and store them in a vector of graphs. The number of vertices is quite small (n $\leq$ 500) so this is no problem.
    - Save the weights of edges in a 3D table (u, v, species).
- **Computing MSTs:** Since we have a start vertex, we can use Prim to compute these.
    - Once computed, we can simply add edges to the supergraph by looping over the vertices and looking up the predecessor to every node. The edge between a vertex and its predecessor will be in the supergraph, and its weight is already saved from the reading step.
    - You don't actually have to filter out edges to only add the minimum. Dijkstra will just pick the shortest edge anyway, and our graph is small.
- **Computing the shortest path:** Just run Dijsktra on the supergraph from a and read the distance to b.