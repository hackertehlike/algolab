#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

void testcase() {
  int n, e, s, a, b; cin >> n >> e >> s >> a >> b;
  
  vector<weighted_graph> graphs(s);
  
  for(int i = 0; i < s; i++) graphs[i] = weighted_graph(n);
  
  for(int i = 0; i < e; i++) {
    int t1, t2; cin >> t1 >> t2;
    for(int j = 0; j < s; j++) {
      int ws; cin >> ws;
      boost::add_edge(t1, t2, ws, graphs[j]);
      // cout << "adding edge " << t1 << "<->" << t2 << " with weight " << ws << " to graph " << j << endl;
    }
  }
  
  for(int i = 0; i < s; i++) {int h; cin >> h;}
  
  vector<vector<edge_desc>> mst_edges(s);

  for(int i = 0; i < s; i++) {
    vector<edge_desc> mst;    // vector to store MST edges (not a property map!)
    boost::kruskal_minimum_spanning_tree(graphs[i], std::back_inserter(mst));
    mst_edges[i] = mst;
  }
  
  weighted_graph supergraph(n);
  
  for(int i = 0; i < s; i++) {
    weight_map weights = boost::get(boost::edge_weight, graphs[i]);
    for(const auto &edge : mst_edges[i]) {
      boost::add_edge(boost::source(edge, graphs[i]), boost::target(edge, graphs[i]), weights[edge], supergraph);
    }
  }
  
  
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(supergraph, a,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, supergraph))));
  cout << dist_map[b] << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  while(t--) testcase();
}