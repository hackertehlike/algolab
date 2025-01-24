/// REVIEW notes: pqueue lambda comparator -> check documentation
// CGAL functions:
/// face->neighbor(i) for i = 0..2
/// and face is a face handle
/// to find the edge, t.segment(f, i)
/// to find its length, t.segment(f, i).squared_length()
/// USE ALL_FACES_BEGIN(), FACES_BEGIN MIGHT BE MISSING INFINITE FACES
/// ALSO ONLY UPDATE INFO WHEN YOU PULL
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_2<K>   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K>    Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;

using namespace std;

void testcase(int n) {
  
  vector<P> pts(n);
  
  for(int i = 0; i < n; i++) {
    cin >> pts[i];
  }
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  auto cmp = [](pair<Tds::Face_handle, K::FT> &p1, pair<Tds::Face_handle, K::FT> &p2) {
    return p1.second < p2.second;
  };
  
  priority_queue<pair<Tds::Face_handle, K::FT>, vector<pair<Tds::Face_handle, K::FT>>,
                decltype(cmp)> pq(cmp);
                
  long inf = numeric_limits<long>::max();
  
  for(auto it = t.all_faces_begin(); it != t.all_faces_end(); it++) {
    if (!t.is_infinite(it)) {
      it->info() = -1;
      continue;
    }
    
    it->info() = inf;
    
    for(int i = 0; i < 3; i++) {
      auto n = it->neighbor(i);
      auto edge_len = t.segment(it, i).squared_length();
      pq.push({n, edge_len});
    }
  }
  
  while(!pq.empty()) {
    auto curr_face = pq.top().first;
    auto potential = pq.top().second;
    pq.pop();
    
    if(curr_face->info() != -1) continue;
    curr_face->info() = potential;
    
    for(int i = 0; i < 3; i++) {
      auto n = curr_face->neighbor(i);
      if(t.is_infinite(n) || n->info() != -1) continue;
      
      auto edge_len = t.segment(curr_face, i).squared_length();
      auto n_potential = min(potential, edge_len);
      pq.push({n, n_potential});
    }
  }
  
  int m; cin >> m;
  
  for(int i = 0; i < m; i++) {
    P pt; long d; cin >> pt >>d;
    
    if(CGAL::squared_distance(t.nearest_vertex(pt)->point(), pt) < d) {
      cout << "n" << " ";
      continue;
    }
    
    auto face = t.locate(pt);
    if(t.is_infinite(face) || face->info() >= 4*d) {
      cout << "y ";
    } else cout << "n ";
  }
  cout << endl;  
}

int main() {
  ios_base::sync_with_stdio(false);
  
  int n; cin >> n;
  while(n) {
    testcase(n);
    cin >> n;
  }
}