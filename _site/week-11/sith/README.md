# Approach:
Union Find. Just UF is enough for 75/100 points.
For the remaining 25 points, we also need Delaunay.

Here I will outline two solutions for this problem. One is too slow for the last test case (O(n^2)) but super simple to implement. The other builds on top of the first, and uses a Delaunay triangulation to speed it up, though the key idea is the same.

## Solution 1 (75/100)

### Key Idea:

There are a couple observations to make.
- Our starting planet imposes an upper limit to how many planets we will be able to recruit at most. For example, if we start from the second planet to be conquered by the empire, that means we only have one time step to potentially reach a free planet and recruit them. To maximize the number of planets on our side, we're better off choosing a starting planet that is one of the last to be conquered.
- Once a planet has been recruited into the rebel alliance, all planets within range are now also reachable. This makes union find very useful to track our "connected components."
- At some point, we will inevitably hit a "boundary." We want to maximize the number of planets on our side, but we can only recruit at most one planet in one day, and the empire recruits a planet a day as well - the key is to balance this so that we have the maximum number of planets in the rebel alliance.

### Computation

We start from the last planet on the empire's schedule, and work our way back, covering the n-t-1th planet at timestep t (starting from t = 0).
- For each new planet, we check its distance to all planets that will be conquered after it to see if we could add it to the connected component (i.e. if it is within reach of any, then they will be in the same component.) For every planet scheduled after our current planet that is within reach, we keep unifying their connected components.
    - Note: It could be that two components that have so far been disjoint will be unified by our new component, and this is automatically done by the unify operation since we will find both disjoint sets while iterating, and take their union with our current node's set, which will make sure they are in the same set by the end.
- We also update the sizes of the components as we go along.
- Once we are done connecting our new planet to any planets that come after it in the schedule, we compute our maximum number of planets for this timestep (day) t. There are three things to consider.
    - Either this planet is now in the biggest network that is achievable in up to t days, or it is not.
    - The maximum number recruitable, independently of the size of any connected components at this time step, is capped by the number of planets that are still free, which is n-t-1.
    - Thus, we take the maximum over:
        - best result so far, which is equivalent to the case where we have already found a bigger alliance in fewer days than the one we will have if we choose the set of planets with our current node included
        - and the minimum over:
            - the size of component that our current node belongs to (which is equivalent to the case where this set of planets gives us the most planets in the alliance recruitable in t days) 
            - the number of free planets left at timestep t (=n-t-1)

## Solution 2

The only thing to add here is that instead of looping over every planet that comes after our current node, we insert the current node into our Delaunay triangulation and only check against neighbors.

We can also terminate early once our maximum exceeds the number of free planets, since we've hit the "boundary."
    - Note: This can also be done for the first solution but does not make a difference in performance.