#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

struct ray_sort {
    bool operator()(const R& a, const R& b) const {
        return a.source() < b.source();  // Compare the source points of the rays
    }
};


int main() {
  int t; std::cin >> t;
  
  while(t--) {
    int n; std::cin >> n;
    
    std::vector<R> bike_paths;
    std::vector<S> bike_segs(n);
    std::vector<bool> bike_stops(n, false);
    
    for(int i = 0; i < n; i++) {
      long y0, x1, y1; std::cin >> y0 >> x1 >> y1;
      
      bike_paths.push_back(R(P(0, y0), P(x1, y1)));
    }
    
    std::sort(bike_paths.begin(), bike_paths.end(), ray_sort());
    
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        if(!bike_stops[i]) {
          if(!bike_stops[j]) {
            //bike i and j are rays
            if(CGAL::do_intersect(bike_paths[i], bike_paths[j])) {
              auto o = CGAL::intersection(bike_paths[i], bike_paths[j]);
              //update both to segments
              bike_stops[i] = true;
              bike_stops[j] = true;
              
              
            }
          } else {
            // bike i is ray and bike j is segment
          }
        } else {
          if(!bike_stops[j]) {
            //bike i is segment and j is ray
            
          } else {
            // bike i and jay are both segments
          }
        }
      }
    }
  }
}