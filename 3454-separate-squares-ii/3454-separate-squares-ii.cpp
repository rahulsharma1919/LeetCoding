class Solution {
public:
    struct Event {
        long long y;
        long long x1, x2;
        int type;
    };
    double separateSquares(vector<vector<int>>& squares) {
        vector<Event> events;
        long long totalArea = 0;
        for (auto& s : squares) {
            long long x = s[0], y = s[1], l = s[2];
            events.push_back({y, x, x + l, +1});
            events.push_back({y + l, x, x + l, -1});
        }
        sort(events.begin(), events.end(),
             [](const Event& a, const Event& b) { return a.y < b.y; });

        multiset<pair<long long, long long>> active;

        auto unionWidth = [&]() {
            if (active.empty())
                return 0LL;
            long long res = 0;
            long long curL = -1e18, curR = -1e18;
            for (auto& [l, r] : active) {
                if (l > curR) {
                    res += max(0LL, curR - curL);
                    curL = l;
                    curR = r;
                } else {
                    curR = max(curR, r);
                }
            }
            res += max(0LL, curR - curL);
            return res;
        };
        long long prevY = events[0].y;
        long double half;
        vector<pair<long double, long double>> slabs;

        for (auto& e : events) {
            long long dy = e.y - prevY;
            if (dy > 0 && !active.empty()) {
                long long width = unionWidth();
                totalArea += width * dy;
            }
            if (e.type == 1)
                active.insert({e.x1, e.x2});
            else
                active.erase(active.find({e.x1, e.x2}));
            prevY = e.y;
        }
        half = totalArea / 2.0L;
        active.clear();
        prevY = events[0].y;
        long double acc = 0;

        for (auto& e : events) {
            long long dy = e.y - prevY;
            if (dy > 0 && !active.empty()) {
                long long width = unionWidth();
                long double slabArea = (long double)width * dy;
                if (acc + slabArea >= half) {
                    long double need = half - acc;
                    return (double)(prevY + need / width);
                }
                acc += slabArea;
            }
            if (e.type == 1)
                active.insert({e.x1, e.x2});
            else
                active.erase(active.find({e.x1, e.x2}));
            prevY = e.y;
        }
        return (double)prevY;
    }
};
