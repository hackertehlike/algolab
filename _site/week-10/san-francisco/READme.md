### Approach
DP

### Key idea:

Recursion for the first two groups of test cases
- The most straightforward idea would be if we started from the Angvariationu-toke, then recursed down the graph, keeping track of moves taken so far and maximum scores.
Unfortunately this is both too slow and doesn't generalize well to the last test case.

So instead we can take a DP approach. Just like the recursion, we can save the optimal score for a node i and depth j. However, the values in our DP table correspond to the best score **starting from** node i, **after taking** j moves. We are working **backward**, in a sense, instead of forward.

The rest is very straightforward to figure out:
- The order of computation is in **ascending order of depth**. The order of the nodes for a specific depth only matters because we want to have computed the score for the Angvariationu-toke **before** any Weayaya - we'll come to why that is in a second.
- dp[i][j] = Σ_((target, score) ∈ out_edges[i]) max(dp[target][j-1] + score):
    - In words, our optimal scoring path for node i at depth j will be the highest scoring path that starts at this node, takes the edge to one child, and takes the child's optimal path, which we have already computed since it has depth j-1.

The trickiest part in my opinion is figuring out what to do with the Waeyayas. Since we can go straight from a Waeyaya to the Angvariationu-toke without expending a move. This can be thought of as just erasing the Waeyaya and rerouting the edge leading to it to the Angvariationu-toke instead. This makes it a bit more clear that we just take the Angvariationu-toke's value at this depth, which we have already computed, since they are "the same node" now.

### Result
There are two ways to achieve this:
 - Read from the DP table once everything is computed by searching for the smallest k in the row of the Angvariationu-toke (node 0).
 - Or, my favored approach, by terminating early as soon as we have found a path from 0 that is equal to or greater than the required score x. This works because we are working in order of ascending depth.

### Implementation
- Boost is actually not necessary for this since we just need to save all out-going edges for each node and their scores. Save yourself some trouble and just use a vector of vectors.
