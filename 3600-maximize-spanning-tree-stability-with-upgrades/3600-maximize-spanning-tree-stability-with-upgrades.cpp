class Solution {
private:
    struct DSU {
        vector<int> parent, rank_;
        int components;
        DSU(int n) : parent(n), rank_(n, 0), components(n) {
            iota(parent.begin(), parent.end(), 0);
        }
        int find(int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }
        bool unite(int x, int y) {
            x = find(x);
            y = find(y);
            if (x == y)
                return false;
            if (rank_[x] < rank_[y])
                swap(x, y);
            parent[y] = x;
            if (rank_[x] == rank_[y])
                rank_[x]++;
            components--;
            return true;
        }
    };

    bool canAchieve(int mid, int n, vector<vector<int>>& edges, int k) {
        DSU dsu(n);
        int upgradesUsed = 0;

        // Step 1: Process MUST edges first
        for (auto& e : edges) {
            int u = e[0], v = e[1], s = e[2], must = e[3];
            if (!must)
                continue;
            // Must edge below target → impossible
            if (s < mid)
                return false;
            // Must edges can't be upgraded, just add them
            if (!dsu.unite(u, v))
                return false; // cycle among must edges
        }

        // Step 2: Add optional edges that don't need upgrade (s >= mid)
        for (auto& e : edges) {
            int u = e[0], v = e[1], s = e[2], must = e[3];
            if (must || s < mid)
                continue;
            dsu.unite(u, v); // no upgrade needed
        }

        // Step 3: Add optional edges needing upgrade (s*2 >= mid, s < mid)
        // i.e., s >= ceil(mid / 2.0)
        for (auto& e : edges) {
            int u = e[0], v = e[1], s = e[2], must = e[3];
            if (must || s >= mid)
                continue;
            if (2 * s >= mid) {
                // Can use with upgrade
                if (upgradesUsed < k && dsu.unite(u, v)) {
                    upgradesUsed++;
                }
            }
        }

        return dsu.components == 1;
    }

public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        // Collect all possible strength values (original + doubled)
        // Binary search over possible stability values
        int lo = 1, hi = 2e5, ans = -1;

        // First check if spanning tree is even possible at stability = 0
        if (!canAchieve(1, n, edges, k))
            return -1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (canAchieve(mid, n, edges, k)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};