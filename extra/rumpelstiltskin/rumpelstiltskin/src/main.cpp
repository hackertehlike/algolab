#include <bits/stdc++.h>
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

using namespace std;

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
  int n, pg, ph, eg, eh, fg, fh, sg, sh;
  cin >> n >> pg >> ph >> eg >> eh >> fg >> fh >> sg >> sh;
  
  graph G(2*n+pg+ph);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  const auto v_source = boost::add_vertex(G);
  const auto v_sink = boost::add_vertex(G);

  int max_pref = 1<<10;
  
  for(int i = 0; i < n; i++) {
    int pi; cin >> pi;
    adder.add_edge(i, n+i, 1, max_pref-pi);
    // cout << "added edge " << i << "->" << n+i << " with cost " << max_pref-pi << endl;
  }

  adder.add_edge(v_source, 2*n, sg, 0);
  // City west
  for(int i = 0; i < eg; i++) {
    int u, v, c; cin >> u >> v >> c;
    adder.add_edge(2*n+u, 2*n+v, c, 0);
  }
  
  
  adder.add_edge(2*n+pg, v_sink, sh, 0);
  // City east
  for(int i = 0; i < eh; i++) {
    int u, v, c; cin >> u >> v >> c;
    adder.add_edge(2*n+pg+v, 2*n+pg+u, c, 0);
  }
  // Transport west
  for(int i = 0; i < fg; i++) {
    int u, v, c; cin >> u >> v >> c;
    adder.add_edge(2*n+u, v, c, 0);
  }
  // Transport east
  for(int i = 0; i < fh; i++) {
    int u, v, c; cin >> u >> v >> c;
    adder.add_edge(n+v, 2*n+pg+u, c, 0);
  }
  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost2 = boost::find_flow_cost(G);
  long s_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
      // if(c_map[*e] - rc_map[*e] > 0) {std::cout << "edge from " << boost::source(*e, G) << " to " << boost::target(*e, G) 
      //       << " with capacity " << c_map[*e] << " and residual capacity " << rc_map[*e] << "\n";}
       
        s_flow += c_map[*e] - rc_map[*e];     
    }
 
  cout << s_flow << " " << s_flow * max_pref - cost2 << endl; 
}

int main() {
  int t; cin >> t;
  while(t--) testcase();
}