# Solution

## Approach
Delaunay, Priority Queue

## Key Idea
Any point/disk in a Delaunay triangulation (**not** a Delaunay vertex, just a point on some Delaunay face) will have to cross through one of the edges to exit unless it's already in an infinite face.
So we can compute for any face the largest disk that can escape from that face using *some* sequence of faces. This will be the narrowest width of the best path, where best path is the one with the widest bottleneck edge (we can call this the **escape potential**). We can think of edges as doorways our large disk/ball has to cross through, which need to be wide enough to accomodate the disk. 
We compute this as follows:
- We keep a priority queue which we will process until it's empty. This will serve to propagate better paths from faces to adjacent faces and adjacent... grand-faces? and so on.
- We begin by finding the neighbors of infinite faces and pushing them onto the queue together with their shared edge's (squared) length as the escape potential, since this will be the last exit if we're taking the exit path to this infinite face.
- Then we process **(face, escape potential)** pairs in order of descending escape potentials.
    - For every face updated, we also need to inform its neighbors with this best path, since they could also use this path if it is better.
    - We only update faces that don't already have a path propagated to them. Since we're processing them in order of priority, if there was a better path for a face, that would have been processed first anyway because of the priority queue's ordering.
    - When pushing a neighbor to inform them of the new path on the priority queue, we must do so taking into account the shared edge with the neighbor. Even if we have a wide path available to us from the current face, the neighbor will have to exit through our shared edge, which might bottleneck the path.

## Implementation Details
I was confused about why this worked with a multiset and not with a priority queue with the same exact comparator... That's because multisets sort elements in ascending order and priority queues in descending order.
So the comparator that worked for the multiset was actually constructing a min heap.