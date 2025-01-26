/// REVIEW NOTES :
/// UF LINK BEFORE YOU UPDATE NEW SIZES... THE ROOT OF THE CURR NODE HAS TO BE UPDATED BEFOREHAND
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>   Triangulation;
typedef K::Point_2 P;
typedef std::pair<P,Index> IPoint;

using namespace std;

void testcase() {
  int n; long r; cin >> n >> r;
  r *= r;
  
  vector<IPoint> planets;
  for(int i = 0; i < n; i++) {
    P planet; cin >> planet;
    planets.emplace_back(planet, i);
  }
  
  Triangulation t;
  
  boost::disjoint_sets_with_storage<> uf(n);
  vector<int> comp_sizes(n, 1);
  int max_comp_size = 1;
  
  for(int i = n-1; i > 0; i--) {
    
    auto [pt, id] = planets[i];
    auto v = t.insert(pt);
    v->info() = id;
    auto neighbor = t.incident_vertices(v);

    if(i == n-1) continue;

    do {
      if(t.is_infinite(neighbor)) continue;
      
      Index c1 = uf.find_set(v->info());
      Index c2 = uf.find_set(neighbor->info());
      if(CGAL::squared_distance(neighbor->point(), v->point()) > r || c1 == c2) continue;
      uf.link(c1, c2);
      comp_sizes[uf.find_set(i)] = comp_sizes[c1] + comp_sizes[c2];
    } while(++neighbor != t.incident_vertices(v));
    
    if(max_comp_size > i) break;
    max_comp_size = max(max_comp_size, min(comp_sizes[uf.find_set(i)], i));
  }
  
  cout << max_comp_size << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) testcase();
}