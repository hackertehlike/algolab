#include<bits/stdc++.h>

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


using namespace std;

void testcase() {
  int N, M, S; cin >> N >> M >> S;
  
  graph G(N+M+S);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  const auto v_source = boost::add_vertex(G);
  const auto v_sink = boost::add_vertex(G);
  
  for(int i = 0; i < S; i++) {
    int ls; cin >> ls;
    adder.add_edge(N+M+i, v_sink, ls, 0);
  }
  
  for(int i = 0; i < M; i++) {
    int sj; cin >> sj;
    adder.add_edge(N+i, N+M+sj-1, 1, 0);
  }
  
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      int bij; cin >> bij;
      adder.add_edge(i, N+j, 1, 100-bij);
    }
      adder.add_edge(v_source, i, 1, 0);
  }
  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost2 = boost::find_flow_cost(G);
   int s_flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
      // std::cout << "edge from " << boost::source(*e, G) << " to " << boost::target(*e, G) 
      //     << " with capacity " << c_map[*e] << " and residual capacity " << rc_map[*e] << "\n";
      s_flow += c_map[*e] - rc_map[*e];     
  }
  cout << s_flow << " " << s_flow * 100 - cost2 << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) testcase();
}