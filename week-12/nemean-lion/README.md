# Solution
50/100

## Approach
Delaunay

## Key Idea
- $a_2$ is the number of Delaunay edges with the shortest distance.
- $a_3$ is the number of Delaunay faces with the smallest circumcenter radius.
    - A defining feature of Delaunay triangulation: for each face (triangle), the circumcircle of that face does not contain any other points of the set in its interior!

## Implementation Details
CGAL::Triangulation::dual(face_it) gives you the center of the faces circumcircle.
