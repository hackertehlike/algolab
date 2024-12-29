#include <vector>
#include <iostream>
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

#include <boost/graph/graphviz.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

void testcase() {
  int n, m; std::cin >> n >> m;
  
  graph G(n);
  edge_adder adder(G);
  
  const auto v_source = boost::add_vertex(G);
  const auto v_sink = boost::add_vertex(G);
  
  int max_cost = 1 << 7;
  
  std::vector<int> capacities(n-1);
  
  for(int i = 0; i < n-1; i++) {
    int ci; std::cin >> ci;
    capacities[i] = ci;
    
    adder.add_edge(i, i+1, ci, max_cost);
    adder.add_edge(v_source, i, ci, 0);
    adder.add_edge(i+1, v_sink, ci, 0);
  }
  
  std::vector<std::vector<std::vector<int>>> item_edges(n-1, std::vector<std::vector<int>>(n));
  
  for(int i = 0; i < m; i++) {
    int a, b, d; std::cin >> a >> b >> d;
    item_edges[a][b].push_back(d);
  }
  
  for(int i = 0; i < n-1; i++) {
    for(int j = i+1; j < n; j++) {
      if(item_edges[i][j].size() == 0) continue;
      std::sort(item_edges[i][j].begin(), item_edges[i][j].end(), std::greater<int>());
      int num_added = 0;
      
      for(int k = 0; k < (int)item_edges[i][j].size() && k < capacities[i]; k++) {
          adder.add_edge(i, j, 1, max_cost*(j-i) - item_edges[i][j][k]); num_added++;
      }
    
      // for(const int d : item_edges[i][j]) {
      //   adder.add_edge(i, j, 1, max_cost * (j-i) - d);
      //   if(++num_added >= capacities[i]) break;
      // }
    }
  }
  
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
    
    int cost = boost::find_flow_cost(G);
    
    int flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
        flow += c_map[*e] - rc_map[*e];     
    }
    
    std::cout <<  flow * max_cost - cost << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
}