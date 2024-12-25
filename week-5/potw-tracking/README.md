# Solution

## Approach
Dijkstra

## Key Idea

Good old layering. This could have been an A&D question.
Make k+1 layers (the graphs are really small, as you can see in the input section). At layer j we've taken j river roads. Connect layer j to j+1 via river roads. All other roads are internal to the layer since they don't increment our count. No need to add river roads to the same layer, except the last layer. Once we get to the last layer we've completed our prerequisite but we still need to reach the target as quickly as possible, so we need all edges.
**And don't forget to add the reverse edge between layers** since we can use a road both ways.
Compute distance to the target node in the k-th layer using Dijkstra.

## Implementation

**Pay attention to indices AND BRACKETS.** I spent about an hour and a half looking for the bug. It was this line: `v = j+1 * n + a;`

fml