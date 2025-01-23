// REVIEW NOTES:
// IF YOU HAVE TO DO DFS FROM EVERY NODE AND NEED TO PASS A VISITED
// DO NOT!!!!!! I REPEAT!!!!!!!! DO NOT FORGET TO REINITIALIZE IT 
// INSIDE THE LOOP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

void mst_worst_edge(int root, int curr, int max,
                    const vector<vector<int>> &weights,
                    const vector<vector<int>> &mst_adj_list,
                    const vector<vector<bool>> &mst_adj_mat,
                    vector<vector<int>> &dp,
                    vector<bool> &visited
                    ) {
  visited[curr] = true;
  dp[root][curr] = dp[curr][root] = max;
  
  for(const auto &neighbor : mst_adj_list[curr]) {
    if(!visited[neighbor]) {
      mst_worst_edge(root, neighbor, std::max(max, weights[curr][neighbor]),
                    weights, mst_adj_list, mst_adj_mat, dp, visited);
    }
  }
}

void testcase() {
  int n, i; cin >> n >> i;
  
  weighted_graph G(n);
  vector<vector<int>> weights(n, vector<int>(n));
  
  for(int i = 0; i < n; i++) {
    for(int j = i+1; j < n; j++) {
      int cost; cin >> cost;
      boost::add_edge(i, j, cost, G);
      weights[i][j] = weights[j][i] = cost;
    }
  }
  
  vector<edge_desc> mst;    // vector to store MST edges (not a property map!)
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  
  vector<vector<int>> mst_adj_list(n); 
  vector<vector<bool>> mst_adj_mat(n, vector<bool>(n)); 
  
  int mst_cost = 0;
  
  for(const auto &edge : mst) {
    auto src = boost::source(edge, G);
    auto target = boost::target(edge, G);
    
    mst_adj_list[src].push_back(target);
    mst_adj_list[target].push_back(src);
    mst_adj_mat[src][target] = mst_adj_mat[target][src] = true;
    mst_cost += weights[src][target];
  }
  
  vector<vector<int>> dp(n, vector<int>(n, -1));
  
  for(int i = 0; i < n; i++) {
    vector<bool> visited(n, false); //// INSIDE!!!!!!!!!!!
    mst_worst_edge(i, i, -1, weights, mst_adj_list, mst_adj_mat, dp, visited);
  }
  
  int min_diff = numeric_limits<int>::max();
  
  for(int i = 0; i < n; i++) {
    for(int j = i+1; j < n; j++) {
      if (mst_adj_mat[i][j]) continue;
      
      min_diff = min(min_diff, weights[i][j] - dp[i][j]);
    }
  }
  
  cout << min_diff + mst_cost << endl;
  
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  while(t--) {
    testcase();
  }
}