/// REVIEW NOTES : 
/// For the love of god use K::FT and cast every long into it BEFORE the operation.

#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;

void testcase() {
  int n; std::cin >> n;
  
  std::vector<std::tuple<int, R, K::FT>> bikers;
  bikers.reserve(n);
  
  for(int i = 0; i < n; i++) {
    long y0, x1, y1;
    std::cin >> y0 >> x1 >> y1;
    R ray(P(0, y0), P(x1, y1));
    // Use exact type CGAL::FT for the slope!!!!!!!!!!!!!!!!!!!
    K::FT slope = (K::FT(y1) - K::FT(y0)) / K::FT(x1);
    
    bikers.push_back({i, ray, slope});
  }
  
  std::sort(bikers.begin(), bikers.end(),
    [](auto &b1, auto &b2) {
      return std::get<1>(b1).source().y() > std::get<1>(b2).source().y();
    }
  );
  
  std::vector<std::tuple<int, R, K::FT>> survivors;
  K::FT lowest_slope = K::FT(std::numeric_limits<double>::max());
  
  for(int i = 0; i < n; i++) {
    auto &[id, track, slope] = bikers[i];
    
    if(slope <= lowest_slope) {
      survivors.push_back({id, track, slope});
      lowest_slope = slope;
      continue;
    }
    
    while(!survivors.empty()) {
      auto &[prev_id, prev_track, prev_slope] = survivors.back();
      
      if(!CGAL::do_intersect(track, prev_track)) {
        lowest_slope = slope;
        break;
      }
      if(CGAL::abs(slope) <= CGAL::abs(prev_slope)) {
        survivors.pop_back();
        lowest_slope = slope;
      } else {
        lowest_slope = prev_slope;
        break;
      }
    }
    
    if(slope <= lowest_slope || survivors.empty()) {
      survivors.push_back({id, track, slope});
    }
  }
  
  std::sort(survivors.begin(), survivors.end(),
    [](auto &s1, auto &s2){
      return std::get<0>(s1) < std::get<0>(s2);
    }
  );
  
  
  for(auto &s : survivors)  std::cout << std::get<0>(s) << " ";
  std::cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
  return 0;
}
