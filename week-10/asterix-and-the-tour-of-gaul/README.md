# Solution

## Approach

Min Cost Max Flow

## Key Idea
Similar to [Car Sharing](https://github.com/hackertehlike/algolab/tree/main/week-13/car-sharing), but with extra limitations, namely the capacity constraints. Also for the last test case (20/100) we need to filter out edges that are definitely not going to be used or else we TLE.

### Capacity Constraints
- At any stop i, we can put at most `capacities[i]` items in our bag. Which also means we can unload from `capacities[i]` items in our bag at the next stop! So we model this limitation by adding edges **source $\rightarrow$ i with capacity $c_i$** and edges **i+1 $\rightarrow$ sink with capacity $c_i$**.
- For each day i, we also add an edge **i $\rightarrow$ i+1 with capacity $c_i$**.

### Costs
- As usual, we normalize to be able to use successive shortest paths, by introducing a max cost per day ($2^7$ as given in the problem).
- The costs are thus 0 for the source and sink edges.
- For the item edges, we have `max_cost * (b-a) - d`.
- Don't forget to normalize at the end: `total_satisfaction = max_cost * flow - total_cost`

### Filtering of Unnecessary Edges
- For a node pair (i, j), we cannot possibly transport more than $c_i$ items, so we can sort the edges in order of descending satisfaction and only add the top $c_i$ edges.
- Initially I thought we only needed $c_i$ outgoing edges from node $i$ in total, but it is not guaranteed that we will choose the top satisfaciton items, since some might for example be very long arrows that are worse in the long run. So we need more than just $c_i$ edges. But we know that for a given (i, j), we cannot possibly carry more than $c_i$, so we don't need the rest.

## Implementation Details
- For some reason,
```
for(const int d : item_edges[i][j]) {
        adder.add_edge(i, j, 1, max_cost * (j-i) - d);
        if(++num_added >= capacities[i]) break;
      }
```
 TLEs while
 ```
 for(int k = 0; k < (int)item_edges[i][j].size() && k < capacities[i]; k++) {
          adder.add_edge(i, j, 1, max_cost*(j-i) - item_edges[i][j][k]); num_added++;
      }
```
does not. I have confirmed that they are adding the exact same number of edges and are otherwise correct. No clue what's happening here.

## Extra
Here are some graphs explaining that flow does indeed take into account a bottleneck along the path.
![1](https://github.com/hackertehlike/algolab/blob/main/week-10/asterix-and-the-tour-of-gaul/flowg1.jpg)
At the top you see the flow graph if we don't take any items.
Middle shows flow if we take the shorter edge.
Bottom shows flow if we take the longer edge.
As you can see, the flow is the same in all cases, so we'll pick the one with the best cost.
![2]([https://github.com/hackertehlike/week-10/asterix-and-the-tour-of-gaul/flowg2.jpg](https://github.com/hackertehlike/algolab/blob/main/week-10/asterix-and-the-tour-of-gaul/flowg1.jpg))
Here you see what happens to flow if we take both edges. Flow is no longer at maximum capacity.
