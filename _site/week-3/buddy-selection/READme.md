## Defensive Line

### Category:
Graph, matching

### Problem:
We have n students, and a subset of interests for each. We want to pair them up in such a way that everyone gets a partner, and the number of shared interests between any two partners is greater than `k`.

### Approach:
We can model this as a graph problem. Each student is a node, and there is an edge between two students if they share more than `k` interests. We can then find the maximum matching in this graph, which will give us the maximum number of pairs we can form.
- Model every student as a set and take set intersection to check if an edge should be added
- Loop through every combination only once to avoid unnecessary checks (0 < i < n, i < j < n)
