///2

#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <algorithm>

// IF YOU USE EXACT CONSTRUCTIONS, YOU WILL TLE
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

bool map_part_contains_point(std::vector<P> map_part, P point) {
  for(int i = 0; i < 3; i++) {
    // careful: if you just use !left_turn, you miss collinear points
    // which are technically also in the map part!
    if (CGAL::right_turn(map_part[2*i], map_part[2*i+1], point))
      return false;
  }
  return true;
}

void testcase() {
  
  int m, n; std::cin >> m >> n;
  
  std::vector<P> hiking_pts;
  
  for(int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    hiking_pts.push_back(P(x, y));
  }
  
  std::vector<std::vector<P>> map_parts;
  std::vector<std::vector<int>> map_coverage(n);
  
  
  for(int i = 0; i < n; i++) {
    std::vector<P> map_part;
    
    for(int j = 0; j < 6; j++) {
      int x, y; std::cin >> x >> y;
      
      map_part.push_back(P(x, y));
    }
    
    for(int j = 0; j < 6; j+=2) {
      if(!CGAL::left_turn(map_part[j], map_part[j+1], map_part[(j+2)%6])) {
        std::swap(map_part[j], map_part[j+1]);
      }
      // std::cout << map_part[j] << " " << map_part[j+1] << std::endl;
    }
    
    
    map_parts.push_back(map_part);
    
    P start = hiking_pts[0];
    int prev = map_part_contains_point(map_part, start);
    int curr = false;
    
    for(int j = 1; j < m; j++) {
      // check which legs are in this map part
      P end = hiking_pts[j];
      
      curr = map_part_contains_point(map_part, end);
      
      // both endpoints of the leg are in the map
      if(prev && curr) {
        map_coverage[i].push_back(j-1);
      }
      
      prev = curr;
      start = end;
    }
  }
  
  // for(auto &elem : map_coverage) {
  //   for(auto & leg : elem) {
  //     std::cout << leg << " ";
  //   }
  //   std::cout << std::endl;
  // }
 
  
  // now i need to do sliding window over map parts and keep track of num maps
  // containing each leg
  
  int l = 0;
  int r = 0;
  
  
  
  int num_parts_covered = 0;
  int min_maps = n;
  std::vector<int> num_maps_covering(m-1, 0);
  // loop over map parts
  
  while(r < n) {
    while(num_parts_covered < m-1 && r < n) {
      for(int leg : map_coverage[r]) {
        if(num_maps_covering[leg]++ == 0) {
          num_parts_covered++;
        }
      }
      r++;  // move r right only when more coverage is needed
    }

    while(num_parts_covered == m-1) {
      min_maps = std::min(min_maps, r - l);
      for(int leg : map_coverage[l]) {
        if(--num_maps_covering[leg] == 0) {
          num_parts_covered--;
        }
      }
      l++;  // move l right to try and find a smaller window
    }
  }
  
  std::cout << min_maps << std::endl;
}

int main() {
  
  std::ios_base::sync_with_stdio(0);
  int c; std::cin >> c;
  
  while(c--) testcase();
  
}