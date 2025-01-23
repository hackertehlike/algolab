#include <bits/stdc++.h>

#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;
typedef boost::graph_traits<graph>::edge_descriptor    edge_desc;// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).  
typedef boost::graph_traits<graph>::edge_iterator    edge_it;    // to iterate over all edges

using namespace std;

void testcase() {
  int n, m; cin >> n >> m;
  graph g(n);
  
  for(int i = 0; i < m; i++) {
    int e1, e2; cin >> e1 >> e2;
    boost::add_edge(e1, e2, g);
  }
  
  auto components = boost::get(boost::edge_weight, g);
  auto biconnected_components = boost::biconnected_components(g, components);
  
  vector<vector<edge_desc>> edges_in_comp(biconnected_components);
  edge_it e_beg, e_end;
  for (boost::tie(e_beg, e_end) = boost::edges(g); e_beg != e_end; ++e_beg) {
    auto comp = components[*e_beg];
    edges_in_comp[comp].push_back(*e_beg);
  }
  
  vector<tuple<int, int>> bridges;
  
  for(const auto &component : edges_in_comp) {
    if(component.size() == 1) {
      auto u = boost::source(component[0], g);
      auto v = boost::target(component[0], g);
      if(u > v) swap(u, v);
      bridges.push_back({u, v});
    }
  }
  
  auto lex = [](tuple<int, int> &t1, tuple<int,int> &t2) {
    return ((get<0>(t1) < get<0>(t2)) || ((get<0>(t1) == get<0>(t2)) && (get<1>(t1) < get<1>(t2))));
  };
  
  sort(bridges.begin(), bridges.end(), lex);
  cout << bridges.size() << endl;
  for(const auto &bridge : bridges) cout << get<0>(bridge) << " " << get<1>(bridge) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  while(t--) testcase();
}