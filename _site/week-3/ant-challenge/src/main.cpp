#include <vector>
#include <iostream>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

// struct EdgeProperty {
//   std::vector<int> times;
// };

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >  graph;
typedef boost::graph_traits<graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;
      
void testcase() {
  int n, e, s, a, b; std::cin >> n >> e >> s >> a >> b;
  
  std::vector<graph> private_graphs(n);
  std::vector<std::vector<std::vector<int>>> weights(n, std::vector<std::vector<int>>(n, std::vector<int>(s)));
  
  for(int i = 0; i < e; i++) {
    int t1, t2; std::cin >> t1 >> t2;
    
    for(int j = 0; j < s; j++) {
      int wi; std::cin >> wi;
      
      auto e = boost::add_edge(t1, t2, wi, private_graphs[j]);
      weights[t1][t2][j] = wi;
      weights[t2][t1][j] = wi;
    }
  }
  
  graph supergraph(n);
  
  // Compute private network for each species
  for(int i = 0; i < s; i++) {
    int hi; std::cin >> hi;
    std::vector<int> pred(n);
    
    prim_minimum_spanning_tree(
      private_graphs[i],
      boost::make_iterator_property_map(pred.begin(), boost::get(boost::vertex_index, private_graphs[i])),
      boost::root_vertex(hi)
    );
    
    for(int j = 0; j < n; j++) {
      // Add mst edges to the supergraph
      boost::add_edge(j, pred[j], weights[j][pred[j]][i], supergraph);
    }
  }
  
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(supergraph, a,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, supergraph))));


  std::cout << dist_map[b] << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
  
  return 0;
}