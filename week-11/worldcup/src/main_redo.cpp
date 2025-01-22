#include <bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 P;
// typedef Triangulation::Edge_iterator  Edge_iterator;

// choose input type (input coefficients must fit)
typedef double IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

long floor_to_double(const CGAL::Quotient<CGAL::Gmpq>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase() {
  int n, m, c; std::cin >> n >> m >> c;
  
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  std::vector<P> points;

  std::vector<std::tuple<int, int, int, int>> warehouses;
  for(int i = 0; i < n; i++) {
    int x, y, s, a; std::cin >> x >> y >> s >> a;
    warehouses.push_back({x, y, s, a});
    points.push_back(P(x, y));
  }
  
  std::vector<std::tuple<int, int, int, int>> stadiums;
  for(int j = 0; j < m; j++) {
    int x, y, d, u; std::cin >> x >> y >> d >> u;
    stadiums.push_back({x, y, d, u});
    points.push_back(P(x, y));
  }
  
  // Supply constraints
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      lp.set_a(j + i * m, i, 1);
    }
    lp.set_b(i, std::get<2>(warehouses[i]));
  }
  
  // Demand constraints
  for(int j = 0; j < m; j++) {
    for(int i = 0; i < n; i++) {
      lp.set_a(j + i * m, j + n, -1);
      lp.set_a(j + i * m, j + m + n, 1);
      lp.set_a(j + i * m, j + 2*m + n, std::get<3>(warehouses[i]));
    }
    lp.set_b(j + n, -std::get<2>(stadiums[j]));
    lp.set_b(j + m + n, std::get<2>(stadiums[j]));
    lp.set_b(j + 2*m + n, std::get<3>(stadiums[j])*100);
  }
  
  std::vector<std::vector<double>> revenues(n, std::vector<double>(m));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      int r_ws; std::cin >> r_ws;
      revenues[i][j] = r_ws;
    }
  }
  
  Triangulation t;
  t.insert(points.begin(), points.end());
  
  std::vector<std::tuple<P, int>> contour_lines;
  // Contour lines
  for(int i = 0; i < c; i++) {
    P center; int r; std::cin >> center >> r;
    
    if(CGAL::squared_distance(t.nearest_vertex(center)->point(), center) > r*r) continue;
    contour_lines.push_back({center, r});
  }
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      P warehouse_p = P(std::get<0>(warehouses[i]), std::get<1>(warehouses[i]));
      P stadium_p = P(std::get<0>(stadiums[j]), std::get<1>(stadiums[j]));
      
      for (const auto &[center, r] : contour_lines) {
        bool w_inside = (CGAL::squared_distance(warehouse_p, center) <= r*r);
        bool s_inside = (CGAL::squared_distance(stadium_p, center) <= r*r);
        
        if((w_inside && !s_inside) || (!w_inside && s_inside)) {
          revenues[i][j] -= 0.01;
        }
      }
      
      lp.set_c(j + i * m, -revenues[i][j]);
    }
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  if(s.is_infeasible()) std::cout << "no" << std::endl;
  else {
    std::cout << floor_to_double(-s.objective_value()) << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
}