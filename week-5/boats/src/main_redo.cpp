#include <bits/stdc++.h>

using namespace std;

void testcase() {
  int n; cin >> n;
  
  auto cmp = [](pair<int, int> &p1, pair<int, int> &p2) {
    return p1.second > p2.second;
  };
  
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> boats(cmp);
  for(int i = 0; i < n; i++) {
    int l, peg; cin >> l >> peg;
    boats.push({l, peg});
  }
  
  int num_boats = 1;
  int prev_end = numeric_limits<int>::min();
  int curr_end = boats.top().second;
  
  boats.pop();
  
  while(!boats.empty()) {
    auto [len, peg] = boats.top();
    boats.pop();
    
    if(peg >= curr_end) {
      num_boats++;
      prev_end = curr_end;
      curr_end = max(prev_end+len, peg);

    } else {
      curr_end = min(curr_end, max(prev_end+len, peg));
    }
  }
  
  cout << num_boats << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) testcase();
}