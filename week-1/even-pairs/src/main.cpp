#include <iostream>
#include <vector>

typedef std::vector<int> vi;

int choose(int n, int k) {
    if (k == 0) return 1;
    return (n * choose(n - 1, k - 1)) / k;
}

int main() {
  
  int t; std::cin >> t;
  vi vec;
  
  for(int i = 0; i < t; i++) {
    
    vec.clear();
    
    int n; std::cin >> n;
    
    int prefix_sum = 0;
    int odd = 0;
    int even = 0;
    
    for(int j = 0; j < n; j++) {
      
      int x_j; std::cin >> x_j;
      prefix_sum += x_j;
      vec.push_back(prefix_sum);
      if(prefix_sum%2 == 0) even++;
      else odd++;
    }
    
    int even_pairs = choose(even, 2);
    int odd_pairs = choose(odd, 2);
    
    int total = even_pairs + odd_pairs + even;
    
    
    std::cout << total << std::endl;
  }
}