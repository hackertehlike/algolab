#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Define graph type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property<boost::edge_weight_t, long> > > > > graph;

typedef boost::graph_traits<graph>::edge_descriptor edge_desc;

// Custom edge adder class for convenience
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;
    w_map[rev_e] = -cost;
  }
};

struct Booking {
  int si, ti, di, ai, pi;
  Booking(int s, int t, int d, int a, int p) : si(s), ti(t), di(d), ai(a), pi(p) {}
};

void testcase() {
  int N, S;
  std::cin >> N >> S;
  std::vector<int> initial_num_cars(S);
  int num_cars = 0;
  
  for (int i = 0; i < S; ++i) {
    int li;
    std::cin >> li;
    initial_num_cars[i] = li;
    num_cars += li;
  }

  std::vector<Booking> bookings;
  std::vector<int> times;
  std::unordered_set<int> timeset;
  timeset.insert(0);
  times.push_back(0);

  for (int i = 0; i < N; ++i) {
    int s, t, d, a, p;
    std::cin >> s >> t >> d >> a >> p;
    bookings.emplace_back(--s, --t, d, a, p);

    if (timeset.insert(a).second) times.push_back(a);
    if (timeset.insert(d).second) times.push_back(d);
  }

  std::sort(times.begin(), times.end());
  int last_t = times.back();
  
  graph G;
  edge_adder adder(G);
  
  const auto v_source = boost::add_vertex(G);
  const auto v_sink = boost::add_vertex(G);
  
  std::map<std::pair<int, int>, int> vertex_handle;
  for (int i = 0; i < S; ++i) {
    for (int timestep : times) {
       auto id = boost::add_vertex(G);
       vertex_handle[{i, timestep}] = id;
    }
  }
  
  for (int i = 0; i < S; ++i) {
    adder.add_edge(v_source, vertex_handle[{i, 0}], initial_num_cars[i], 0);
    adder.add_edge(vertex_handle[{i, last_t}], v_sink, num_cars, 0);
  }

  for (const Booking &b : bookings) {
    adder.add_edge(vertex_handle[{b.si, b.di}], vertex_handle[{b.ti, b.ai}], 1, 100 * (b.ai - b.di) - b.pi);
  }

  for (int i = 0; i < S; ++i) {
    for (size_t j = 0; j < times.size() - 1; ++j) {
      adder.add_edge(vertex_handle[{i, times[j]}], vertex_handle[{i, times[j+1]}], num_cars, 100 * (times[j+1] - times[j]));
    }
  }

  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  long cost = boost::find_flow_cost(G);
  std::cout << (100 * num_cars * last_t - cost) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
