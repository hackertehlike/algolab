# Solution

## Approach
Recursion

## Key Idea
This one was a *headache* to figure out even though I looked at the solution and it boiled down to ten lines of code.
Here is the problem statement abstracted:
- We have n nodes.
- We have n - 1 directed edges between these nodes, and the race starts from 0.
- Additionally, all cities are reachable from 0.
From this so far we can deduce that the graph is a tree that has 0 as its root.
- Every node has a cost associated with it.
- We are looking for a **vertex cover**, but note that this vertex cover is **not** minimum! Instead, we are looking for a vertex cover that has the **minimum total cost**, where the total cost is the sum of costs associated with the vertices in the vertex cover.

Since we know the graph is a tree, recursion seems obvious. However, due to the "sandwiching" nature of the cover, it is quite tricky.
It is easier to think bottom-up than top-down in this problem.

The decision logic at each recursive calls is as follows:
- We are going to return 3 values for the current vertex at the end of the call. These are:
    - Minimum cost to cover this node's entire subtree (including the node itself), given that we have chosen, definitely, to include (or "fix", according to the story of the problem) the current node.
    - Minimum cost to cover this node's entire subtree (including the node itself), if we **don't** fix the node but cover it using a child instead.
    - Minimum cost to cover all descendants (children, grandchildren, etc.) of this node, **excluding** this node. This *disregards* the coverage problem of the current node. Why we need this one as well will become clearer in a moment.

So now we only need to calculate these quantities!

For leaf nodes, we have no choice but to fix the node.
    - **Note that the decision to take a node or cover it *by its parent* is always made higher up at the parent's level!** At every recursive call, we are only considering the possibility of covering the node either covering itself by being fixed, or being covered by a child. The third value returned (min cost to cover all descendants excluding the current node) will be handy for when that decision has to be made, again, at the parent's level!
Thus, we return {cost of leaf node, cost of leaf node, 0} since we have to cover this node. (Note that the second value does not correspond to the description above, for this specific case. This is because we don't have any children here that *can* cover for us, which is what the second value normally represents.)

For all other nodes, we have to loop over all children and calculate the three values.
- Let's start with the third one. This is the minimum cost to cover all of its children, without considering whether or not the current node is being covered. For this, we simply accumulate the minimums of the first two values of the children, i.e. the cheapest way to cover the whole subtrees of all children. Here, taking the min over the first two values for each child means that we are picking the cheaper way out of fixing the child and covering it with one of the child's children.
- The second value builds on top of the third. Assume we already know that one. So we know the cost of covering all of the children, but now we need to also cover the current node using a child.
    - In the worst case scenario, the cheapest way that we have already computed (which is the third value) might be a case where all children of the current node are covered by their children and none of them are fixed. In this case, we will have to fix at least one child to cover the current node, which will incur an additional cost. The optimal child to fix will be the one that incurs the smallest additional cost to repair.
    - In all other scenarios, the cheapest way that we have already computed (which is the third value) includes at least one child that is being repaired, which is enough to cover the current node.
    - So we can just keep track, while looping over the children, the smallest difference between the cheapest way to cover the child's subtree(min over the first two values for the child), and the minimum cost of covering the child's subtree with the child fixed (the first value for the child).
    - The second value is then the cost of covering all children, which is the third value we computed in the first bullet point, plus the additional cost of repairing the best child (which will be 0 if any child was already cheaper to repair).
- The first value is now easy to compute and understand as well. Since we know we're fixing the current node, we have to add its cost to this value. Now this triggers the consideration that I made above. Namely, we now cover all of our children, and this allows us to "relieve" the pressure from our children if there are any that were paying a high cost to be able to cover themselves. We still have to cover our grandchildren, though, but we already know, for every child, the minimum cost to cover all of *their* descendants without considering the coverage of said child. This is the third value returned by the child's recursive step.
    - So now we can accumulate, child by child, the cheaper way to cover all descendant. We simply add to our first value the min over the cost of the child (either its first or its second value, where the child is being covered either by one of *its* children or by itself) and the cost of covering all of its descendants (which, again, is its third value).

Once we calculate these values for the root node, we can decide if fixing it or covering it with a child is cheaper, by simply taking the minimum over its first two values.
This brings us to the end.