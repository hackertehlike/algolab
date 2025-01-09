#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;

// As edges are not explicitly represented in the triangulation, we extract them
// from the triangulation to be able to sort and process them. We store the
// indices of the two endpoints, first the smaller, second the larger, and third
// the squared length of the edge. The i-th entry, for i=0,... of a tuple t can
// be accessed using std::get<i>(t).
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}

int main(){
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    int n, h; long s; std::cin >> n >> s >> h;
    
     typedef std::pair<K::Point_2,Index> IPoint;
      std::vector<IPoint> points;
      points.reserve(n);
      for (Index i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points.emplace_back(K::Point_2(x, y), i);
      }
      
    Triangulation t;
    t.insert(points.begin(), points.end());
    
  // extract edges and sort by (squared) length
  // This step takes O(n log n) time (for the sorting).
  EdgeV edges;
  edges.reserve(3*n); // there can be no more in a planar graph
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    // ensure smaller index comes first
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });
  
  
  K::FT min = std::get<2>(edges[0]);

  int a_2 = std::count_if(edges.begin(), edges.end(), [min](Edge& e) {
    return std::get<2>(e) == min;
  });
  
  int a_3 = 0;
  K::FT min_r = std::numeric_limits<long>::max();
  for (auto it = t.finite_faces_begin(); it!=t.finite_faces_end(); it++){
    K::Point_2 center = t.dual(it);
    K::FT dist = CGAL::squared_distance(center, it->vertex(0)->point());
    if (dist < min_r){
      min_r = dist;
      a_3 = 1;
    }else if (dist == min_r){
      a_3++;
    }
  }
  
  std::cout << a_2 << " " << a_3 << " " << h << " " << h << std::endl;
  
  
  // int as = 0;
  // int curr_count = 1;
  // long prev_dist = -1;
  // for(const auto &edge : edges) {
  //   std::cout << "curr edge len: " << std::get<2>(edge) << std::endl;
  //   if(std::get<2>(edge) == prev_dist) curr_count++;
  //   else {
  //     as = std::max(curr_count, as);
  //     curr_count = 1;
  //     prev_dist = std::get<2>(edge);
  //   }
  // }
  
  }
}