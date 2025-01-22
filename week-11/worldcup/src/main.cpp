#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 Point;


// choose input type (input coefficients must fit)
typedef double D;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpz)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<D> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct Warehouse {
  int supply;
  Point location;
  int alcohol_content;
  
  Warehouse(int s, Point p, int a) : supply(s), location(p), alcohol_content(a) {};
};

struct Stadium {
  int demand;
  Point location;
  int upper_limit;
  
  Stadium(int d, Point p, int u) : demand(d), location(p), upper_limit(u) {};
};

struct Contour {
  Point location;
  long radius;
  
  Contour(Point p, long r) : location(p), radius(r) {};
};


long floor_to_long(const CGAL::Quotient<CGAL::Gmpq>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase() {
  int n, m, c; std::cin >> n >> m >> c;
  
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  
  std::vector<Point> points;
  std::vector<Warehouse> warehouses;
  
  for(int i = 0; i < n; i++) {
    long x, y; int s, a; std::cin >> x >> y >> s >> a;
    warehouses.push_back(Warehouse(s, Point(x, y), a));
    points.push_back(Point(x, y));
    
    for(int j = 0; j < m; j++) {
      // Supply constraints LHS
      lp.set_a(i * m + j, i, 1);
    }
    
    // Supply constraints RHS
    lp.set_b(i, s);
  }
  
  std::vector<Stadium> stadiums;
  
  for(int j = 0; j < m; j++) {
    long x, y; int u, d; std::cin >> x >> y >> d >> u;
    stadiums.push_back(Stadium(d, Point(x, y), u));
    points.push_back(Point(x, y));
    
    for (int i = 0; i < n; i++) {
      // // Demand constraints LHS
      lp.set_a(i * m + j, n + 2 * j, 1);
      lp.set_a(i * m + j, n + 2 * j + 1, -1);
      
      // // Anti-riot constraints LHS
      lp.set_a(i * m + j, n + 2 * m + j, warehouses[i].alcohol_content);
    
    }
    
    // // Demand constraints RHS
    lp.set_b(n + 2 * j, d);
    lp.set_b(n + 2 * j + 1, -d);
    
    // // Anti-riot constraints RHS
    lp.set_b(n + 2 * m + j, u * 100);
  }
  
  std::vector<std::vector<double>> revenues(n, std::vector<double>(m));
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      std::cin >> revenues[i][j];
    }
  }
  
  Triangulation t;
  t.insert(points.begin(), points.end());
  
  std::vector<Contour> contours;
  contours.reserve(100);
  
  // Prefilter contours that are irrelevant
  // (there are no warehouses or stadiums inside)
  for(int k = 0; k < c; k++) {
    long x, y, r; std::cin >> x >> y >> r;
    
    auto p = K::Point_2(x,y);
    auto d_sq = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
    
    if(d_sq > r * r) continue;
    
    contours.push_back(Contour(Point(x, y), r));
  }
  
    
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      
      for(Contour &c : contours) {
        
        Point center = c.location;
        long radius = c.radius;
        Point w = warehouses[i].location;
        Point s = stadiums[j].location;
        
        // std::cout << "radius: " << radius << std::endl;
        // std::cout << "center: " << center << std::endl;
        // std::cout << "w: " << w << std::endl;
        // std::cout << "s: " << s << std::endl;
        
        
        auto d_w = (CGAL::squared_distance(w, center));
        bool w_inside = false;
        if(d_w <= radius * radius) w_inside = true;
        
        auto d_s = (CGAL::squared_distance(s, center));
        bool s_inside = false;
        if(d_s <= radius * radius) s_inside = true;
        
        if((s_inside && !w_inside) || (w_inside && !s_inside)) {
          revenues[i][j] -= 0.01;
          //std::cout << revenues[i][j] << std::endl;
        }
      }
      
      lp.set_c(i * m + j, -revenues[i][j]);
      // std::cout << "For w " << i << " stadium " << j << " effective revenue " << revenues[i][j] << std::endl;
    }
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()) {
    std::cout << "no" << std::endl;
    return;
  } else {
    auto val = s.objective_value();
    std::cout << floor_to_long(-val) << std::endl;
    //std::cout << s << std::endl;
  }
}

int main() {
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
}