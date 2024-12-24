# Approach
Linear Programming

## Key Idea

It's quite straightforward to see that this is a linear programming question, but there are a few details that are *a little bit* annoying, in my opinion. Here are the key points:
### Objective
 We are maximizing the sum of the circumferences: $\sum_{a_i} a_i * 2(w+h)$, which is equivalent to maximizing $\sum_{a_i} a_i$, or minimizing $ \sum_{a_i} -a_i$.
### Constraints
#### New Photos (First two test cases)
- For every pair of **new** photos, we have overlap constraints. The coordinates of the right/left/top/bottom edges of the magnified pictures are already given to us.
    - Initially I thought we could use both x and y constraints, and only skip the corresponding coordinates if they are equal (e.g. no x constraint if $x_1 = x_2$). My thought was that the closer coordinate would impose a tighter bound, and limit the solution accordingly while rendering the other axis constraint useless. However, that is **not** how that works.
    - Observing the case of $w = 1, h = 1$, it is easy to see that the limiting constraint is not the closer distance but the **max distance**. The simplest example is the case of colinear nails: for $x_1 = x_2$, we are only limited by the distance between $y_1$ and $y_2$, bzw. |$y_1 - y_2$|, and not |$x_1 - x_2$| (= 0 in this case).
    - The second important observation is that they aren't constrained independently of w and h. Consider the case where |$x_1 - x_2$| = 4 and |$y_1 - y_2$| = 2 for w = 4 and h = 2. Even though |$x_1 - x_2$| > |$y_1 - y_2$|, they are actually constrained by y and not x.
    - The formulation is easy to derive, luckily. The two constraints, independently (note that we will only use the more limiting one) are as follows:

    ```math
        \text{w.l.o.g. assume: } x_i < x_j. \\

        \Rightarrow x_i + a_i \frac{w}{2} \leq x_j - a_j \frac{w}{2} \\
        \Leftrightarrow  a_i + a_j \leq (x_j - x_i) \frac{2}{w} \\ 
        \text{which generalizes to: } \\
        a_i + a_j \leq |x_j - x_i| \frac{2}{w} \\

        \text{Similarly, } a_i + a_j \leq |y_j - y_i| \frac{2}{h} .
    ```


    - As we have noted, it is only the more limiting of the RHS bounds that we use as a constraint. So we take
    the **max** of $|y_2 - y_1| \frac{2}{h}$ and $|x_2 - x_1| \frac{2}{w}$, and use that as our b. LHS remains the same for both constraints.

- One small detail is that $\forall{a_i}, \quad a_i \geq 1$, so don't forget to lower-bound.

#### Old Photos
It is easy to see that we apply a similar logic here, except we can't magnify the old photos. So actually we only have one variable for each constraint:
```math
    a_i \leq |y_i - y_{old}| \frac{2}{h} \\
    a_i \leq |x_i - x_{old}| \frac{2}{w}
```
and we again use the **max** constraint among these.

Again, only the tightest bound - the closest old photograph - matters. So we can loop over each old photo and our RHS becomes the tightest (**min**) bound for $a_i$. Note that we can use `set_u` since we only have one variable on the left-hand side.

