#include <bits/stdc++.h>

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

void testcase(){
  int e, w, m, d, p, l; std::cin >> e >> w >> m >> d >> p >> l;
  
  graph G(2 * (e+w));
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  const auto v_source_l = boost::add_vertex(G);
  const auto  v_source_rest = boost::add_vertex(G);
  const auto  v_sink_l = boost::add_vertex(G);
  const auto  v_sink_rest = boost::add_vertex(G);
  const auto  v_target = boost::add_vertex(G);
  const auto  v_source = boost::add_vertex(G);
  
  adder.add_edge(v_source, v_source_l, e*l, 0);
  adder.add_edge(v_source, v_source_rest, p-e*l, 0);
  adder.add_edge(v_sink_l, v_target, w*l, 0);
  adder.add_edge(v_sink_rest, v_target, p-w*l, 0);
  
  int max = std::numeric_limits<int>::max();
  
  for(int i = 0; i < e; i++) {
    adder.add_edge(v_source_l, i, l, 0);
    adder.add_edge(v_source_rest, e+w+i, max, 0);
    adder.add_edge(v_source_rest, i, max, 0);
  }
  
  for(int i = 0; i < w; i++) {
    adder.add_edge(e+i, v_sink_l, l, 0);
    adder.add_edge(e+i, v_sink_rest, max, 0);
    adder.add_edge(2*e+w+i, v_sink_rest, max, 0);
  }
  
  for(int i = 0; i < m; i++) {
    int u, v, r; std::cin >> u >> v >> r;
    adder.add_edge(u, e+v, 1, r);
  }
  
  for(int i = 0; i < d; i++) {
    int u, v, r; std::cin >> u >> v >> r;
    adder.add_edge(e+w+u, 2*e+w+v, 1, r);
  }
  
  
  int min_needed = std::max(e * l, w * l);
    if(min_needed > p) {
        std::cout << "No schedule!" << std::endl;
        return;
  }
  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
  int cost2 = boost::find_flow_cost(G);
  // std::cout << "-----------------------" << std::endl;
  // std::cout << "Minimum Cost Maximum Flow with successive_shortest_path_nonnegative_weights()" << "\n";
  // std::cout << "cost " << cost2 << "\n"; // 12
  // Iterate over all edges leaving the source to sum up the flow values.
  int s_flow = 0;
  out_edge_it ei, eend;
  for(boost::tie(ei, eend) = boost::out_edges(boost::vertex(v_source,G), G); ei != eend; ++ei) {
      // std::cout << "edge from " << boost::source(*ei, G) << " to " << boost::target(*ei, G) 
      //     << " with capacity " << c_map[*ei] << " and residual capacity " << rc_map[*ei] << "\n";
      s_flow += c_map[*ei] - rc_map[*ei];     
  }
  
  if(s_flow == p) std::cout << cost2 << std::endl;
  else std::cout << "No schedule!" << std::endl;

  return;
}


int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
}