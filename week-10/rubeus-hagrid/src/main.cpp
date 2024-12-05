#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

struct Tunnel;

struct Room {
    long long galleons;          // Use long long for galleons
    long long time_needed;       // Use long long for time needed
    std::vector<Tunnel*> children;
    int index;

    explicit Room(int index) : index(index), galleons(0), time_needed(0) {};

    bool operator<(const Room& other) const {
        return time_needed > other.time_needed; // pqueue sorts in descending order
    };
};

struct Tunnel {
    Room* leading_to;
    long long length;            // Use long long for tunnel length

    Tunnel(Room* child, long long len) : leading_to(child), length(len) {};
};

long long precompute(Room* room) {
    if (room->children.empty()) {
        return 0;
    }

    long long time_needed = 0;
    for (const auto& tunnel : room->children) {
        time_needed += 2 * tunnel->length + precompute(tunnel->leading_to);
    }

    room->time_needed = time_needed;
    return time_needed;
}

long long traverse(Room* room, long long& t) {
    long long value = room->galleons - t;

    for (const auto& c : room->children) {
        value += traverse(c->leading_to, t += c->length);
        t += c->length;
    }

    return value;
}

void testcase() {
    int n; std::cin >> n;
    std::vector<Room*> rooms(n + 1);

    for (int i = 0; i <= n; ++i) {
        rooms[i] = new Room(i);
    }

    rooms[0]->galleons = 0;

    for (int i = 1; i <= n; i++) {
        std::cin >> rooms[i]->galleons;
    }

    for (int i = 0; i < n; i++) {
        int u, v; long long l; // Use long long for length
        std::cin >> u >> v >> l;
        Room* parent = rooms[u];
        Room* child = rooms[v];
        Tunnel* tunnel = new Tunnel(child, l);

        parent->children.push_back(tunnel);
    }

    precompute(rooms[0]);

    for (const auto& room : rooms) {
        std::sort(room->children.begin(), room->children.end(), [](Tunnel* a, Tunnel* b) {
            return (a->leading_to->time_needed + 2 * a->length) < (b->leading_to->time_needed + 2 * b->length);
        });
    }

    long long time = 0;
    long long val = traverse(rooms[0], time);

    std::cout << val << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t; std::cin >> t;
    while (t--) {
        testcase();
    }
}
