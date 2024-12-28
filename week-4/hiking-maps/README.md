# Solution

## Approach
Sliding window, CGAL point/line orientations

## Key Idea
- Compute for each map which legs of the hike are included and save them in a vector of vectors.
    - To do this, first fix map part orientations. If first point on edge, second point on edge, first point on next edge do a left turn, the orientation is correct. Otherwise, swap the two edge points.
    - Then loop over legs, checking if both ends are in the current map part triangle by using `!CGAL::right_turn()`.
        - Because each leg of the hike shares a point with the previous leg, use this in the loop to avoid unnecessary recomputation, since target's inclusion in the map part for leg j will be equal to the start's inclusion for leg j+1.
        - **Don't** use `CGAL::left_turn` alone because then collinear points (points on the edge of the map) won't be counted in the inclusions!
- Then do a sliding window to compute minimum number of maps.
    - The logic here is nice and clever and I had to look it up. For each leg, keep track of the number of maps in the current window that are covering the leg, and the number of map parts covered. Once a map part is covered for the first time the counter goes from 0 to 1, so increment `num_legs_covered`. Conversely, once a map part is no longer covered when we move `l` it will fall to 0, so decrement it.
    - If the current window doesn't cover everything, we need to buy new maps, so we want to increment our right pointer until everything is covered.
    - Once we have covered everything (`num_legs_covered ==  m-1`) we can start shrinking the window.
    

## Implementation Details
- Use inexact constructions, or you'll get a TLE!