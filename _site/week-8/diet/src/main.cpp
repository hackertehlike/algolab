#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(int n) {
  int m; std::cin >> m;
  
  std::vector<std::pair<int, int>> min_max_amounts;
  
  for(int i = 0; i < n; i++) {
    int min, max;
    std::cin >> min >> max;
    min_max_amounts.push_back(std::make_pair(min, max));
  }
  
  // for(auto &elem : min_max_amounts) {
  //   std::cout << "min amount: " << elem.first << " max amount: " << elem.second << std::endl;
  // }
  
  std::vector<int> prices;
  std::vector<std::vector<int>> nutrients;
  
  for(int j = 0; j < m; j++) {
    int p; std::cin >> p;
    prices.push_back(p);
    
    std::vector<int> nutrients_in_j;
    for(int i = 0; i < n; i++) {
      int C_ij; std::cin >> C_ij;
      nutrients_in_j.push_back(C_ij);
    }
    
    nutrients.push_back(nutrients_in_j);
  }
  
  
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  
  // set up constraints
  for(int i = 0; i < n; i++) {
    int min_amount = min_max_amounts[i].first;
    int max_amount = min_max_amounts[i].second;
    
    for(int j = 0; j < m; j++) {
      int amount_of_nut_i_in_food_j = nutrients[j][i]; // Careful! Indexing
      
      // std::cout << "amount of nutrient " << i << " in food " << j << " : " << amount_of_nut_i_in_food_j << std::endl;
      
      lp.set_a(j, 2*i, amount_of_nut_i_in_food_j);
      lp.set_a(j, 2*i+1, -amount_of_nut_i_in_food_j);
    }
    
    lp.set_b(2*i, max_amount);
    lp.set_b(2*i+1, -min_amount);
  }
  
  // set up objective
  for(int j = 0; j < m; j++) {
    lp.set_c(j, prices[j]);
  }
  

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  // output solution
  if(s.is_infeasible()) {
    std::cout << "No such diet." << std::endl;
    return;
  }
  
  std::cout << static_cast<int>(CGAL::to_double(s.objective_value())) << std::endl; 
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