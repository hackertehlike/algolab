#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(int p) {
  int a, b; std::cin >> a >> b;
  
  if(p == 1) {
    // Maximization problem
    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    
    // set the coefficients of A and b
    const int x = 0; 
    const int y = 1;
    
    lp.set_a(x, 0,  1); lp.set_a(y, 0, 1); lp.set_b(0, 4);  //  x + y  <= 4
    lp.set_a(x, 1, 4); lp.set_a(y, 1, 2); lp.set_b(1, a*b);  // 4x + 2y <= ab
    lp.set_a(x, 2, -1); lp.set_a(y, 2, 1); lp.set_b(2, 1); // -x + y <= 1
    
    // objective function
    lp.set_c(x, a); lp.set_c(y, -b); // a*x - b*y
    
    
    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));
    
    
    if(s.is_infeasible()) std::cout << "no" << std::endl;
    else {
    
      auto sol = s.objective_value();
      int sol_d = -1 * static_cast<int>(CGAL::to_double(sol));
      std::cout << sol_d << std::endl;
    }
    
  } else {
    // Minimization problem
    
    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::LARGER, false, 0, true, 0); 
    
    // set the coefficients of A and b
    const int x = 0; 
    const int y = 1;
    const int z = 2;
    
    lp.set_a(x, 0,  1); lp.set_a(y, 0, 1); lp.set_b(0, -4);  //  x + y  >= -4
    lp.set_a(x, 1, 4); lp.set_a(y, 1, 2); lp.set_a(z, 1, 1); lp.set_b(1, -a*b);  // 4x + 2y + z <= -ab
    lp.set_a(x, 2, -1); lp.set_a(y, 2, 1); lp.set_b(2, -1); // -x + y >= -1
    
    // objective function
    lp.set_c(x, a); lp.set_c(y, b); lp.set_c(z, 1); // a*x + b*y + z
  
    
    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));
    
    if(s.is_infeasible()) std::cout << "no" << std::endl;
    else {
      auto sol = s.objective_value();
      int sol_d = static_cast<int>(CGAL::to_double(sol));
      std::cout << sol_d << std::endl;
    }
    
  }
  
  
}


int main() {
  std::ios_base::sync_with_stdio(false);
  
  int p; std::cin >> p;
  while(p) {
    
    testcase(p);
    std::cin >> p;
  }
  
  
  return 0;
}