///3

#include <vector>
#include <iostream>
#include <algorithm>

void testcase() {
  std::cout << "new testcase" << std::endl;
  int n, k, w; std::cin >> n >> k >> w;
  
  std::vector<int> men_requirements(n);
  
  for(int i = 0; i < n; i++) {
    int ci; std::cin >> ci;
    
    men_requirements[i] = ci;
  }
  
  std::cout << __LINE__ << std::endl;
  
  std::vector<std::vector<int>> waterways(w);
  
  for(int i = 0; i < w; i++) {
    int l; std::cin >> l;
    
    for(int j = 0; j < l; j++) {
      int r; std::cin >> r;
      waterways[i].push_back(r);
    }
  }
  
  
  std::cout << __LINE__ << std::endl;
  
  std::vector<std::vector<int>> super_waterways;
  
  if(w == 1) super_waterways.push_back(waterways[0]);
  
  std::cout << "waterways: " << waterways.size() << std::endl;
  
  for(int i = 0; i < w; i++) {
    for(int j = i+1; j < w; j++) {
      
      // Create a new vector to hold the merged result
    std::vector<int> merged;

    merged.insert(merged.end(), waterways[i].rbegin(), waterways[i].rend());
    std::cout << __LINE__ << std::endl;
    merged.insert(merged.end(), waterways[j].begin(), waterways[j].end());
    std::cout << __LINE__ << std::endl;
    super_waterways.push_back(merged);
    std::cout << __LINE__ << std::endl;
    }
  }
    std::cout << __LINE__ << std::endl;

  int max = 0;
  
  // for(auto &elem : men_requirements) std::cout << elem << " ";
  // std::cout << std::endl;
  
  for(const auto &waterway : super_waterways) {
    int l = 0, r = 0, curr_sum = 0;
    
    if (!waterway.empty()) curr_sum = men_requirements[waterway[0]];

    while (r < waterway.size()) {
        while (curr_sum > k && l <= r) {
            curr_sum -= men_requirements[waterway[l++]];
        }

        if (curr_sum == k) {
            max = std::max(max, r - l + 1);
        }

        if (++r < waterway.size()) {
            curr_sum += men_requirements[waterway[r]];
        }
    }
}

  std::cout << __LINE__ << std::endl;
  std::cout << max << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
  
  return 0;
}