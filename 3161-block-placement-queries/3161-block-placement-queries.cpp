class Solution {
public:
    vector<int> seg;
    int N;

    void update(int node, int lo, int hi, int pos, int val) {
        if (lo == hi) {
            seg[node] = val;
            return;
        }
        int mid = (lo + hi) / 2;
        if (pos <= mid)
            update(2 * node, lo, mid, pos, val);
        else
            update(2 * node + 1, mid + 1, hi, pos, val);
        seg[node] = max(seg[2 * node], seg[2 * node + 1]);
    }

    int query(int node, int lo, int hi, int l, int r) {
        if (r < lo || hi < l)
            return 0;
        if (l <= lo && hi <= r)
            return seg[node];
        int mid = (lo + hi) / 2;
        return max(query(2 * node, lo, mid, l, r),
                   query(2 * node + 1, mid + 1, hi, l, r));
    }

    vector<bool> getResults(vector<vector<int>>& queries) {
        int maxVal = 0;
        for (auto& q : queries)
            maxVal = max(maxVal, q[1]);

        N = maxVal + 1;
        seg.assign(4 * N, 0);

        set<int> obstacles;
        obstacles.insert(0);
        obstacles.insert(maxVal + 1);

        for (auto& q : queries)
            if (q[0] == 1)
                obstacles.insert(q[1]);

        for (auto it = next(obstacles.begin()); it != obstacles.end(); ++it) {
            auto prev = std::prev(it);
            if (*it <= maxVal)
                update(1, 0, N - 1, *it, *it - *prev);
        }

        vector<bool> results;

        set<int> active = {0, maxVal + 1};
        for (auto it = next(obstacles.begin()); it != obstacles.end(); ++it)
            if (*it <= maxVal)
                active.insert(*it);

        set<int> removed;
        for (int i = (int)queries.size() - 1; i >= 0; i--) {
            auto& q = queries[i];
            if (q[0] == 1) {
                int x = q[1];
                removed.insert(x);
                auto it = active.find(x);
                auto nxt = next(it);
                auto prv = prev(it);
                active.erase(it);
                if (*nxt <= maxVal)
                    update(1, 0, N - 1, *nxt, *nxt - *prv);
            }
        }

        vector<bool> rev;
        set<int> current = {0, maxVal + 1};
        seg.assign(4 * N, 0);

        for (auto& q : queries) {
            if (q[0] == 1) {
                int x = q[1];
                auto it = current.insert(x).first;
                auto nxt = next(it);
                auto prv = prev(it);
                update(1, 0, N - 1, x, x - *prv);
                if (*nxt <= maxVal)
                    update(1, 0, N - 1, *nxt, *nxt - x);
            } else {
                int x = q[1], sz = q[2];
                auto it = current.upper_bound(x);
                --it;
                int lastObs = *it;
                int tailGap = x - lastObs;
                int best = lastObs > 0 ? query(1, 0, N - 1, 0, lastObs) : 0;
                best = max(best, tailGap);
                rev.push_back(best >= sz);
            }
        }

        return rev;
    }
};