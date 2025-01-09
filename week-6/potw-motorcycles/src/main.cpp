#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

// using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;

void testcase(){
  int n; std::cin >> n;
  
  std::vector<std::tuple<int, R, K::FT>> tracks;
  
  for(int i = 0; i < n; i++) {
    long y0, x1, y1; std::cin >> y0 >> x1 >> y1;
    R ray = R(P(0, y0), P(x1, y1));
    K::FT slope = (K::FT(y1) - K::FT(y0)) / K::FT(x1);
    tracks.push_back({i, ray, slope});
  }
  
  std::sort(tracks.begin(), tracks.end(),
          [](const std::tuple<int, R, K::FT> &o1, std::tuple<int, R, K::FT> &o2)
          {
            return std::get<1>(o1).source().y() > std::get<1>(o2).source().y();
          });
  
  std::vector<std::tuple<int, R, K::FT>> survivors;
  std::tuple<int, R, K::FT> lowest_sloping_track = tracks[0];
  std::tuple<int, R, K::FT> curr_track;
  survivors.push_back(lowest_sloping_track);
  
  for(int i = 1; i < n; i++) {
    curr_track = tracks[i];
    
    if(std::get<2>(curr_track) <= std::get<2>(lowest_sloping_track)) {
      survivors.push_back(curr_track);
      lowest_sloping_track = curr_track;
      continue;
    }
    
    if(CGAL::abs(std::get<2>(curr_track)) <= CGAL::abs(std::get<2>(lowest_sloping_track))) {
      int first_remaining_survivor = survivors.size();
      while(first_remaining_survivor > 0
            && CGAL::do_intersect(std::get<1>(curr_track), std::get<1>(survivors[first_remaining_survivor-1]))
            && CGAL::abs(std::get<2>(curr_track)) <= CGAL::abs(std::get<2>(survivors[first_remaining_survivor-1]))
      ) first_remaining_survivor--;
      
      survivors.erase(survivors.begin()+first_remaining_survivor, survivors.end());
      
      if(first_remaining_survivor == 0 || std::get<2>(curr_track) <= std::get<2>(survivors[first_remaining_survivor-1])) {
        lowest_sloping_track = curr_track;
        survivors.push_back(curr_track);
      }
    }
  }
  
  std::sort(survivors.begin(), survivors.end(),
          [](const std::tuple<int, R, K::FT> &o1, std::tuple<int, R, K::FT> &o2)
          {
            return std::get<0>(o1) < std::get<0>(o2);
          });
  
  for(const auto &survivor : survivors) std::cout << std::get<0>(survivor) << " ";
  std::cout << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
}