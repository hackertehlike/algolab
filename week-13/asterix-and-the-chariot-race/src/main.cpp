#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

std::vector<std::vector<int>> stages;
std::vector<long> costs;

std::tuple<long, long, long> solve(int curr){
  
  if(stages[curr].size() == 0) {
    return {costs[curr], costs[curr], 0};
  }
  
  // Values to accumulate:
  // Minimal cost while fixing the current city
  // Cost of covering all descendants **excluding** the current city
  // Best child switch cost to cover current node
  
  long min_cost_curr_fixed = costs[curr];
  long min_cost_children_covered = 0;
  long cheapest_switch_to_cover_curr = std::numeric_limits<long>::max();
  
  for(const int child : stages[curr]) {
    auto [min_cost_child_fixed, min_cost_child_covered, min_cost_grandchildren_covered] = solve(child);
    
    // The minimal cost of covering THIS child
    // either by fixing it or covering it with one of its descendants
    long optimal_child_cover = std::min(min_cost_child_fixed, min_cost_child_covered);
    
    min_cost_children_covered += optimal_child_cover; // Accumulate child cover costs
    cheapest_switch_to_cover_curr = std::min(cheapest_switch_to_cover_curr, min_cost_child_fixed - optimal_child_cover);
    
    // Now that we're fixing the current node, we can "relieve" costs for children
    // who were covering themselves by covering them
    min_cost_curr_fixed += std::min(optimal_child_cover, min_cost_grandchildren_covered);
  }
  
  return {min_cost_curr_fixed, min_cost_children_covered + cheapest_switch_to_cover_curr, min_cost_children_covered};
}

void testcase() {
  int n; std::cin >> n;
  
  stages = std::vector<std::vector<int>>(n, std::vector<int>());
  costs = std::vector<long>();
  
  for(int i = 0; i < n-1; i++) {
    int s, t; std::cin >> s >> t;
    stages[s].push_back(t);
  }
  
  for(int i = 0; i < n; i++) {
    long c_i; std::cin >> c_i;
    costs.push_back(c_i);
  }
  
  auto s = solve(0);
  
  std::cout << std::min(std::get<0>(s), std::get<1>(s)) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
  
  return 0;
}