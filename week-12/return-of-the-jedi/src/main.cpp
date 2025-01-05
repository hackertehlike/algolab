#include <vector>
#include <iostream>
#include <limits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;


std::vector<std::vector<bool>> mst_adj_matrix;
std::vector<std::vector<int>> mst_adj_list;
std::vector<std::vector<int>> max_edge_between;
std::vector<bool> visited;
std::vector<std::vector<int>> weights;

void mst_worst_edges(int root, int curr, int max) {
  visited[curr] = true;
  max_edge_between[curr][root] = max_edge_between[root][curr] = max;
  
  for(auto &neighbor : mst_adj_list[curr]) {
    if(!visited[neighbor]) {
      mst_worst_edges(root, neighbor, std::max(max, weights[curr][neighbor]));
    }
  }
}

void testcase() {
  int n, tattooine; std::cin >> n >> tattooine;
  
  weighted_graph g(n);
  weights = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));
  
  for(int i = 0; i < n-1; i++) {
    for(int j = i+1; j < n; j++) {
      int weight; std::cin >> weight;
      boost::add_edge(i, j, weight, g);
      weights[i][j] = weights[j][i] = weight;
    }
  }
  
  std::vector<int> pred_map(n);
  boost::prim_minimum_spanning_tree(
    g, 
    boost::make_iterator_property_map(pred_map.begin(), boost::get(boost::vertex_index, g)),
    // Don't forget to offset tattoine index
    boost::root_vertex(tattooine-1)
  );
  
  // Things to save: MST adjacency matrix, MST adj list, max edge
  mst_adj_matrix = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
  mst_adj_list = std::vector<std::vector<int>>(n);
  max_edge_between = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));
  
  int mst_cost = 0;
  
  for(int i = 0; i < n; i++) {
    if(i != pred_map[i]) {
      mst_adj_matrix[i][pred_map[i]] = mst_adj_matrix[pred_map[i]][i] = true;
      mst_adj_list[i].push_back(pred_map[i]);
      mst_adj_list[pred_map[i]].push_back(i);
      mst_cost += weights[i][pred_map[i]];
    }
  }
  
  // NOT JUST FROM 0, ALL VERTICES MUST BE STARTING VERTICES AT SOME POINT!!! 
  for(int i = 0; i < n; i++) {
    visited = std::vector<bool>(std::vector<bool>(n, false));
    mst_worst_edges(i, i, 0);
  }
  
  int min_diff = std::numeric_limits<int>::max();
  
  for(int i = 0; i < n; i++) {
    for(int j = i+1; j < n; j++) {
      if(mst_adj_matrix[i][j]) continue;
      
      min_diff = std::min(min_diff, weights[i][j] - max_edge_between[i][j]);
    }
  }
  
  std::cout << mst_cost + min_diff << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
}