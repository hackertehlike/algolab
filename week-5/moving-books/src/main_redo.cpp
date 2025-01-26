`#include <bits/stdc++.h>

using namespace std;

void testcase() {
  int n, m; cin >> n >> m;
  
  multiset<int, std::greater<int>> strengths;
  for(int i = 0; i < n; i++) {
    int si; cin >> si;
    strengths.insert(si);
  }
  
  multiset<int, std::greater<int>> boxes;
  for(int i = 0; i < m; i++) {
    int wi; cin >> wi;
    boxes.insert(wi);
  }
  
  if(*strengths.begin() < *boxes.begin()) {
    cout << "impossible" << endl;
    return;
  }
  
  auto friend_it = strengths.begin();
  int rounds = 1;
  while(!boxes.empty()) {
    auto friend_strength = *friend_it;
    
    if(boxes.lower_bound(friend_strength) == boxes.end()) {
      strengths.erase(friend_strength);
      friend_it = strengths.begin();
      rounds++;
      continue;
    } else {
      boxes.erase(boxes.lower_bound(friend_strength));
    }
    
    if(++friend_it == strengths.end() && !boxes.empty()) {
      friend_it = strengths.begin();
      rounds++;
    }
  }
  
  cout << 3*(rounds-1) + 2 << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) testcase();
}