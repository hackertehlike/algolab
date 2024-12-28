#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> coins;
std::vector<std::vector<int>> min_guaranteed_win_vec;

int min_guaranteed_win(int l, int r) {
    // Check if the result is already computed
    if (min_guaranteed_win_vec[l][r] == -1) {
        if (r < l) return 0; // Sanity check, should not happen
        if (l == r) return coins[l];
        if (r - l == 1) return std::max(coins[l], coins[r]);
        
        // Memoize the result
        min_guaranteed_win_vec[l][r] = std::max(
            coins[l] + std::min(min_guaranteed_win(l + 2, r), min_guaranteed_win(l + 1, r - 1)),
            coins[r] + std::min(min_guaranteed_win(l, r - 2), min_guaranteed_win(l + 1, r - 1))
        );
    }
    
    return min_guaranteed_win_vec[l][r];
}

int main() {
    int t; std::cin >> t;

    while (t--) {
        int n; std::cin >> n;
        coins.resize(n);  // Resizing global coins vector to fit the number of inputs

        // Resize and initialize the memoization table with -1
        min_guaranteed_win_vec.clear();
        min_guaranteed_win_vec.resize(n, std::vector<int>(n, -1));

        // Input the coin values
        for (int i = 0; i < n; ++i) {
            std::cin >> coins[i];
        }


        // Output the result
        std::cout << min_guaranteed_win(0, n-1) << std::endl;
    }

    return 0;
}
