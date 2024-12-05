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
  const auto v_source = boost::add_vertex(G);
  const auto v_sink = boost::add_vertex(G);

  // std::vector<int> balances(n);
  int sum_positive_balances = 0;
  
  for(int i = 0; i < n; i++) {
    int bi; std::cin >> bi;
    
    if(bi > 0) {
      sum_positive_balances += bi;
      adder.add_edge(v_source, i, bi);
    } else {
      adder.add_edge(i, v_sink, -bi);
    }
  }
  
  for(int i = 0; i < m; i++) {
    int pi, pj, dij; std::cin >> pi >> pj >> dij;
    
    adder.add_edge(pi, pj, dij);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
 
  if(flow < sum_positive_balances) std::cout << "yes" << std::endl;
  else std::cout << "no" << std::endl;
  
}

int main() {
  int t; std::cin >> t;
  
  while(t--) {
    make_it_flow();
  }
}