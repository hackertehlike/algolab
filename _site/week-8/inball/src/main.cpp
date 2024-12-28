#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


void testcase(int n) {
  int d; std::cin >> d;
  
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  
  for(int i = 0; i < n; i++) {
    
    int norm_sq = 0;
    
    for(int j = 0; j < d; j++) {
      int a_id; std::cin >> a_id;
      
      norm_sq += a_id * a_id;
      
      lp.set_a(j, i, a_id);
     }
     
     int norm = std::sqrt(norm_sq);
     
     lp.set_a(d, i, norm);
    
    int b_i; std::cin >> b_i;
    lp.set_b(i, b_i);
  }
  
  lp.set_c(d, -1);
  
  lp.set_l(d, true, 0); // radius nonnegative, DON'T FORGET the second argument
  
  // CGAL::Quadratic_program_options options;
  // options.set_pricing_strategy(CGAL::QP_BLAND);
  // solve the program, using ET as the exact type
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  int radius = static_cast<int>(CGAL::to_double(s.objective_value()) * -1);
  
  //output solution
  
  if(s.is_infeasible()) std::cout << "none" << std::endl;
  else if(s.is_unbounded()) std::cout << "inf" << std::endl;
  else std::cout << radius << std::endl; 
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int n; std::cin >> n;
  
  
  while(n) {
    testcase(n);
    std::cin >> n;
  }
  
  return 0;
}