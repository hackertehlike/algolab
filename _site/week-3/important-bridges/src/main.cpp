// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

typedef boost::property<boost::edge_weight_t, int> EdgeProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property, EdgeProperty> graph;

typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;  
typedef boost::graph_traits<graph>::edge_descriptor    edge_desc; 
typedef boost::graph_traits<graph>::edge_iterator edge_it;

struct lexicographic {
  bool operator() (const std::pair<int, int>& e1, const std::pair<int, int>& e2) {
    return (e1.first < e2.first || (e1.first == e2.first && e1.second < e2.second));
  }
};

void testcase(){
  
  int n, m; std::cin >> n >> m;
  
  graph G;
  edge_desc e;
  
  for(int i = 0; i < m; i++) {
    int ei1, ei2; std::cin >> ei1 >> ei2;
    
    e = boost::add_edge(ei1, ei2, G).first;
  }
  
  auto component = boost::get(boost::edge_weight, G);
  
  int ncc = boost::biconnected_components(G, component);
  
  std::vector<int> num_edges_in_comp(ncc, 0);
  
  edge_it ebeg, eend;
  
  for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg) {
    num_edges_in_comp[component[*ebeg]]++;
  }
  
  std::vector<std::pair<int, int>> important_bridges;
  
  for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg) {
    if (num_edges_in_comp[component[*ebeg]] == 1) {
      int u = boost::source(*ebeg, G), v = boost::target(*ebeg, G);
      if(u > v) std::swap(u, v);
      important_bridges.push_back(std::make_pair(u, v));
    }
  }
  std::sort(important_bridges.begin(), important_bridges.end(), lexicographic());

  std::cout << important_bridges.size() << std::endl;
  for(const auto &b : important_bridges) {
    std::cout << b.first << " " << b.second << std::endl;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase(); 
  }

  return 0;
}
