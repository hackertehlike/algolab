# Solution

## Approach
Delaunay

## Key Idea
This is fairly straightforward. A bacterium will die either by touching its nearest neighbor, or the side of the petri dish. So we can triangulate the vertices, then check the nearest neighbor, and take the min over their **squared distance** and $4r^2$ where r is the distance to the closest side of the dish (we do this conversion because the side of the petri dish doesn't grow, but we must be able to compare these distances to the distance between two bacteria, which is the square of the sum of *two times* their radius at the timestep when they touch).
We then sort the distances, and compute the time of death for the first, last, and middle elements.

## Implementation Details
Be careful with the math! Specifically don't forget to convert the distance to sides as $4r^2$, and also, while computing time of death. $0.5+t^2 = radius$ means that for a distance of $d$, $d=2*(0.5+t^2)$. Therefore $t=\sqrt{d-1}$ unless distance is less than 1, in which case $t=0$.