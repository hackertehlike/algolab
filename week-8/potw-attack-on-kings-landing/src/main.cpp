///3
#include <vector>
#include <iostream>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>


// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>
            
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;


void testcase() {
  
  // std::cout <<  __LINE__ << std::endl;
  // // std::cout <<  "new testcase: " << std::endl;
  int n, m, b, p, d; std::cin >> n >> m >> b >> p >> d;
  // std::cout 
  std::vector<int> barracks;
  weighted_graph g(n);
  
  for(int i = 0; i < b; i++) {
    int ai; std::cin >> ai;
    barracks.push_back(ai);
  }
  
  std::vector<bool> is_plaza(n, false);
  for(int i = 0; i < p; i++) {
    int pi; std::cin >> pi;
    is_plaza[pi] = true;
  }
  
  std::vector<std::pair<int, int>> edges;
  for(int i = 0; i < m; i++) {
    int x, y, l; std::cin >> x >> y >> l;
    boost::add_edge(x, y, l, g);
    edges.push_back(std::make_pair(x, y));
  }
  // std::cout <<  __LINE__ << std::endl;
  std::vector<bool> reachable(n, false);
  for(const auto &b : barracks) {
    
    std::vector<long> dist_map(n);
    
    boost::dijkstra_shortest_paths(g, b,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, g))));
    // std::cout <<  __LINE__ << std::endl;
    for(int i = 0; i < n; i++) {
      //// std::cout <<  ___LINE__ << std::endl;
      bool reachable_from_b = dist_map[i] <= d ? 1 : 0;
      if (reachable_from_b) reachable[i] = true;
    }
  }
  
  graph matching_graph;
  
  // std::cout <<  __LINE__ << std::endl;
  for(const auto &edge : edges) {
    // // std::cout <<  i << " is reachable: " << reachable[i] << std::endl;
    auto [u, v] = edge;
    if(reachable[u] && reachable[v]) boost::add_edge(u, v, matching_graph);
  }
  
  int nv = boost::num_vertices(matching_graph);
  std::vector<vertex_desc> mate_map(nv);  // exterior property map
  boost::edmonds_maximum_cardinality_matching(matching_graph,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, matching_graph)));
    // std::cout <<  __LINE__ << std::endl;
  int matching_size = boost::matching_size(matching_graph,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, matching_graph)));
  // std::cout <<  __LINE__ << std::endl;
  std::cout <<  matching_size << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
  
  return 0;
}