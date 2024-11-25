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

int index(int i, int j, int n) {
  return i * n + j;
}

void testcase() {
  int n; std::cin >> n;
  
  std::vector<bool> is_hole(n*n, false);
  
  int sum_non_hole = n * n;
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      bool hole; std::cin >> hole;
      if(!hole) {
        is_hole[index(i, j, n)] = true;
        sum_non_hole--;
      }
    }
  }
  
  graph G(n * n);
  edge_adder adder(G);
  
  std::vector<std::pair<int, int>> possible_moves = {
      {-1, -2}, {1, -2}, {-1, 2}, {1, 2},
      {-2, -1}, {2, -1}, {-2, 1}, {2, 1}
  };
  
  const auto v_source = boost::add_vertex(G);
  const auto v_sink = boost::add_vertex(G);
  
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      
      
      int square_index = index(i, j, n);
       if(is_hole[square_index]) continue; 
      
      // white tiles
      if((i + j) % 2 == 0) {
        adder.add_edge(v_source, square_index, 1);
        
        for(auto &move : possible_moves) {
          int ni = i + move.first;
          int nj = j + move.second;
          int neighbor_index = index(ni, nj, n);
          
          if(ni >= 0 && ni < n && nj >= 0 && nj < n && !is_hole[neighbor_index] ) {
            adder.add_edge(square_index, neighbor_index, 1);
          }
        }
      } else {
        adder.add_edge(square_index, v_sink, 1);
      }
    }
  }
  
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  std::cout << sum_non_hole - flow << "\n";
  

  // //Retrieve the capacity map and reverse capacity map
  // const auto c_map = boost::get(boost::edge_capacity, G);
  // const auto rc_map = boost::get(boost::edge_residual_capacity, G);
  // // Iterate over all the edges to print the flow along them
  // auto edge_iters = boost::edges(G);
  // for (auto edge_it = edge_iters.first; edge_it != edge_iters.second; ++edge_it) {
  //   const edge_desc edge = *edge_it;
  //   const long flow_through_edge = c_map[edge] - rc_map[edge];
  //   std::cout << "edge from " << boost::source(edge, G) << " to " << boost::target(edge, G)
  //             << " runs " << flow_through_edge
  //             << " units of flow (negative for reverse direction). \n";
  // }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  while(t--) testcase();
  
}