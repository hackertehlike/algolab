#include <iostream>
#include <vector>
#include <limits>
int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    
    int n, m, r, b; std::cin >> n >> m >> r >> b;
    std::vector<std::vector<int>> transitions;
    transitions.resize(n);
    for(int i = 0; i < m; i++) {
      int u,v; std::cin >> u >> v;
      transitions[u].push_back(v);
    }
    
    std::vector<int> minmoves, maxmoves;
    minmoves.resize(n+1, std::numeric_limits<int>::max());
    maxmoves.resize(n+1, std::numeric_limits<int>::min());

    minmoves[n] = 0;
    maxmoves[n] = 0;
    
    for(int i = n-1; i > 0; i--) {
      for(auto &target_cell : transitions[i]) {
        minmoves[i] = std::min(minmoves[i], maxmoves[target_cell] + 1);
        maxmoves[i] = std::max(maxmoves[i], minmoves[target_cell] + 1);
      }
    }
    

    if(minmoves[r] < minmoves[b] || (minmoves[r] == minmoves[b] && minmoves[r] % 2 == 1)) std::cout << 0 << std::endl;
    else std::cout << 1 << std::endl;
  }
}