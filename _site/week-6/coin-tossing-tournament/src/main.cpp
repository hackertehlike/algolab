#include <iostream>
#include <vector>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void make_it_flow() {
  
  int n, m; std::cin >> n >> m;
  
  // n player nodes, m match nodes, source and sink
  graph G;
  edge_adder adder(G);
  
  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  
  std::vector<vertex_desc> match_nodes(m);
  std::vector<vertex_desc> player_nodes(n);
  

  for (int i = 0; i < m; ++i) match_nodes[i] = boost::add_vertex(G);
  for (int i = 0; i < n; ++i) player_nodes[i] = boost::add_vertex(G);


  for(int i = 0; i < m; i++) {
    int a, b, c; std::cin >> a >> b >> c;
    // add the edges from source to match node
    adder.add_edge(v_source, match_nodes[i], 1);
    // std::cout << "added edge from " << v_source << " to " << match_nodes[i] << std::endl;
    // add the edges from match node to player nodes
    switch(c) {
      // we don't know who won, so we add edges to both player nodes
      case 0:
        adder.add_edge(match_nodes[i], player_nodes[a], 1);
        adder.add_edge(match_nodes[i], player_nodes[b], 1);
            // std::cout << "added edge from " << match_nodes[i] << " to " << player_nodes[a] << std::endl;
            // std::cout << "added edge from " << match_nodes[i] << " to " << player_nodes[b] << std::endl;
        break;
      case 1:
        adder.add_edge(match_nodes[i], player_nodes[a], 1);
        break;
      case 2:
        adder.add_edge(match_nodes[i], player_nodes[b], 1);
    }
  }
  
  
  int tot_scores = 0;
  for(int i = 0; i < n; i++) {
    int si; std::cin >> si;
    adder.add_edge(player_nodes[i], v_sink, si);
    tot_scores += si;
      // std::cout << "added edge from " << player_nodes[i] << " to " << v_sink << std::endl;

  }
  
  // Calculate flow from source to sink
  // The flow algorithm uses the interior properties (managed in the edge adder)
  // - edge_capacity, edge_reverse (read access),
  // - edge_residual_capacity (read and write access).
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  
  // Retrieve the capacity map and reverse capacity map
  const auto c_map = boost::get(boost::edge_capacity, G);
  const auto rc_map = boost::get(boost::edge_residual_capacity, G);

  // Iterate over all the edges to print the flow along them
  auto edge_iters = boost::edges(G);
  for (auto edge_it = edge_iters.first; edge_it != edge_iters.second; ++edge_it) {
    const edge_desc edge = *edge_it;
    const long flow_through_edge = c_map[edge] - rc_map[edge];
    // std::cout << "edge from " << boost::source(edge, G) << " to " << boost::target(edge, G)
    //           << " runs " << flow_through_edge
    //           << " units of flow (negative for reverse direction). \n";
  }
  
  if (flow == m && flow == tot_scores) std::cout << "yes" << std::endl;
  else std::cout << "no" << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    make_it_flow();
  }
  
  return 0;
}