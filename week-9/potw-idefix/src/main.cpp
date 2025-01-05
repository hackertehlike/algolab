#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

// Epic kernel is enough, no constructions needed, provided the squared distance fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;

// Define Edge structure to represent edges in the triangulation
typedef std::tuple<Index, Index, K::FT> Edge;
typedef std::vector<Edge> EdgeV;

std::vector<int> num_bones_in_union(const Triangulation& t, double radius, const std::vector<std::pair<Index, K::FT>>& bone_distances, const EdgeV& edges) {
    int n = t.number_of_vertices();
    boost::disjoint_sets_with_storage<> uf(n);
    Index n_components = n;

    // Process edges for MST construction
    for (const Edge& e : edges) {
        if (std::get<2>(e) > radius) break;

        Index c1 = uf.find_set(std::get<0>(e));
        Index c2 = uf.find_set(std::get<1>(e));

        if (c1 != c2) {
            uf.link(c1, c2);
            if (--n_components == 1) break;
        }
    }

    // Count bones in each connected component
    std::vector<int> res(n, 0);
    for (const auto& [vertex_index, dist] : bone_distances) {
        if (4 * dist <= radius) {
            res[uf.find_set(vertex_index)]++;
        }
    }

    return res;
}

void testcase() {
    int n, m, k;
    long s;
    std::cin >> n >> m >> s >> k;

    // Read the trees
    std::vector<std::pair<P, int>> trees(n);
    for (int i = 0; i < n; ++i) {
        P tree;
        std::cin >> tree;
        trees[i] = {tree, i};
    }

    // Construct the Delaunay triangulation
    Triangulation t;
    t.insert(trees.begin(), trees.end());

    // Read the bones and precompute distances to the nearest vertices
    std::vector<std::pair<Index, K::FT>> bone_distances(m);
    for (int j = 0; j < m; ++j) {
        P bone;
        std::cin >> bone;

        auto nearest_vertex = t.nearest_vertex(bone);
        K::FT dist = CGAL::squared_distance(nearest_vertex->point(), bone);
        bone_distances[j] = {nearest_vertex->info(), dist};
    }

    // Extract and sort edges from the triangulation
    EdgeV edges;
    edges.reserve(3 * n);
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Index i1 = e->first->vertex((e->second + 1) % 3)->info();
        Index i2 = e->first->vertex((e->second + 2) % 3)->info();
        if (i1 > i2) std::swap(i1, i2);
        edges.emplace_back(i1, i2, t.segment(e).squared_length());
    }

    std::sort(edges.begin(), edges.end(),
              [](const Edge& e1, const Edge& e2) -> bool {
                  return std::get<2>(e1) < std::get<2>(e2);
              });

    // Calculate the maximum number of bones within distance `s`
    std::vector<int> bone_counts = num_bones_in_union(t, s, bone_distances, edges);
    int a = *std::max_element(bone_counts.begin(), bone_counts.end());

    // Perform binary search for the minimum radius
    long start = 0, end = 1L << 51;
    while (start < end) {
        long mid = start + (end - start) / 2;
        bone_counts = num_bones_in_union(t, mid, bone_distances, edges);
        int max_bones = *std::max_element(bone_counts.begin(), bone_counts.end());

        if (max_bones >= k) {
            end = mid;
        } else {
            start = mid + 1;
        }
    }

    // Output the results
    std::cout << a << " " << end << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}
