#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef CGAL::Triangulation_vertex_base_2<K>                   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K>    Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2                                             P;
typedef Delaunay::Face_handle                                  Face;

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int n; std::cin >> n;
  
  
  while(n != 0) {
    
    std::vector<P> pts(n);
    
    for(int i = 0; i < n; i++) {
      std::cin >> pts[i];
    }
    
    Delaunay t;
    t.insert(pts.begin(), pts.end());
    
    auto cmp = [](const std::pair<Face, K::FT>& f1, const std::pair<Face, K::FT>& f2) {
      return f1.second < f2.second;
    };

    std::priority_queue<std::pair<Face, K::FT>, std::vector<std::pair<Face, K::FT>>, decltype(cmp)> pq(cmp);
    
    for(auto f = t.all_faces_begin(); f != t.all_faces_end(); f++) {
      if(!t.is_infinite(f)) {
          f->info() = 0;
          continue;
      }

      f->info() = -1;
      for(int i = 0; i < 3; i++) {
        if(!t.is_infinite(f->neighbor(i))) pq.push({f->neighbor(i), t.segment(f, i).squared_length()});
      }
    }
    
    
    while(!pq.empty()) {
      
      auto face = pq.top().first;
      auto dist = pq.top().second;
      pq.pop();
      
      if(face->info() != 0) continue;
      face->info() = dist;

      for(int i = 0; i < 3; i++) 
        if(!t.is_infinite(face->neighbor(i)) && face->neighbor(i)->info() == 0) {
            auto edge_len = t.segment(face, i).squared_length();
            pq.push({face->neighbor(i), std::min(dist, edge_len)});
        }
    }
    
    for(auto f = t.all_faces_begin(); f != t.all_faces_end(); f++) std::cout << f->info() << std::endl;
    
    int m; std::cin >> m;
    
    for(int i = 0; i < m; i++) {
      P starting_loc; long long d; std::cin >> starting_loc >> d;
      
      auto nearest_vertex = t.nearest_vertex(starting_loc);
      
      if(CGAL::squared_distance(nearest_vertex->point(), starting_loc) < d) {
        std::cout << "n";
        continue;
      }
      
      Face face = t.locate(starting_loc);
      if(t.is_infinite(face) || face->info() >= 4*d) std::cout << "y";
      else std::cout << "n";
    }
    
    std::cout << std::endl;
    std::cin >> n;
  }
  
  return 0;
}

