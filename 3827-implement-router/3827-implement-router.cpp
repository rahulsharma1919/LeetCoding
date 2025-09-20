class Router {
    struct Packet {
        int source, dest, time;
    };

    int limit;
    queue<uint64_t> q;                               // FIFO queue of keys
    unordered_map<uint64_t, Packet> packets;         // key -> packet
    unordered_map<int, vector<int>> destTimes;       // destination -> all timestamps
    unordered_map<int, int> destHead;                // destination -> index of first valid timestamp

    uint64_t encode(int source, int dest, int time) {
        return ((uint64_t)source << 48) | ((uint64_t)dest << 30) | (uint64_t)time;
    }

public:
    Router(int memoryLimit) { limit = memoryLimit; }

    bool addPacket(int source, int destination, int timestamp) {
        uint64_t key = encode(source, destination, timestamp);

        // duplicate
        if (packets.count(key)) return false;

        // evict if full
        if ((int)packets.size() == limit) forwardPacket();

        packets[key] = {source, destination, timestamp};
        q.push(key);
        destTimes[destination].push_back(timestamp);
        return true;
    }

    vector<int> forwardPacket() {
        if (q.empty()) return {};

        uint64_t key = q.front(); q.pop();
        auto p = packets[key];
        packets.erase(key);

        // logically remove earliest timestamp of this destination
        destHead[p.dest]++;

        return {p.source, p.dest, p.time};
    }

    int getCount(int destination, int startTime, int endTime) {
        if (!destTimes.count(destination)) return 0;
        auto &v = destTimes[destination];
        int head = destHead[destination];

        // skip already forwarded timestamps
        if (head >= (int)v.size()) return 0;

        auto it1 = lower_bound(v.begin() + head, v.end(), startTime);
        auto it2 = upper_bound(v.begin() + head, v.end(), endTime);

        return (int)(it2 - it1);
    }
};
