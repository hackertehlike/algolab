# Solution

## Approach
MST, DFS

## Key Idea
We're asked to find the second best MST.
For this we can compute the MST, then find the best "replacement" edge.
This replacement edge, when added to the MST, must create a cycle. If we remove the most expensive edge in the cycle that was in the original MST, we are back to having a spanning tree. So we only need to find the minimum difference for all such edges.
-For this we can compute the MST using Prim or Kruskal, then we can compute for every pair of vertices the maximum edge contained in the path between tham **in the MST** using DFS.
-We can call DFS starting once from each vertex, and then follow every path from some root using the MST adjacency list we construct at the start using the predecessor map from Prim. We keep updating and passing down most expensive edge so far, saving these in `max_edge_between[root][i]` for all vertices i. We also keep track of visited vertices and only visit them once.
-At the end we have the most expensive edge in the path between any two nodes in the MST.
-Now all we need to do is to loop over every non-MST edge, and check the difference between the edge's weight and the most expensive edge, and keep track of the best replacement.
-The cost of our second best MST will be the base cost + replacement cost.