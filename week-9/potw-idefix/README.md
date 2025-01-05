# Solution

## Approach

Delaunay, UF, Binary Search

## Key Idea

This is similar to [Clues](https://github.com/hackertehlike/algolab/tree/main/week-7/clues) but easier. The trees within range of each other create connected components of shadows. We construct a Delaunay triangulation to be able to compute these connected components using Union Find.

For subtask 1, all we need to do is to loop over the edges of the triangulation in ascending order of length until we get to the trees that are too far apart to be in the same connected component, linking the trees within range (for given radius k). We then count the bones in each connected component and find the max element.

For subtask 2, we do binary search over radii to find the smallest radius for the given radius.

## Implementation Details
-The emst sample code has most of the code you need for this.
-Initially I looped over every neighbor of every vertex. Redundant, expensive recomputations. Don't do that. The sorted edges of the triangulation will suffice.
-Precompute bone distances to nearest triangulation vertex instead of recomputing it every time. Really really expensive for the binary search in subtask 2 and unnecessary. Causes TLE for test sets 2 and 4.