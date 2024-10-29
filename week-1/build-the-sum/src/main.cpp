#include <iostream>

int main() {
  
  int t; std::cin >> t;
  
  for(int i = 0; i < t; i++) {
    
    int n; std::cin >> n;
    int sum = 0;
    
    for (int j = 0; j < n; j++) {
      
      int a_j; std::cin >> a_j;
      sum += a_j;
    }
    
    std::cout << sum << std::endl;
  }
  
  
  return 0;
}