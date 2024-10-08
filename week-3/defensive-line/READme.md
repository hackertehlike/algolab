## Defensive Line
# Category: DP

# Problem Statement:
Find exactly m disjoint sub-arrays of a given array such that the sum of the elements in each sub-array is equal to a given number k, and the total sum of the elements in all the sub-arrays is maximum.

# Approach:
- Precompute the auxiliary vector:
    - If there is no interval ending at i with sum k: -1.
    - If there is an interval ending at i with sum k: the length of the interval.
- DP table m+1 x n+1:
    - Row and column 0 are 0 (0 items, 0 defenders)
    - For the first row: dp[1][i] = max(dp[1][i-1], aux[i])
    - For the rest of the cells dp[i][j]:
        - If top left cell is 0 -> 0 (we can't move onto the j-th defender yet because we haven't used the j-1-th defender)
        - If the auxiliary vector is -1 -> dp[i][j] = dp[i][j-1] (we can't improve the maximum at this j because there is no interval ending at j)
        - If dp[i-1][j-aux[j]] = 0 -> dp[i][j] = 0 since we can't take this interval (we haven't used the j-1-th defender yet)
        - Otherwise: We take the maximum between:
            - dp[i][j-1] (there are better intervals we have found alreadyso we don't take the one ending at j)
            - dp[i-1][j-aux[j]] + aux[j] (we choose best intervals ending before j starts for all previous defenders and add the interval ending at j)
