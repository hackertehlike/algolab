#include <iostream>
#include <queue>

struct Boat {
  int l;
  int p;
  
  bool operator<(const Boat &other) const {
    return p > other.p;
  }
  
  Boat(int l, int p) {
    this->l = l;
    this->p = p;
  }
};

void testcase() {
  
  int n; std::cin >> n;
  
  std::priority_queue<Boat> boats;
  
  for(int i = 0; i < n; i++) {
    int l, p; std::cin >> l >> p;
    boats.push(Boat(l, p));
  }
  
  // take the first boat fo sho
  
  Boat curr_boat = boats.top();
  
  int prev_end = curr_boat.p;
  int curr_end = prev_end;
  int num_boats = 1;
  
  boats.pop();
  
  while(!boats.empty()) {
    
    curr_boat = boats.top();
    boats.pop();

    
    // we'll have to make a choice since the last boat in consideration is
    // currently occupying the ring
    if(curr_boat.p < curr_end) {
      curr_end = std::min(curr_end, std::max(curr_boat.p, prev_end + curr_boat.l));
    } 
    // this boat lives in harmony with the prev one
    else {
      prev_end = curr_end;
      curr_end = std::max(curr_boat.p, prev_end + curr_boat.l);
      num_boats++;
    }
    
  }
  
  std::cout << num_boats << std::endl;
  
}

int main() {
  
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
  
  return 0;
}