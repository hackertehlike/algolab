#include <bits/stdc++.h>

using namespace std;

void testcase() {
  int n, m, k; long x; cin >> n >> m >> x >> k;
  
  vector<vector<tuple<int, int>>> children(n);
  for(int i = 0; i < m; i++) {
    int u, v, p; cin >> u >> v >> p;
    children[u].push_back({v, p});
  }
  
  vector<vector<long>> dp(n, vector<long>(k+1));
  for(int i = 0; i < n; i++) dp[i][0] = 0;
  
  bool possible = false;
  int num_moves = -1;
  
  for(int j = 1; j < k+1; j++) {
    for(int i = 0; i < n; i++) {
      if(children[i].empty()) dp[i][j] = dp[0][j];
      else {
        long max_score = 0;
        for(const auto &child : children[i]) {
          max_score = max(max_score, dp[get<0>(child)][j-1] + get<1>(child));
        }
        dp[i][j] = max_score;
      }
    }
    if(dp[0][j] >= x) {
      possible = true;
      num_moves = j;
      break;
    }
  }
  
  if(possible) cout << num_moves << endl;
  else cout << "Impossible" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
}