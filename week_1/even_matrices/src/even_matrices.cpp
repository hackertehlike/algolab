#include <iostream>
#include <vector>

long long n_choose_2(int n) {
  return static_cast<long long>(n) * (n-1) / 2;
}

void testcase() {
  
  int n; std::cin >> n;
  std::vector<std::vector<int>> S(n+1, std::vector<int>(n+1, 0));
   
  for(int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int x_ij; std::cin >> x_ij;
      S[i][j] = S[i-1][j] + S[i][j-1] 
                              - S[i-1][j-1]+ x_ij;
    }
  }
  
  int even_quads = 0;
  
  for(int col_l = 1; col_l <= n; col_l++) {
    for (int col_r = col_l; col_r <= n; col_r++) {
      
      int even = 0;
      int odd = 0;
      
      for(int i = 1; i <= n; i++) {
        int res = S[i][col_r] - S[i][col_l - 1];
        
          (res % 2 == 0) ? ++even : ++odd;
      }
      
      even_quads += n_choose_2(odd) + n_choose_2(even) + even;
    }
  }
  std::cout << even_quads << std::endl;
}


int main() {
  
  std::ios_base::sync_with_stdio(false); // Always for faster I/O
  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
  
  return 0;
}
