/// REVIEW NOTES :
/// During the orientation fix, we want to swap them even if they are collinear. But not during inclusion test.
/// Sliding window easier in two while blocks within the outer one
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

using namespace std;

bool is_contained(vector<P> map_part, P q) {
  for(int i = 0; i < 3; i++) {
    if (CGAL::orientation(map_part[2*i], map_part[2*i+1], q) == CGAL::RIGHT_TURN)
      return false;
  }
  return true;
}

void testcase() {
  int m, n; cin >> m >> n;
  
  vector<P> hike_pts;
  
  for(int i = 0; i < m; i++) {
    P pt; cin >> pt;
    hike_pts.push_back(pt);
  }
  
  vector<vector<P>> map_parts;
  for(int i = 0; i < n; i++) {
    vector<P> part;
    P q0, q1, q2, q3, q4, q5; cin >> q0 >> q1 >> q2 >> q3 >> q4 >> q5;
    part.push_back(q0); part.push_back(q1); part.push_back(q2);
    part.push_back(q3); part.push_back(q4); part.push_back(q5);
    
    for(int j = 0; j < 3; j++) {
      if(CGAL::orientation(part[2*j], part[(2*j+1)%6], part[(2*(j+1))%6]) != CGAL::LEFT_TURN) {
        swap(part[2*j], part[(2*j+1)]);
      }
    }
    map_parts.push_back(part);
  }
  
  vector<vector<bool>> leg_in_part(m-1, vector<bool>(n, false));
  for(int i= 0; i < n; i++) {
    bool prev = is_contained(map_parts[i], hike_pts[0]);
    for(int j = 1; j < m; j++) {
      bool next = is_contained(map_parts[i], hike_pts[j]);
      if(prev && next) leg_in_part[j-1][i] = true;
      prev = next;
    }
  }
  
  vector<int> leg_coverage(m-1, 0);
  int left = 0;
  int right = 0;
  int num_covered = 0;
  int min_window = n;
  
  while(right < n) {
    
    while(num_covered < m-1 && right < n) {
      for(int j = 0; j < m-1; j++) {
        if(leg_in_part[j][right]) {
          if(++leg_coverage[j] == 1) num_covered++;
        }
      }
      right++;
    }
    
    
    while(num_covered == m-1) {    
      min_window = min(min_window, right-left);
      for(int j = 0; j < m-1; j++) {
        if(leg_in_part[j][left]) {
          if(--leg_coverage[j] == 0) num_covered--;
        }
      }
      left++;
    } 
    
    
  }
  
  cout << min_window << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) testcase();
}