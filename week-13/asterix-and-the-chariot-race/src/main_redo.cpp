#include <bits/stdc++.h>

using namespace std;

tuple<int, int, int> dfs(int curr, const vector<vector<int>>& children, const vector<int>& repair_costs) {
  
  if(children[curr].empty()) {
    return {repair_costs[curr], repair_costs[curr], 0};
  }
  
  int all_children_cover = 0;
  int min_switch_cost = numeric_limits<int>::max();
  int min_repair_cost = repair_costs[curr];
  
  for(const auto &child : children[curr]) {
    
    auto [repair_child, cover_child, min_cost_grandchildren] = dfs(child, children, repair_costs);

    min_switch_cost = min(min_switch_cost, repair_child - min(repair_child, cover_child));
    all_children_cover += min(repair_child, cover_child);
    min_repair_cost += min(repair_child, min_cost_grandchildren);
  }
  
  return {min_repair_cost, all_children_cover + min_switch_cost, all_children_cover};
}

void testcase() {
  int n; cin >> n;
  
  vector<vector<int>> children(n);
  for(int i = 0; i < n-1; i++) {
    int u, v; cin >> u >> v;
    children[u].push_back(v);
  }
  
  vector<int> repair_costs(n);
  for(int i = 0; i < n; i++) {
    cin >> repair_costs[i];
  }
  
  auto [first, second, third] = dfs(0, children, repair_costs);
  std::cout << min(first,second) << std::endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) {
    testcase();
  }
}