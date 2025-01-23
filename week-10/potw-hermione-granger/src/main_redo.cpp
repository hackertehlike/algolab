#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2                                             P;

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void testcase() {
  int f, m, c, g, d, s; cin >> f >> m >> c >> g >> d >> s;
  
  // mi, ci, gi, best f of assigned DA
  vector<tuple<int, int, int, int>> slytherin_students;
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  
  for(int i = 0; i < s; i++) {
    P pt; int mi, ci, gi; cin >> pt >> mi >> ci >> gi;
    slytherin_students.push_back({mi, ci, gi, numeric_limits<int>::max()});
    points.emplace_back(pt, i);
  }
  
  Delaunay t;
  t.insert(points.begin(), points.end());
  
  for(int i = 0; i < d; i++) {
    P pt; int ff; cin >> pt >> ff;
    auto slytherin_nearest = t.nearest_vertex(pt)->info();
    get<3>(slytherin_students[slytherin_nearest]) = min(get<3>(slytherin_students[slytherin_nearest]), ff);
  }
  
  vector<tuple<int, int, int, int>> used_slytherins;
  
  for(int i = 0; i < s; i++) {
    auto [mi, ci, gi, ff] = slytherin_students[i];
    if (ff == numeric_limits<int>::max()) continue;
    used_slytherins.push_back({mi, ci, gi, ff});
  }
  
  Program lp (CGAL::LARGER, true, 0, true, 24);
  
  const int malfoy = 0;
  const int crabbe = 1;
  const int goyle = 2;
  const int felix_felicis = 3;
  
  for(int i = 0; i < used_slytherins.size(); i++) {
    auto [mi, ci, gi, ff] = used_slytherins[i];
    lp.set_a(i, malfoy, mi);
    lp.set_a(i, crabbe, ci);
    lp.set_a(i, goyle, gi);
    lp.set_a(i, felix_felicis, -ff);
  }
  
  lp.set_b(malfoy, m);
  lp.set_b(crabbe, c);
  lp.set_b(goyle, g);
  lp.set_b(felix_felicis, -f);
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  // output solution
  if(sol.is_infeasible()) cout << "H" << endl;
  else cout << "L" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  
  while(t--) {
    testcase();
  }
}