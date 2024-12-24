#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

// choose input type (input coefficients must fit)
typedef double IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const CGAL::Quotient<ET> x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}


void testcase() {
  int n, m, h, w; std::cin >> n >> m >> h >> w;
  
  std::vector<std::pair<int, int>> new_nails;
  
  for(int i = 0; i < n; i++) {
    int xi, yi; std::cin >> xi >> yi;
    
    new_nails.push_back(std::make_pair(xi, yi));
  }
  
  std::vector<std::pair<int, int>> old_nails;
  
  for(int i = 0; i < m; i++) {
    int xi, yi; std::cin >> xi >> yi;
    
    old_nails.push_back(std::make_pair(xi, yi));
  }
  
  Program lp (CGAL::SMALLER, true, 1, false, 0);
  
  int num_constraints = 0;
  
  for(int i = 0; i < n; i++) {
    for(int j = i+1; j < n; j++) {
      
      auto diff_x = std::abs(new_nails[i].first - new_nails[j].first);
      auto diff_y = std::abs(new_nails[i].second - new_nails[j].second);
      
      auto b = std::max(double(2 * diff_x) / w, double(2 * diff_y) / h);

      lp.set_a(i, num_constraints, 1);
      lp.set_a(j, num_constraints, 1);
      
      lp.set_b(num_constraints, CGAL::to_double(b));

      num_constraints++;
    }

    lp.set_c(i, -1);
  }
  
  for(int i = 0; i < n; i++) {
    
    double min_constr = std::numeric_limits<double>::max(); 
    for(int j = 0; j < m; j++) {
      
      auto diff_x = std::abs(new_nails[i].first - old_nails[j].first);
      auto diff_y = std::abs(new_nails[i].second - old_nails[j].second);
      
      auto b = std::max(double(2 * diff_x) / w - 1, double(2 * diff_y) / h - 1);

      min_constr = std::min(b, min_constr);
    }
    
    lp.set_u(i, true, min_constr);
    
  }
  
  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  // output solution
  
  // std::cout << s; 
  std::cout << (long) -floor_to_double((s.objective_value() * 2 * (w+h))) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
  
  return 0;
}