# Solution

## Approach
MinCost-MaxFlow

## Key Idea
Man this was hard. It's fairly clear it should be min-cost-max-flow since we're dealing with matches again, and that we have a bipartite graph. We can also realize that by nature of the problem the flow graph will look "symmetric" in construction since we can always exchange e and w and should be able to get the same schedule. (Note: This does not mean they look exactly symmetric, since we have different $e$ and $w$, but that the graph construction logic should be symmetric!)
- We have to fulfill two constraints:
    - Every team must play at least l matches.
    - There must be in total exactly p matches played.
- The l matches constraint is the easier part of the problem to model. As usual, we can connect the source to the east teams with l capacity, and the west teams to sink with l capacity. Every potential match is an edge between the corresponding nodes with capacity one and cost = risk.
- You might realize at this point that this is not going to work because we have now imposed a restriction on every team in that they can play at most l games, which is not what we want! It also means a proper schedule is nearly impossible.
- The extra matches must come from somewhere. They can come from difficult or non-difficult matches, but we'll get to difficult matches later. For now, the important point is that **we need more flow coming into the first layer** of teams, i.e. east teams. Symmetrically, we need more flow going out of the west teams to somewhere. But all before the first layer bzw. after the second is the sink and source nodes..? ...so we need two sources and two sink nodes, which we can separate as `l source` and `rest source`. We similarly have an `l sink` and a `rest sink`. We also naturally add a supersource and a supersink.
- We want all edges with capacity l going out from `l source` to the east teams to be at max capacity. There are e of them. This means we want exactly $e*l$ flow from the supersource to `l source`.
- To enforce this, we need to make sure there can be no flow from the supersource to the `rest source` to compensate! So we add an edge between supersource and `rest source` with capacity $p-e*l$. This means at full capacity flow, we will have p matches in total, and $l$ flow must come from the `l source` into each east team, so we have modelled that constraint. Symmetrically, we have an edge from `l sink` to supersink with capacity $w*l$ and one from `rest sink` to supersink with capacity $p-w*l$.
- We also need to allow east teams to take in flow from the `rest source`. This is why we added it in the first place! These edges have infinite capacity because there is no restriction on this. Similarly we also have edges from the west teams to the `rest sink`.
- The only thing remaining is handling the difficult matches. Note again that they do not count toward the l assessment matches played. This means they have to go through the rest source and sink.
    - We model these matches by having a second copy of the two team layers that are only connected through the rest source and sink. As above, we have an edge with capacity 1 between every potential match pair in this "parallel subgraph."
- If $e*l < p$ or $w*l < p$ we cannot ever have a valid schedule because the total number of matches required to play for assessment is greater than the number of total matches p.
- If we have enough matches to fulfill the assessment constraint, we need to check if there are indeed p matches available, by checking flow. If `flow == p` we can simply return min cost.