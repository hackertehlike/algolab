// Credit to Theo von Arx's solution: https://gitlab.ethz.ch/varxth/algolab-theo/-/blob/master/pow12/src/algorithm.cpp?ref_type=heads

#include <iostream>
#include <vector>
#include <boost/pending/disjoint_sets.hpp>

void recruit_rebels() {
  
  int n; long r_sq; std::cin >> n >> r_sq;
  r_sq *= r_sq;
  boost::disjoint_sets_with_storage<> uf(n);
  
  std::vector<std::pair<long, long>> planets;
  
  for(int i = 0; i < n; i++) {
    long xi, yi; std::cin >> xi >> yi;
    planets.push_back(std::make_pair(xi, yi));
  }

  std::vector<int> component_sizes(n, 1);
  
  int max_recruited = 0;
  // Work in reverse order of conquest
  for(int i = n-1; i > 0; i--) {
    for(int j = i+1; j < n; j++) {
      // Check if planet i and j are within reach of each other
      long distance_x = planets[i].first - planets[j].first;
      long distance_y = planets[i].second - planets[j].second;
      
      if(distance_x * distance_x + distance_y * distance_y <= r_sq) {
        int root_1 = uf.find_set(i);
        int root_2 = uf.find_set(j);
        if (root_1 != root_2) {
            uf.link(root_1, root_2);
            component_sizes[uf.find_set(i)] = component_sizes[root_1] + component_sizes[root_2];
        }
      }
    }
    // std::cout << uf.component_size[i] << std::endl;
    max_recruited = std::max(max_recruited, std::min(i, component_sizes[uf.find_set(i)]));
  }
  
  std::cout << max_recruited << std::endl;
}

int main() {
  int t; std::cin >> t;
  
  while(t--) {
    recruit_rebels();
  }
}