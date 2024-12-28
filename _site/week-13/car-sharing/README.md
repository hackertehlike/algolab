# Solution

## Approach
Min-Cost-Max-Flow

## Key Idea
This is very similar to [Asterix and the Tour of Gaul](https://github.com/hackertehlike/algolab/tree/main/week-10/asterix-and-the-tour-of-gaul). We have overlapping intervals that bring us some kind of profit that we must pick a non-overlapping, optimal subset of. The difficulty of this one stems from the main idea that was absent from Tour of Gaul, but one that takes me back to my A&D days, which is **temporal layers** for the graph.

### The Flow Graph
As is the case for most flow problems, once you construct the flow graph you're already there. For this one specifically, here is the construction:
- **Nodes**: We have one node for each (station, timestep) pair.
  - **Timesteps** consist of the timesteps that are important, i.e. **the set of all departure and arrival times of all bookings**, plus timestep 0.
- **Source edges**: These are the cars available at each station at timestep 0. For all s $\in$ {Stations} we have an edge $v_{source} \rightarrow$ (s, 0) with capacity $l_i$ and cost = 0.
- **Sink edges**: These are the cars at the last timestep `last_t`. For all s $\in$ {Stations} we have an edge (s, 0) $\rightarrow v_{sink}$  with capacity `num_cars` since there is unlimited parking space, and cost = 0.
- **Idle edges**: These are the cars waiting at the station. We have (s, t) $\rightarrow$ (s, t+1) where t and t+1 correspond to timesteps in our sorted set of departure and arrival times (plus 0).
    - To make weights non-negative, we incur costs of "waiting" per minute. Because the maximum profit from a booking is 100, we can set this to 100. So **cost = (t+1 - t) * 100** The capacity is the number of total cars, again because we have unlimited parking space. 
- **Booking edges**: These are the edges that represent the bookings. For every booking $b = (s, t, d, a, p)$ we have an edge (s, d) $\rightarrow$ (t, a) with capacity 1 and **cost = (a - d) * 100 - p**.

### Result
The max profit = 100 * `num_cars` * `last_t` - `flow`. The first quantity is the cost if we don't accept any bookings, so by subtracting the flow which is the minimal cost from our flow graph, we get the total booking profits.

### Implementation
I used a map to save station timestep pairs and their corresponding vertex descriptors. The last test case causes a TLE at the moment (80/100), and I'm pretty sure it's an issue with the implementation and not the approach.
A vector of vectors might be faster.
Also, there might be a more elegant solution to handle timesteps. Currently I'm using a set to get unique timesteps while reading booking inputs, and saving them to a vector, which is then sorted.
