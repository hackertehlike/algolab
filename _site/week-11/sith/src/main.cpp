// Credit to https://github.com/chaehni/AlgoLab/blob/master/2019/week13/potw%20-%20revenge%20of%20the%20sith/src/algorithm.cpp

#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef K::Point_2 Point;

void recruit_rebels() {
  
  int n; long r_sq; std::cin >> n >> r_sq;
  r_sq *= r_sq;
  boost::disjoint_sets_with_storage<> uf(n);
  
  std::vector<Point> planets;
  
  for(int i = 0; i < n; i++) {
    long xi, yi; std::cin >> xi >> yi;
    planets.push_back(Point(xi, yi));
  }
  
  Triangulation t;
  
  std::vector<int> component_sizes(n, 1);
  
  int max_recruited = 0;
  // Work in reverse order of conquest
  for(int i = n-1; i >= 0; i--) {
    
    auto v = t.insert(planets[i]);
    v->info() = i;
    Triangulation::Vertex_circulator c = t.incident_vertices(v);

    if (c != 0) {
      do {
        if (t.is_infinite(c)) continue;
     
        int neighbour = c->info();
        K::FT distance_sq = CGAL::squared_distance(v->point(), c->point());
        if (distance_sq <= r_sq) {
          int root_1 = uf.find_set(i);
          int root_2 = uf.find_set(neighbour);
          if (root_1 != root_2) {
              uf.link(root_1, root_2);
              component_sizes[uf.find_set(i)] = component_sizes[root_1] + component_sizes[root_2];
          }
        }
      } while (++c != t.incident_vertices(v));
    }
    
    if(i < max_recruited) break;
    max_recruited = std::max(max_recruited, std::min(i, component_sizes[uf.find_set(i)]));
  }
  
  std::cout << max_recruited << std::endl;
}

int main() {
  int t; std::cin >> t;
  
  while(t--) {
    recruit_rebels();
  }
}