#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

void testcase(int n)
{
  // read points
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for (std::size_t i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }
  // construct triangulation
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  // output all edges
  
  
  int m; std::cin >> m;
  //std::cout << std::setprecision(0) << std::fixed;
  for (int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    K::Point_2 p(x, y);
    
    Triangulation::Vertex_handle v = t.nearest_vertex(p);
    K::Point_2 q = v->point();
    
    std::cout << long(CGAL::squared_distance(p, q)) << std::endl;
  }
  
}

int main() {
  // read number of points
  std::size_t n;
  std::cin >> n;
  
  while (n) {
    testcase(n);
    std::cin >> n;
  }
}