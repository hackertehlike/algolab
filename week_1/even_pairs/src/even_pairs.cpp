#include <iostream>
#include <vector>

typedef std::vector<int> vi;

int choose(int n, int k) {
    if (k == 0) return 1;
    return (n * choose(n - 1, k - 1)) / k;
}

int main() {

  std::ios_base::sync_with_stdio(False);
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
     // std::cout << "Now reading: " << x_j << std::endl;
      prefix_sum += x_j;
      vec.push_back(prefix_sum);
     // std::cout << "Pref sum: " << prefix_sum << " " << std::endl;
      if(prefix_sum%2 == 0) even++;
      else odd++;
    }
    
    //std::cout << std::endl;
    /*
    for(int j = 1; j <= n; j++) {
      
      std::cout << "curr elem: " << vec.at(j) << " ";
      std::cout << "prev elem: " << vec.at(j-1) << " ";
      std::cout << "next elem: " << vec.at(j+1) << " ";
      std::cout << std::endl;
      
      if(vec.at(j)%2 == 0) total_even++;
      
      if(vec.at(j-1)%2 == vec.at(j+1)%2) total_even++;
      
      std::cout << "Total even: " << total_even << std::endl;
    }
    */
    
    int even_pairs = choose(even, 2);
    int odd_pairs = choose(odd, 2);
    
    int total = even_pairs + odd_pairs + even;
    
    
    std::cout << total << std::endl;
  }
}
