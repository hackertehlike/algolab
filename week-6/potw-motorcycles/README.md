# Solution

## Approach
CGAL

## Key Idea
The key idea is that because they are moving with the same speed, and stop when they see another biker's tracks, the **flattest slope will always win**. And, **for two bikes to not cut each other off, the upper one has to have a higher slope**. So in the end we will be left with a "fan" shape where none of the tracks are intersecting because they are in order of descending slope (numerically descending - not in terms of absolute value!).
- We sort all bikers by **descending** $y$-coordinate (start from the highest biker). A biker starting higher can potentially cut off any bikers below if it has a “better” (flatter) slope. By the time we process a lower biker, we already know which upper bikers remain active to possibly cut it off.
-We keep a list (or stack) of surviving bikers who are still riding and haven’t been cut off. This is our active frontier of surviving tracks.
   - Each biker’s path is represented by its **index,** **Ray** and **slope**, where
     $\text{slope} = \frac{y_1 - y_0}{x_1},$
     given the biker starts at $(0, y_0)$ and heads toward $(x_1, y_1)$ with $x_1 > 0$.
-When a new biker arrives (in descending $y$-order):
    - If the new biker’s slope is numerically $\le$ (or in some solutions, “$\le$” in absolute value) compared to the “best” slope in the stack, we just accept it immediately. This means it is **no steeper** than whatever’s currently dominating. This is the case where our new track complies with "the fan" shape.
    - Otherwise, we have to kill some tracks since our current track must intersect with at least one downward sloping track. For any track from above that has a steeper absolute slope that it intersects with, our current track will kill it. So we have to kill them until we either erase all of them, or we get to the first surviving track. Once we hit that, we know everything above fits the "fan" already, so we can stop erasing tracks. 
    The first surviving track will be either
        - the first track that is no longer intersecting with the current track because it has a higher slope (in other words, fits the "fan" together with our current track)
            - in which case, we can add our current track to the survivors, and it becomes the lowest sloping track
         or
        - the first track that is flatter than our current track
            - in which case it will kill our current track, and we don't change anything with our survivors or our lowest sloping track and move on to the next track.
- We then sort these survivors by their **original indices** (as required by the problem) and output them in ascending index order.

-**Complexity**  
   - The initial **sort** is $O(n \log n)$.
   - Each biker can only be **pushed** once and **popped** once from the stack (amortized $O(n)$ total for stack operations).
   - Intersection checks happen only during pops, so total time remains $O(n \log n)$.

## Implementation Details
- Use CGAL::abs()
- Don't forget to sort y in *descending* order, not ascending!