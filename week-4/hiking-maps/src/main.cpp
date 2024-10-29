#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;

void testcase() {
  
  int m, n; std::cin >> m >> n;
  
  std::vector<P> hiking_pts;
  
  for(int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    hiking_pts.push_back(P(x, y));
  }
  
  std::vector<S> hiking_paths;
  for (int i = 0; i < m - 1; ++i) {
    hiking_paths.push_back(S(hiking_pts[i], hiking_pts[i + 1]));  // Create a segment between p_i and p_(i+1)
  }

  std::vector<std::vector<S>> map_parts(n);
  
  for(int i = 0; i < n; i++) {
    int q0, q1, q2, q3, q4, q5;
    std::cin >> q0 >> q1 >> q2 >> q3 >> q4 >> q5;

    // Create the triangle's vertices
    P p0(q0, q1), p1(q2, q3), p2(q4, q5);

    // Ensure counter-clockwise orientation
    // IMPORTANT!!!
    if (!CGAL::left_turn(p0, p1, p2)) {
        // Points are in clockwise order, so swap p1 and p2 to make them counterclockwise
        std::swap(p1, p2);
    }

    // Now that the points are in counterclockwise order, construct the segments
    map_parts[i].push_back(S(p0, p1));  // First segment: p0 -> p1
    map_parts[i].push_back(S(p1, p2));  // Second segment: p1 -> p2
    map_parts[i].push_back(S(p2, p0));  // Third segment: p2 -> p0
  }

  std::vector<std::vector<bool>> coverage(m - 1, std::vector<bool>(n, false));
  
  for(int j = 0; j < n; j++) {
    for(int i = 0; i < m - 1; i++) {
        S s0 =  map_parts[j][0];
        S s1 =  map_parts[j][1];
        S s2 =  map_parts[j][2];

        bool cond1 = CGAL::left_turn(s0.source(), s0.target(), hiking_paths[i].source());
        bool cond2 = CGAL::left_turn(s0.source(), s0.target(), hiking_paths[i].target());
        bool cond3 = CGAL::left_turn(s1.source(), s1.target(), hiking_paths[i].source());
        bool cond4 = CGAL::left_turn(s1.source(), s1.target(), hiking_paths[i].target());
        bool cond5 = CGAL::left_turn(s2.source(), s2.target(), hiking_paths[i].source());
        bool cond6 = CGAL::left_turn(s2.source(), s2.target(), hiking_paths[i].target());

        if(cond1 && cond2 && cond3 && cond4 && cond5 && cond6) {
            coverage[i][j] = true;
        } else {
            coverage[i][j] = false;
        }
        
        std::cout << "Segment " << i << " with Map Part " << j << ": " << std::endl;
        std::cout << "Segment " << i << " : " <<  hiking_paths[i].source() << " " << hiking_paths[i].target() << std::endl;
        std::cout << "Map part " << j << " : " << map_parts[j][0] << " " << map_parts[j][1] << " " << map_parts[j][2] << std::endl;
        std::cout << "Conditions: " << cond1 << cond2 << cond3 << cond4 << cond5 << cond6;
        std::cout << " Coverage: " << coverage[i][j] << std::endl;
    }
}

  
  
}

int main() {
  
  std::ios_base::sync_with_stdio(0);
  int c; std::cin >> c;
  
  while(c--) testcase();
  
}