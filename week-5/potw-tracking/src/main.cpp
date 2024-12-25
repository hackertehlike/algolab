#include <vector>
#include <iostream>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, long> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void testcase() {
  
  int n, m, k, x, y; std::cin >> n >> m >> k >> x >> y;
  
  weighted_graph g((k+1) * n);

  for(int i = 0; i < m; i++) {
    int a, b, d; long c; std::cin >> a >> b >> c >> d;
    
    for(int j = 0; j < k+1; j++) {
      
      if(d == 0 || j == k) {
        // non-river road
        int u = j * n + a;
        int v = j * n + b;
        boost::add_edge(u, v, c, g);
      } else {
        // river road
        int u = j * n + a;
        int v = (j+1) * n + b;
        boost::add_edge(u, v, c, g);
        
        u = j * n + b;
        v = (j+1) * n + a;
        boost::add_edge(u, v, c, g);
      }
    }
  }
  
  int num_vertices = boost::num_vertices(g);
  std::vector<long> dist_map(num_vertices);

  boost::dijkstra_shortest_paths(g, x,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, g))));

  std::cout << dist_map[n * k + y] << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
  
  return 0;
}