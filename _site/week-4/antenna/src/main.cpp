#include <iostream>
#include <vector>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 Point;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

// take from the example file but ALSO FLIP THE OPERATIONS
double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n;
  std::cin >> n;
  
  while (n != 0) {
    
    std::vector<Point> P(n);
    // DECLARE OUTSIDE OR YOU GET TIME EXCEEDED
    long int xi, yi;
    
    for (int i = 0; i < n; i++) {
      std::cin >> xi >> yi;
      Point p(xi, yi);
      P[i] = p;
    }
    
    // Construct the minimum enclosing circle from the points
    Min_circle mc(P.begin(), P.end(), true);  // Compute the enclosing circle
    
    // Output the rounded radius
        std::cout << std::fixed << std::setprecision(0) << ceil_to_double(CGAL::sqrt(mc.circle().squared_radius())) << "\n";
    // Read the next value for n
      std::cin >> n;
  }
}
