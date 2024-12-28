#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <vector>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <algorithm>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      graph;
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;
        
int main() {
  
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    int n, m; std::cin >> n >> m;
    
    graph g(n);
    weight_map weights = boost::get(boost::edge_weight, g);
    
    for(int i = 0; i < m; i++) {
      
      int u, v, w; std::cin >> u >> v >> w;
      edge_desc e = boost::add_edge(u, v, g).first;
      weights[e] = w;
      
      // std::cout << "added edge " << u << " -- " << v << std::endl;
    }
    
    std::vector<edge_desc> mst;
    
    boost::kruskal_minimum_spanning_tree(g, std::back_inserter(mst));
    
    int total_weight = 0;
    for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
      int u = boost::source(*it, g);
      int v = boost::target(*it, g);
      int w = weights[*it];
      // std::cout << u << " -- " << v << " with weight " << w << std::endl;
      total_weight += w;
    }
    
    std::vector<int> distances(n, -1);
    distances[0] = 0;
    
     dijkstra_shortest_paths(g, 0, distance_map(boost::make_iterator_property_map(
                 distances.begin(), get(boost::vertex_index, g))));
    
    auto max_it = std::max_element(distances.begin(), distances.end());

    std::cout << total_weight << " " << *max_it << std::endl;
  }
  
  
  return 0;
}