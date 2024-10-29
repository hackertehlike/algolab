#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    
    // std::cout << "Testcase " << t << std::endl;
    
    int n, m, k; std::cin >> n >> m >> k;
    
    std::vector<int> defense_values;
    
    for(int i = 0; i < n; i++) {
      int vi; std::cin >> vi;
      defense_values.push_back(vi);
    }
    
    std::vector<int> precompute(n , -1);
    int l = 0;
    int r = 0;
    int tot_sum = defense_values[0];

    while(r < n) {

      if(tot_sum > k) {
        
        tot_sum -= defense_values[l++];
        if(l > r) {
          tot_sum = defense_values[++r];
        }
      }
      
      else if(tot_sum < k) {
        tot_sum += defense_values[++r];
      }
      
      else {
        precompute[r] = r-l+1;
        tot_sum = tot_sum + defense_values[++r] - defense_values[l++];
      }
    }
    
    // for(auto &elem : precompute) std::cout << elem << " ";
    // std::cout << std::endl;
     
    std::vector<std::vector<int>> dp;
    for(int i = 0; i < m+1; i++) {
      std::vector<int> row_i(n+1);
      dp.push_back(row_i);
    }
    
    
    
    for(int i = 0; i < m+1; i++) dp[i][0] = 0;
    
    for(int i = 0; i < n+1; i++) {
      dp[0][i] = 0;
    }
    
    int curr_max = 0;
    for(int i = 1; i < n+1; i++) {
      curr_max = std::max(curr_max, precompute[i-1]);
      dp[1][i] = curr_max;
    }
    
    
    for(int i = 2; i < m+1; i++) {
       for(int j = 1; j < n+1; j++) {
         if(dp[i-1][j-1] == 0) continue;
         if(precompute[j-1] == -1) {
           dp[i][j] = dp[i][j-1];
           continue;
         }
         if(dp[i-1][j - precompute[j-1]] == 0) continue;
         int val = dp[i-1][j - precompute[j-1]] + precompute[j-1];
         dp[i][j] = std::max(val, dp[i][j-1]);
       }
    }
    
    if(dp[m][n] == 0) std::cout << "fail" << std::endl;
    else std::cout << dp[m][n] << std::endl;
    
  
    // for(int i = 0; i < m+1; i++) {
    //     for(int j = 0; j < n+1; j++) {
    //       std::cout << dp[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
  }
}