#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>
#include <CGAL/squared_distance_2.h>
#include <random>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

using namespace std;

double floor_to_double(const K::FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; 
    std::cin >> n;
    
    while (n > 0) {
        long x, y, a, b;
        cin >> x >> y >> a >> b;
        std::vector<S> walls;
        
        R phileas_ray = R(P(x, y), P(a, b));
        
        // Read the segments
        for (int i = 0; i < n; i++) {
            long r, s, t, u;
            cin >> r >> s >> t >> u;
            
            S segment = S(P(r, s), P(t, u));
            walls.push_back(segment);
        }
        
        // important for time constraint for some reason
        std::random_shuffle(walls.begin(), walls.end());
        
        bool hitFound = false;
        S phileas_seg;  // Initialize with a default value

        
        for (const auto &wall : walls) {
          // cout << wall.source() << " to " << wall.target() << endl;
            if(!hitFound) {
              // Check if ray intersects with wall
              if(CGAL::do_intersect(wall, phileas_ray)) {
                auto o = CGAL::intersection(wall, phileas_ray);
                if (const P* op = boost::get<P>(&*o)) {
                  phileas_seg = S(phileas_ray.source(), *op);
                  hitFound = true;
                  // cout << "Hit found with point " << *op << endl;
                  // cout << "New seg: " << phileas_ray.source() << " to " << *op << endl;
                } else if (const S* os = boost::get<S>(&*o)) {
                  P p1 = os->source();
                  P p2 = os->target();
                  if (CGAL::squared_distance(phileas_ray.source(), p1) > CGAL::squared_distance(phileas_ray.source(), p2)) {
        std::swap(p1, p2);
    }
                  phileas_seg = S(phileas_ray.source(), p1);
                  hitFound = true;
                  // cout << "Hit found with point " << p1 << endl;
                  // cout << "New seg: " << phileas_ray.source() << " to " << p1 << endl;
                } //else cout << "huh?" << endl;
              }
            } else {
              if(CGAL::do_intersect(wall, phileas_seg)) {
                auto o = CGAL::intersection(wall, phileas_seg);
                if (const P* op = boost::get<P>(&*o)) {
                  phileas_seg = S(phileas_ray.source(), *op);
                  hitFound = true;
                  // cout << "New seg: " << phileas_ray.source() << " to " << *op << endl;
                } else if (const S* os = boost::get<S>(&*o)) {
                  P p1 = os->source();
                  P p2 = os->target();
                  
                  //don't use CGAL::has_smaller_distance_to_point, didn't work for some reason
                  if (CGAL::squared_distance(phileas_ray.source(), p1) > CGAL::squared_distance(phileas_ray.source(), p2)) {
        std::swap(p1, p2);
    }
                  phileas_seg = S(phileas_ray.source(), p1);
                  // cout << "New seg: " << phileas_ray.source() << " to " << p1 << endl;
                }
              }
            }
        }
        
        // IMPORTANT FOR LARGE NUMBERS!!!
        cout << fixed << setprecision(0);
        if(hitFound) cout << floor_to_double(phileas_seg.target().x()) << " " << floor_to_double(phileas_seg.target().y()) << endl;
        else cout << "no" << endl;
        // Read the next case
        cin >> n;
    }

    return 0;
}
