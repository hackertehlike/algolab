#include <vector>
#include <iostream>
#include <limits>

void testcase() {
    int n, m, k; long long x;
    std::cin >> n >> m >> x >> k;
    
    std::vector<std::vector<std::pair<int, long long>>> out_edges(n, std::vector<std::pair<int, long long>>());

    for (int i = 0; i < m; i++) {
        int u, v; long long p; 
        std::cin >> u >> v >> p;
        out_edges[u].push_back(std::make_pair(v, p));
    }
    
    // Note: This can be done with a k x n table, where k isn't moves taken so far
    // but alos includes the move we're doing at that step.
    // e.g. at depth 0, we are already counting the out-edges since we'll be making
    // that move now.
    // But I find it more intuitive that k should be moves taken so far, i.e.
    // dp[i][j] is the max score we can get if we start from i and take j moves.
    // Hence k+1.
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(k + 1, 0));
    
    for(int i = 0; i < n; i++) dp[i][0] = 0;
    
    for(int j = 1; j < k + 1; j++) {
      for(int i = 0; i < n; i++) {
       
       long long best_score = 0;
        
        // If it's a hole, we can just take the score of 0
        if(out_edges[i].size() == 0) {
          dp[i][j] = dp[0][j];
          continue;
        }
        
        for(const auto &edge : out_edges[i]) {
          best_score = std::max(best_score, edge.second + dp[edge.first][j-1]);
        }
        
        if(i == 0 && best_score >= x) {
          std::cout << j << std::endl;
          return;
        }
        
        dp[i][j] = best_score;
      }
    }
    
   std::cout << "Impossible" << std::endl;
}

int main() {
    int t; std::cin >> t;

    while(t--) {
        testcase();
    }

    return 0;
}
