#include <vector>
#include <iostream>
#include <algorithm>

void testcase() {
  std::cout << "new testcase" << std::endl;
  int n, k, w; std::cin >> n >> k >> w;
  
  std::vector<int> men_requirements;
  
  for(int i = 0; i < n; i++) {
    int ci; std::cin >> ci;
    std::cout << "c" << i << ": " << ci << std::endl;
    men_requirements.push_back(ci);
  }
  
  std::vector<std::vector<int>> waterways(w);
  
  for(int i = 0; i < w; i++) {
    int l; std::cin >> l;
    for(int j = 0; j < l; j++) {
      int ri; std::cin >> ri;
      waterways[i].push_back(ri);
    }
  }
  
  std::vector<std::vector<int>> extended_waterways;
  
  if(w == 1) extended_waterways.push_back(waterways[0]);
  
  for(int i = 0; i < w; i++) {
    for(int j = i+1; j < w; j++) {
      std::vector<int> w1 = waterways[i];
      std::vector<int> w2 = waterways[j];
      
      std::reverse(w1.begin(), w1.end());
      
      std::cout << w1.size() << std::endl;
       std::cout << w2.size() << std::endl;
      
      w1.insert(w1.end(), w2.begin()+1, w2.end());
      extended_waterways.push_back(w1);
    }
  }
  
  // for(auto &ext_wateray: extended_waterways) {
    // std::cout << "extended waterway: " << std::endl;
    // for(auto &elem: ext_wateray) std::cout << elem << " ";
    // std::cout << std::endl;
  // }
  
  int curr_max_islands = - 1;
  int w_ct = 0;
  
  
  for(auto &waterway : extended_waterways) {
    
    // std::cout << "on waterway " << w_ct++ << std::endl;
    
    int l = 0;
    int r = 0;
    
    
    // std::cout << "waterway[0]: " << waterway[0] << std::endl;

    int total_men_used = men_requirements[waterway[0]];
    
    while(r < waterway.size() && l < waterway.size()) {
      
      // std::cout << "curr interval: " << l << " - " << r << std::endl;
      // std::cout << "total men used: " << total_men_used << std::endl;
      if(total_men_used > k) {
        
        // std::cout << "too many men" << std::endl;
        total_men_used = total_men_used - men_requirements[waterway[l++]];
        if (l > r) {
          if (r + 1 < waterway.size()) {
            total_men_used += men_requirements[waterway[++r]];
          } else {
              break; // Exit if we can't increase the window size anymore
          }
        }

      }
      
      else if (total_men_used < k) {
        
        // std::cout << "too few men" << std::endl;
        if (r + 1 < waterway.size()) {
            total_men_used += men_requirements[waterway[++r]];
        } else {
            break; // Exit if we can't increase the window size anymore
        }
    }

      
      else {
        // std::cout << "perfect number of men" << std::endl;
        int len_curr_subway = r - l + 1;
        if(len_curr_subway > curr_max_islands) {
          curr_max_islands = len_curr_subway;
        }
        r++;
        l++;
      }
      
    }
  }
  
  if(curr_max_islands == -1) std::cout << "0" << std::endl;
  else std::cout << curr_max_islands << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
  
  return 0;
}