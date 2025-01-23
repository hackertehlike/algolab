/// REVIEW NOTES :
/// Isolate the variables so that coeffs are 1.
/// BE CAREFUL WHERE YOU PUT THE -1 IN THE OLD NAIL COMPARISON
/// I.E. NOT INSIDE THE PARANTHESIS

#include <bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
using namespace std;

typedef double D;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<D> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double ceil_to_double(const CGAL::Quotient<CGAL::Gmpq>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase() {
  int n, m, h, w; cin >> n >> m >> h >> w;
  
  vector<tuple<int, int>> free_nails;
  for(int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    free_nails.push_back({x, y});
  }
  
  vector<tuple<int, int>> occupied_nails;
  for(int j = 0; j < m; j++) {
    int x, y; cin >> x >> y;
    occupied_nails.push_back({x, y});
  }
  
  Program lp (CGAL::SMALLER, true, 1, false, 0); 
  int num_constraints = 0;
  
  for(int i = 0; i < n; i++) {
    for(int k = i+1; k < n; k++) {
      if (i == k) continue;
      
      auto [xi, yi] = free_nails[i];
      auto [xk, yk] = free_nails[k];
      
      double x_diff = 2*abs(double(xi - xk) / w);
      double y_diff = 2*abs(double(yi - yk) / h);
      
      auto b = max(x_diff, y_diff);
      
      lp.set_a(i, num_constraints, 1);
      lp.set_a(k, num_constraints, 1);
      lp.set_b(num_constraints, CGAL::to_double(b));
      num_constraints++;
    }
    
    lp.set_c(i, -1);
  }
  
  for(int i = 0; i < n; i++) {
    
    double most_constricting_b = numeric_limits<long>::max();
    for(int j = 0; j < m; j++) {
      auto [xi, yi] = free_nails[i];
      auto [xk, yk] = occupied_nails[j];
      
      double x_diff = 2*abs(double(xi - xk) / w) - 1;
      double y_diff = 2*abs(double(yi - yk) / h) - 1;
      
      auto b = max(x_diff, y_diff);
      most_constricting_b = min(most_constricting_b, b);
    }
    lp.set_u(i, true, most_constricting_b);
  }
  
  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  // output solution
  cout << (long) -ceil_to_double(s.objective_value()) * 2*(w+h) << endl; 
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) {
    testcase();
  }
}