#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    while(t--) {
      
      // Read input
      int n; std::cin >> n;
      int k; std::cin >> k;
      
      std::vector<int> vec;
      
      for(int i = 0; i < n; i++) {
        int vi; std::cin >> vi;
        vec.push_back(vi);
      }
      
      int best_diff = std::numeric_limits<int>::max();
      int l = 0;
      int r = 0;
      int curr_sum = vec[0];
      std::pair<int, int> best_interval = std::make_pair(-1, -1);
      
      while(l < n && r < n) {
        
        if(std::abs(curr_sum - k) < best_diff) {
          best_diff = std::abs(curr_sum - k);
          best_interval = std::make_pair(l,r);
          
          // If an interval with sum k has been found, exit the loop
          if(best_diff == 0) {
            l = n;
          }
        }
        
        if(curr_sum > k) {
          curr_sum -= vec[l];
          l++;
        } else {
          r++;
          curr_sum += vec[r];
        }
      }
      
      std::cout << best_interval.first << " " << best_interval.second << std::endl;
    }
}