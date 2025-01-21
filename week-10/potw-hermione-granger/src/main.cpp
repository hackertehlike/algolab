///3
#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

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

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
struct VertexInfo {
  int mi;
  int ci;
  int gi;
  int best_f;
  
  VertexInfo(int mi = 0, int ci = 0, int gi = 0, int best_f = -1) : mi(mi), ci(ci), gi(gi), best_f(best_f) {};
};
typedef CGAL::Triangulation_vertex_base_with_info_2<VertexInfo,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2                                             P;

void testcase() {
  int f, m, c, g, d, s; std::cin >> f >> m >> c >> g >> d >> s;
  
  std::vector<std::pair<P, VertexInfo>> slytherin_students;
  
  for(int i = 0; i < s; i++) {
    P pt; int mi, ci, gi; std::cin >> pt >> mi >> ci >> gi;
    slytherin_students.emplace_back(pt, VertexInfo(mi, ci, gi, std::numeric_limits<int>::max()));
  }
  
  Delaunay t;
  t.insert(slytherin_students.begin(), slytherin_students.end());
  
  for(int i = 0; i < d; i++) {
    P pt; int fj; std::cin >> pt >> fj;
    auto closest_slytherin = t.nearest_vertex(pt);
    closest_slytherin->info().best_f = std::min(closest_slytherin->info().best_f, fj);
  }
  
  std::vector<std::tuple<int, int, int, int>> used_slytherins;
  for(auto it = t.finite_vertices_begin(); it != t.finite_vertices_end(); it++) {
    auto info = it->info();
    if(info.best_f == std::numeric_limits<int>::max()) continue;
    used_slytherins.push_back({info.mi, info.ci, info.gi, info.best_f});
  }
  
  Program lp(CGAL::LARGER, true, 0, true, 24); 
  
  for(int i = 0; i < used_slytherins.size(); i++) {
    lp.set_a(i, 0, std::get<0>(used_slytherins[i]));
    lp.set_a(i, 1, std::get<1>(used_slytherins[i]));
    lp.set_a(i, 2, std::get<2>(used_slytherins[i]));
    lp.set_a(i, 3, -std::get<3>(used_slytherins[i]));
  }
  
  lp.set_b(0, m);
  lp.set_b(1, c);
  lp.set_b(2, g);
  lp.set_b(3, -f);
  
  // solve the program, using ET as the exact type
  Solution sol = CGAL::solve_linear_program(lp, ET());
  assert(sol.solves_linear_program(lp));
  
  // output solution
  if(sol.is_infeasible()) std::cout << "H" << std::endl;
  else std::cout << "L" << std::endl;
}

int main() {
  int t; std::cin >> t;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  
  while(t--) {
    testcase();
  }
}