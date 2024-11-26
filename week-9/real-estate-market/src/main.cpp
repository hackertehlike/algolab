#include <iostream>
#include <vector>

#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;
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

void make_it_flow() {
  int N, M, S; std::cin >> N >> M >> S;
  
  std::vector<int> state_limits(S);
  for(int i = 0; i < S; i++) {
    std::cin >> state_limits[i];
  }
  
  std::vector<int> site_states(M);
  for(int i = 0; i < M; i++) {
    std::cin >> site_states[i];
  }
  
  std::vector<std::vector<int>> bids(N, std::vector<int>(M));
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      std::cin >> bids[i][j];
    }
  }
  
  graph G(N + M + S);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  // Make flow graph
  
  for(int i = 0; i < N; i++) {
    // Add source to buyer node
    adder.add_edge(v_source, i, 1, 0);
    
    for(int j = 0; j < M; j++) {
      // Add buyer node to site node
      adder.add_edge(i, N + j, 1, -1 * bids[i][j]);
    }
  }
  
  // Add site node to state node
  for(int i = 0; i < M; i++) {
    adder.add_edge(N + i, N + M + site_states[i] - 1, 1, 0);
  }
  
  // Add state node to sink
  for(int i = 0; i < S; i++) {
    adder.add_edge(N + M + i, v_sink, state_limits[i], 0);
  }
  
  int flow1 = boost::push_relabel_max_flow(G, v_source, v_sink);
    boost::cycle_canceling(G);
    int cost1 = boost::find_flow_cost(G);
    std::cout << flow1 << " " << -1 * cost1 << "\n"; // 12

}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  while(t--) {
    make_it_flow();
  }
  
  return 0;
}