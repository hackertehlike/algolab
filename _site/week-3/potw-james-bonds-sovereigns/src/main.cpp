#include <iostream>
#include <vector>
#include <limits>

int n, m, k;
std::vector<int> coins;
std::vector<std::vector<int>> dp;

int maxWinnings(int i, int j) {
  if (i > j) return 0;
  if (dp[i][j] != -1) return dp[i][j];
  
  int curr_player = (n - j + i - 1) % m;
  
  if (curr_player == k) {
    dp[i][j] = std::max(coins[i] + (i + 1 <= j ? maxWinnings(i + 1, j) : 0),
                        coins[j] + (i <= j - 1 ? maxWinnings(i, j - 1) : 0));
  } else {
    int opt1 = i + 1 <= j ? maxWinnings(i + 1, j) : 0;
    int opt2 = i <= j - 1 ? maxWinnings(i, j - 1) : 0;
    dp[i][j] = std::min(opt1, opt2);
  }

  return dp[i][j];
}

void testcase() {
  std::cin >> n >> m >> k;
  coins.resize(n);
  dp.assign(n, std::vector<int>(n, -1));
  
  for (int i = 0; i < n; i++)
    std::cin >> coins[i];
  
  if ((n - 1) % m == k)
    for (int i = 0; i < n; i++)
        dp[i][i] = coins[i];
  
  std::cout << maxWinnings(0, n - 1) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i)
    testcase();
}
