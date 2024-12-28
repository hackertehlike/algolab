#include <iostream>
#include <iostream>

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
  
  graph G(n);
  edge_adder adder(G);
  
  for(int i = 0; i < m; i++) {
    int a, b, c; std::cin >> a >> b >> c;
    adder.add_edge(a, b, c);
  }
  
  long min_flow = std::numeric_limits<int>::max();
  
  for(int i = 1; i < n; i++) { 
    std::cout << i << std::endl;
    long flow_fwd = boost::push_relabel_max_flow(G, 0, i);
    std::cout << flow_fwd << std::endl;
    long flow_bwd = boost::push_relabel_max_flow(G, i, 0);
    std::cout << flow_bwd << std::endl;
    min_flow = std::min(std::min(min_flow, flow_fwd), flow_bwd);
    std::cout << min_flow << std::endl;
  }
  
  std::cout << min_flow << std::endl;
}

int main() {
  int t; std::cin >> t;
  
  while(t--) {
     make_it_flow();
  }
  
  return 0;
}