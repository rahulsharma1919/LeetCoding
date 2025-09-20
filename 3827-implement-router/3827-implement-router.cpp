class Router {
private:
    int size;
    unordered_map<string, array<int,3>> packets; // key -> {source,dest,time}
    unordered_map<int, deque<int>> counts;       // destination -> deque of timestamps (unique per insertion order)
    queue<string> q;

    string keyStr(int source, int destination, int timestamp) {
        return to_string(source) + "#" + to_string(destination) + "#" + to_string(timestamp);
    }

public:
    Router(int memoryLimit) {
        size = memoryLimit;
    }

    bool addPacket(int source, int destination, int timestamp) {
        string key = keyStr(source, destination, timestamp);

        // duplicate check
        if (packets.find(key) != packets.end())
            return false;

        // if full, evict oldest packet
        if ((int)packets.size() >= size) 
            forwardPacket();

        packets[key] = {source, destination, timestamp};
        q.push(key);

        // append timestamp for that destination (timestamps are non-decreasing)
        counts[destination].push_back(timestamp);

        return true;
    }

    vector<int> forwardPacket() {
        if (packets.empty()) return {};

        string key = q.front();
        q.pop();

        auto arr = packets[key];
        packets.erase(key);

        int src = arr[0], dest = arr[1], time = arr[2];

        // remove earliest timestamp for this destination (O(1) with deque)
        auto it = counts.find(dest);
        if (it != counts.end() && !it->second.empty()) {
            it->second.pop_front();
            if (it->second.empty()) counts.erase(it);
        }

        return {src, dest, time};
    }

    int getCount(int destination, int startTime, int endTime) {
        auto it = counts.find(destination);
        if (it == counts.end() || it->second.empty()) return 0;

        auto &dq = it->second;
        auto lb = lower_bound(dq.begin(), dq.end(), startTime);
        auto ub = upper_bound(dq.begin(), dq.end(), endTime);
        return int(ub - lb);
    }
};
