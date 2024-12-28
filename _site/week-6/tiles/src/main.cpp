#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>

#include <boost/graph/max_cardinality_matching.hpp>

using namespace boost;

typedef adjacency_list< vecS, vecS, undirectedS > Graph;

void testcase() {
  // std::cout << "new testcase" << std::endl;
  int w, h; std::cin >> w >> h;
  
  std::vector<std::vector<bool>> garden(h+1, std::vector<bool>(w+1, 0));
  
  int num_free_tiles = 0;
  
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      char character; std::cin >> character;
      
      if(character == '.') {
        garden[i][j] = true;
        num_free_tiles++;
      }
      // std::cout << garden[i][j] << " ";
    }
    // std::cout << std::endl;
  }
  
  if(num_free_tiles % 2 == 1) {
    std::cout << "no" << std::endl;
    return;
  }
  
  Graph g(w * h);
  
  int num_edges_added = 0;
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
        if(garden[i][j]) {
            if(i + 1 < h && garden[i+1][j]) {
                add_edge(i * w + j, (i+1) * w + j, g);
            }
            if(j + 1 < w && garden[i][j+1]) {
                add_edge(i * w + j, i * w + (j+1), g);
            }
        }
    }
}

  
  // std::cout << "Edges added: " << num_edges_added << std::endl;
  
  
  std::vector< graph_traits< Graph >::vertex_descriptor > mate(h * w);
  
  checked_edmonds_maximum_cardinality_matching(g, &mate[0]);  
  
  // std::cout << num_free_tiles << std::endl;
  //   std::cout << std::endl
  //             << "Found a matching of size " << matching_size(g, &mate[0])
  //             << std::endl;
              
    
  if(matching_size(g, &mate[0]) == num_free_tiles / 2) std::cout << "yes" << std::endl;
  else std::cout << "no" << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  
  while(t--) {
    testcase();
  }
}