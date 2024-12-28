// Algolab BGL Tutorial 2 (Max flow, by taubnert@ethz.ch)
// Flow example demonstrating how to use push_relabel_max_flow using a custom edge adder
// to manage the interior graph properties required for flow algorithms
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

// returns the 1D index given the 2d index (row, col)
int index(int row, int col, bool in, int cols) {
  return 2 * (cols * row + col) + in;
}

void make_it_flow() {
  
  int n, m, k, c; std::cin >> n >> m >> k >> c;
  
  
  graph G(2 * n * m);
  edge_adder adder(G);
  
  
  if(n == 0 || m == 0 || k == 0 || c == 0) {
    std::cout << "0" << std::endl;
    return;
  }
  
  
  // add intersections first
  
  for(int row = 0; row < m; row++) {
     for(int col = 0; col < n; col++) {
       
       // add inner edge with capacity c
       adder.add_edge(index(row, col, true, n), index(row, col, false, n), c);
       
      // Neighbors
      if (row > 0)
        adder.add_edge(index(row - 1, col, false, n), index(row, col, true, n), 1);
      if (row < m - 1)
        adder.add_edge(index(row + 1, col, false, n), index(row, col, true, n), 1);
      if (col > 0)
        adder.add_edge(index(row, col - 1, false, n), index(row, col, true, n), 1);
      if (col < n - 1)
        adder.add_edge(index(row, col + 1, false, n), index(row, col, true, n), 1);
     }
  }

  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  
  //for(int row = 0; row < m; row++) {
  //   for(int col = 0; col < n; col++) {
  //     if(row == 0 || row == m-1 || col == 0 || col == n-1) adder.add_edge(index(row, col, false, n), v_sink, 1);
  //   }
  //}
  
  for (int row = 0; row < m; ++row) {
    adder.add_edge(index(row, 0, false, n), v_sink, 1);
    adder.add_edge(index(row, n - 1, false, n), v_sink, 1);
  }
  for (int col = 0; col < n; ++col) {
    adder.add_edge(index(0, col, false, n), v_sink, 1);
    adder.add_edge(index(m - 1, col, false, n), v_sink, 1);
  }
  
  for(int i = 0; i < k; ++i) {
    int row, col; std::cin >> col >> row;
    int intersection_idx = index(row, col, true, n);
    // i don't think capacity matters here, it will be bottlenecked in the inner node anyway
    // ACTUALLY THAT'S WRONG, 1 FLOW FOR 1 KNIGHT, or for example in a corner, you'll count 2
    // knights instead of one
    adder.add_edge(v_source, intersection_idx, 1);
  }
  
   
  // Calculate flow from source to sink
  // The flow algorithm uses the interior properties (managed in the edge adder)
  // - edge_capacity, edge_reverse (read access),
  // - edge_residual_capacity (read and write access).
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  std::cout << flow << "\n";

}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    make_it_flow();
  }
  
  return 0;
}