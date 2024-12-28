#include <iostream>
#include <queue>

struct Ball {
  int n;
  int t;
  
  bool operator<(const Ball &other) const {
    return this->t > other.t;
  }
  
  Ball(int n, int t) {
    this->n = n;
    this->t = t;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  while(t--) {
    int n; std::cin >> n;
    
    std::vector<int> time_until_explosion;
    
    for(int i = 0; i < n; i++) {
      int ti; std::cin >> ti;
      if(i > 0) {
        if(i % 2 == 0) {
          ti = std::min(ti, time_until_explosion[(i - 2) / 2] - 1);
        } else {
          ti = std::min(ti, time_until_explosion[(i - 1) / 2] - 1);
        }
      }
      time_until_explosion.push_back(ti);
    }
    
    
    std::vector<bool> deactivated(n, false);
    std::priority_queue<Ball> deactivatable;
    //int num_deactivated = 0;

    // Add all "leaf" bombs to deactivatable
    for (int i = (n-1)/2; i < n; i++) {
      deactivatable.push(Ball(i, time_until_explosion[i]));
    }
    
    int pi = 0;
    
    while(!deactivatable.empty()) {
      Ball curr_ball = deactivatable.top();
      
      deactivatable.pop();
      
        // std::cout << "Time step: " << pi << std::endl;
        // std::cout << "Remaining time for curr bomb: " << curr_ball.t << std::endl;
        // std::cout << "Curr ball: " << deactivatable.top().n << std::endl;
      
      // check if bomb has already run out of time
      if(pi >= curr_ball.t) {
        std::cout << "no" << std::endl;
        break;
      }
      
      deactivated[curr_ball.n] = true;
      // std::cout << "Ball " << curr_ball.n << " deactivated." << std::endl;
      
      if(curr_ball.n == 0) {
        std::cout << "yes" << std::endl;
        // should be empty at this point but... sanity check.
        break;
      }
      
      if(curr_ball.n % 2 == 0 && deactivated[curr_ball.n - 1]) {
        // std::cout << "Ball is right ball and left ball also deactivated." << std::endl;
        deactivatable.push(Ball((curr_ball.n - 2) / 2,
                        time_until_explosion[(curr_ball.n - 2) / 2]));
        // std::cout << "Ball " << (curr_ball.n - 2) / 2 << " added to schedule." << std::endl;

      } else if (curr_ball.n % 2 == 1 && deactivated[curr_ball.n + 1]) {
        // std::cout << "Ball is left ball and right ball also deactivated." << std::endl;
        deactivatable.push(Ball((curr_ball.n - 1) / 2,
                        time_until_explosion[(curr_ball.n - 1) / 2]));
        // std::cout << "Ball " << (curr_ball.n - 1) / 2 << " added to schedule." << std::endl;
      }
      
      
      // std::cout << "Size of queue: " << deactivatable.size() << std::endl;
      // std::cout << "Next: " << deactivatable.top().n << std::endl;
      pi++;
    }
    
  }
  
  return 0;
}