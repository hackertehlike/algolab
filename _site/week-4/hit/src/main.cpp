#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>


typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

int main() {
  
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n; std::cin >> n;
  
  while(n != 0) {
    long x, y, a, b;
    std::cin >> x >> y >> a >> b;
    
    R phileas_ray(P(x,y), P(a,b));
    
    bool intersects = false;
    
    for(int i = 0; i < n; i++) {
      long r, s, t, u;
      std::cin >> r >> s >> t >> u;
      
      
      if (!intersects) {
        S segment(P(r,s), P(t,u));
        intersects = CGAL::do_intersect(phileas_ray, segment) ? true : intersects;
      }
    }
    
    if(intersects) std::cout << "yes" << std::endl;
    else std::cout << "no" << std::endl;
    
    std::cin >> n;
  }
}