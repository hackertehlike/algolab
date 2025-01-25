#include <bits/stdc++.h>
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

using namespace std;

bool can_do(int a, int p, vector<tuple<int, int, int, int, int>> &stables) {
  
  Program lp (CGAL::LARGER, true, 0, true, 1);
  
  const int h1 = 0;
  const int h2 = 1;
  const int h3 = 2;
  
  int a_sq = a*a;
  int p_sq = p*p;
  int ap = a*p;
  
  for(int stall = 0; stall < stables.size(); stall++) {
    auto [f, c, k, l, m] = stables[stall];
    lp.set_a(h1, stall, k + a_sq);
    lp.set_a(h2, stall, l + p_sq);
    lp.set_a(h3, stall, m + ap);
    lp.set_b(stall, f-c);
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  return !(s.is_infeasible());
}

void testcase() {
  
  int n; cin >> n;
  
  vector<tuple<int, int, int, int, int>> stables(n);
  for(int i = 0; i < n; i++) {
    int f, c, k, l, m; cin >> f >> c >> k >> l >> m;
    stables[i] = {f, c, k, l, m};
  }
  
  vector<int> alpheius(25);
  alpheius[0] = 0;
  for(int i = 1; i < 25; i++) {
    int additional_alpheius; cin >> additional_alpheius;
    alpheius[i] = alpheius[i-1] + additional_alpheius;
  }
  
  vector<int> peneius(25);
  peneius[0] = 0;
  for(int i = 1; i < 25; i++) {
    int additional_peneius; cin >> additional_peneius;
    peneius[i] = peneius[i-1] + additional_peneius;
  }
  
  int min_hrs = 49;
  
  int l = 0;
  int r = 48;
  
  vector<vector<int>> memo(25, vector<int>(25, -1));
  
  while(l < r) {
    int mid = (r+l)/2;
    bool feasible = false;
    for(int ai = 0; ai <= min(mid, 24); ai++) {
      int pi = mid - ai;
      if(pi > 24) continue; //pi > 24
      
      if(memo[ai][pi] == -1) memo[ai][pi] = can_do(alpheius[ai], peneius[pi], stables);
      
      if(memo[ai][pi]) {
        min_hrs = min(min_hrs, mid);
        feasible = true;
        break;
      }
    }
    
    if(feasible) r = mid;
    else l = mid+1;
  }
  
  if(min_hrs == 49) cout << "Impossible!" << endl;
  else cout << min_hrs << endl;
}

int main() {
  int t; cin >> t;
  while(t--) testcase();
}
