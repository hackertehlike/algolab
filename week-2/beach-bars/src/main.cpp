#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> parasols(n);

        for (int i = 0; i < n; i++) {
            std::cin >> parasols[i];
        }

        std::sort(parasols.begin(), parasols.end());

        int l = 0;
        int r = 0;

        int max_parasols = -1;
        int min_longest_distance = -1;
        std::vector<int> optimal_locations;

        
        while(r < n) {
          while(l < r && parasols[r] - parasols[l] > 200) {
            l++; // Shift the window to maintain the 100m radius condition
          }
          
            int distance = parasols[r] - parasols[l];
            
            // Update if we found a window with more parasols or the same number but better distance
            if (r-l+1 > max_parasols) {
                optimal_locations.clear();
                max_parasols = r-l+1;
                min_longest_distance = distance/2 + (distance%2);
            }
            
            if(r-l+1 == max_parasols) {
              if(distance/2 + (distance%2) < min_longest_distance) {
                min_longest_distance = distance/2 + (distance%2);
                optimal_locations.clear();
              }
              
              if(distance/2 + (distance%2) == min_longest_distance) {
                if(distance%2 == 0) optimal_locations.push_back(parasols[l] + distance/2);
                else {
                  optimal_locations.push_back(parasols[l] + distance/2);
                  optimal_locations.push_back(parasols[l] + distance/2 + 1);
                }
              }
            }

            r++; // Expand the window by increasing the right pointer
        }

        std::cout << max_parasols << " " << min_longest_distance << std::endl;
        for (auto &elem : optimal_locations) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
