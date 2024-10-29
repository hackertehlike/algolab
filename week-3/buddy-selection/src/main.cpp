#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/adjacency_list.hpp>


typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS > graph;

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    
    int n, c, f; std::cin >> n >> c >> f;
    std::vector<std::set<std::string>> interests(n);
    
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < c; j++) {
        std::string interest; std::cin >> interest;
        interests[i].insert(interest);
      }
    }
    
    graph g(n);
    
    for(int i = 0; i < n; i++) {
      for(int j = i+1; j < n; j++) {
        
        
        std::vector<std::string> intersection;
 
        std::set_intersection(interests[i].begin(), interests[i].end(),
                              interests[j].begin(), interests[j].end(),
                              std::back_inserter(intersection));
                              
        int num_common = intersection.size();
        
        if (num_common > f) boost::add_edge(i, j, g);
      }
    }
    
    std::vector<boost::graph_traits<graph>::vertex_descriptor>mate(n);
    edmonds_maximum_cardinality_matching(g, &mate[0]);
    
    
    bool optimal = false;
    
    for(auto matched_mate : mate) {
      if (matched_mate == boost::graph_traits<graph>::null_vertex()) {
        std::cout << "optimal" << std::endl;
        optimal = true;
        break;
      }
    }
    
    if(!optimal) std::cout << "not optimal" << std::endl;
    
  }
  
}