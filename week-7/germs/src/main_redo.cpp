#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
using namespace std;

void testcase(int n) {
  long l, b, r, t; cin >> l >> b >> r >> t;
  
  vector<P> pts(n);
  for(int i = 0; i < n; i++) {
    cin >> pts[i];
  }
  
  Triangulation tri;
  tri.insert(pts.begin(), pts.end());
  
  vector<K::FT> time_of_death;
  
  for(auto v = tri.finite_vertices_begin(); v!= tri.finite_vertices_end(); v++) {
  // cout <<__LINE__<<endl;
    auto vx = v->point().x();
    auto vy = v->point().y();
    auto dl = CGAL::abs(vx - l);
    auto dr = CGAL::abs(vx - r);
    auto dt = CGAL::abs(vy - t); 
    auto db = CGAL::abs(vy - b);
    auto min_t = CGAL::sqrt(min(dl, min(dr, min(dt,db))) - 0.5);
    auto nearest_neighbor = CGAL::nearest_neighbor(tri, v);
    
    if(!tri.is_infinite(nearest_neighbor) && nearest_neighbor != nullptr) {

      auto dist = CGAL::sqrt(CGAL::squared_distance(v->point(), nearest_neighbor->point()));
      min_t = min(min_t, CGAL::sqrt((dist - 1) * 0.5));
    }
   
    time_of_death.push_back(min_t);
  }
  
  std::sort(time_of_death.begin(), time_of_death.end());
  
  cout << ceil(time_of_death[0]) << " "
       << ceil(time_of_death[ceil(n/2)]) << " "
       << ceil(time_of_death[n-1]) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while(n) {
    testcase(n);
    cin >> n;
  }
}