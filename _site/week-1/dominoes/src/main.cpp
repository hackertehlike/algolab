#include <iostream>
#include <vector>

int main() {
  int t; std::cin >> t;

  while(t--) {
    std::vector<int> doms;
    int n; std::cin >> n;
    while(n--) {
      int h; std::cin >> h;
      doms.push_back(h);
    }
  
    int fuel = doms[0];
    std::vector<int>::size_type curr_dom = 0;  // Changed to match the type returned by doms.size()
  
    while(fuel > 0 && curr_dom < doms.size()) {
      if(doms[curr_dom] >= fuel) fuel = doms[curr_dom];
      fuel--;
      curr_dom++;
    }
  
    std::cout << curr_dom << std::endl;
  }
}
