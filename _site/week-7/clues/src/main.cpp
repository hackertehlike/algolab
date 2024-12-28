#include <iostream>
#include <vector>
// CGAL includes
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/bipartite.hpp>

// CGAL typedefs
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

// This adds an info field to vertex handles
// I thought this was a headache at first but actually it is kind of nice to have
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>  Triangulation;

typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Vertex_circulator  Vertex_circ;
typedef K::Point_2 Point;


// BGL typedefs
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS    // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
    >          graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;    // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).  
typedef boost::graph_traits<graph>::edge_iterator    edge_it;    // to iterate over all edges

void testcase() {
  int n, m, r; std::cin >> n >> m >> r;
  
  double sq_r = r * r;
  
  std::vector<std::pair<Point, int>> stations;
  
  // Read station points and assign indices
  for (int i = 0; i < n; i++) {
      int xi, yi;
      std::cin >> xi >> yi;
      stations.emplace_back(Point(xi, yi), i); // Store point with an index
  }
  
  // // Insert points with indices into the triangulation
  Triangulation t;
  t.insert(stations.begin(), stations.end());

  
  graph g;
    // Iterate over all vertices
    for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
      
        Vertex_circ neighbor = t.incident_vertices(v);
      // std::cout << v->info() << std::endl;
          
      do {
          if (!t.is_infinite(neighbor)) {
              double dist = CGAL::squared_distance(neighbor->point(), v->point());
              if (dist <= sq_r) {
                  boost::add_edge(neighbor->info(), v->info(), g);
              }
          }
      } while (++neighbor != t.incident_vertices(v));

    }
    
    std::vector<int> component_map(n);  // We MUST use such a vector as an Exterior Property Map: Vertex -> Component
    boost::connected_components(g, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, g))); 
  
    bool not_bipartite = false;
  
    if(!boost::is_bipartite(g)) not_bipartite = true;
  
    for (int i = 0; i < m; i++) {
      int ai_x, ai_y, bi_x, bi_y; std::cin >>  ai_x >> ai_y >> bi_x >> bi_y;
      Point clue_1 = Point(ai_x, ai_y);
      Point clue_2 = Point(bi_x, bi_y);
      
      // This is buggy, there could be other stations in range.
      // nvm
      auto station_a = t.nearest_vertex(clue_1);
      auto station_b = t.nearest_vertex(clue_2);
      
      // If the graph is not bipartite, there are interferences
      if (not_bipartite) std::cout << "n";
      else if (CGAL::squared_distance(clue_1, clue_2) <= sq_r) {
        std::cout << "y";
      } else if(CGAL::squared_distance(station_a->point(), clue_1) <= sq_r
        && CGAL::squared_distance(station_b->point(), clue_2) <= sq_r
        && component_map[station_a->info()] == component_map[station_b->info()]) {
        std::cout << "y";
      } else {
        std::cout << "n";
      }
      
    }
    
    std::cout << std::endl;
}


int main() {
  
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
  
  return 0;  
}