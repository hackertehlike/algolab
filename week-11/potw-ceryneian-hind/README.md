# Solution

## Approach
MinCut-MaxFlow

## Key Idea
This is somewhat similar to [Asterix in Switzerland](https://github.com/hackertehlike/algolab/tree/main/week-11/asterix-in-switzerland). Obviously, finding a subset of vertices immediately reminds us of min-cut. The crucial thing here is what a unit of flow represents: **a convenience point that we don't get**, because it flows out of our subset. This, then, we can think of as follows:
- We lose convenience points precisely when we have a negative convenience score in our semi-dead-end. So we can model our source and sink as "supply" and "demand" once again.
- Similar to Asterix in Switzerland, we must have a non-negative surplus trapped in the semi-dead-end.  Thus, we can again sum positive convenience points and see if our flow is less to see if some are trapped.
- To enforce the semi-dead-end constraint, which is crucial to the problem, we can add **infinity** valued edges, since we don't want any outgoing edges from our semi-dead-end. These edges drain any benefit we get from that or any node with a positive convenience score that has an edge to this node, so we are never worse-off for excluding this.

## Implementation Details
- Don't forget to make flow a long. The convenience scores can add up to $>2^32$.
- Also don't use $2^{10}$ as infinity value... This is wrong.