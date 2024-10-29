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

        // // Print initial states
        // std::cout << "Initial strengths: ";
        // for (int s : strengths) std::cout << s << " ";
        // std::cout << "\nInitial boxes: ";
        // for (int b : boxes) std::cout << b << " ";
        // std::cout << std::endl;

        // Check if the heaviest box can be lifted
        if(*strengths.begin() < *boxes.begin()) {
            std::cout << "impossible" << std::endl;
            continue;
        }

        int num_rounds = 1;
        auto friend_it = strengths.begin();  // Initialize friend iterator once

        while(!boxes.empty()) {
            // std::cout << "\nCurrent round: " << num_rounds + 1 << std::endl;
            // std::cout << "Friend strength: " << *friend_it << std::endl;

            auto box_it = boxes.lower_bound(*friend_it);  // Find the heaviest box this friend can lift

            if (box_it != boxes.end()) {
                // std::cout << "Friend with strength " << *friend_it 
                //           << " lifts box with weight " << *box_it << std::endl;
                box_it = boxes.erase(box_it);  // Box is removed
                friend_it++;

            } else {
                // std::cout << "Friend with strength " << *friend_it 
                //           << " can't lift any remaining box, removing from lineup." << std::endl;
                friend_it = strengths.erase(friend_it); 
            }
        


            // Reset friend iterator and increment round count if needed
            if (!boxes.empty() && friend_it == strengths.end()) {
                // std::cout << "End of friend lineup reached; restarting from strongest friend for next round." << std::endl;
                friend_it = strengths.begin();
                num_rounds++;
            }

            // Print remaining boxes after each iteration
            // std::cout << "Remaining boxes: ";
            // for (int b : boxes) std::cout << b << " ";
            // std::cout << std::endl;
        }

        // std::cout << "Total rounds (including initial load): " << num_rounds << std::endl;
        std::cout << (num_rounds - 1) * 3 + 2 << std::endl;
    }
}
