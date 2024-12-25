#include <iostream> 
#include <set>
#include <algorithm>

int main() {
    int t;
    std::cin >> t;

    while(t--) {
        int n, m;
        std::cin >> n >> m;

        std::multiset<int, std::greater<int>> strengths;
        for(int i = 0; i < n; i++) {
            int si;
            std::cin >> si;
            strengths.insert(si);
        }

        std::multiset<int, std::greater<int>> boxes;
        for(int i = 0; i < m; i++) {
            int wi;
            std::cin >> wi;
            boxes.insert(wi);
        }
        
        // Check if the heaviest box can be lifted
        if(*strengths.begin() < *boxes.begin()) {
            std::cout << "impossible" << std::endl;
            continue;
        }

        int num_rounds = 1;
        auto friend_it = strengths.begin();  // Initialize friend iterator once

        while(!boxes.empty()) {

            auto box_it = boxes.lower_bound(*friend_it);  // Find the heaviest box this friend can lift

            if (box_it != boxes.end()) {
                box_it = boxes.erase(box_it);  // Box is removed
                friend_it++;

            } else {
                friend_it = strengths.erase(friend_it); 
            }

            // Reset friend iterator and increment round count if needed
            if (!boxes.empty() && friend_it == strengths.end()) {
                friend_it = strengths.begin();
                num_rounds++;
            }
        }
        std::cout << (num_rounds - 1) * 3 + 2 << std::endl;
    }
}
