class Solution {
private:
    vector<int> parent, rnk;

    void init(int n) {
        parent.resize(n);
        rnk.assign(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]]; // path halving (faster in practice)
            x = parent[x];
        }
        return x;
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (rnk[x] < rnk[y])
            swap(x, y);
        parent[y] = x;
        if (rnk[x] == rnk[y])
            rnk[x]++;
        return true;
    }

    // Returns true if we can form spanning tree with min strength >= mid
    bool canAchieve(int mid, int n, const vector<array<int, 4>>& mustEdges,
                    const vector<array<int, 4>>& optFree,    // s >= mid
                    const vector<array<int, 4>>& optUpgrade, // mid/2 <= s < mid
                    int k) {
        init(n);
        int comp = n, upgradesUsed = 0;

        // Must edges
        for (auto& e : mustEdges) {
            if (e[2] < mid)
                return false; // can't upgrade must edges
            if (!unite(e[0], e[1]))
                return false; // cycle
            comp--;
        }

        // Free optional edges (no upgrade needed)
        for (auto& e : optFree) {
            if (unite(e[0], e[1]))
                comp--;
            if (comp == 1)
                return true;
        }

        // Optional edges needing upgrade
        for (auto& e : optUpgrade) {
            if (upgradesUsed >= k)
                break;
            if (unite(e[0], e[1])) {
                comp--;
                upgradesUsed++;
            }
            if (comp == 1)
                return true;
        }

        return comp == 1;
    }

public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        // Convert for cache efficiency
        vector<array<int, 4>> must, optional_;
        vector<int> candidates;
        candidates.reserve(edges.size() * 2);

        for (auto& e : edges) {
            array<int, 4> a = {e[0], e[1], e[2], e[3]};
            if (e[3])
                must.push_back(a);
            else
                optional_.push_back(a);
            candidates.push_back(e[2]);
            candidates.push_back(e[2] * 2);
        }

        // Deduplicate and sort candidates descending (try highest stability
        // first)
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()),
                         candidates.end());

        // Pre-sort optional by strength descending for greedy (strongest first)
        sort(optional_.begin(), optional_.end(),
             [](const array<int, 4>& a, const array<int, 4>& b) {
                 return a[2] > b[2];
             });

        // Binary search over candidate values
        int lo = 0, hi = (int)candidates.size() - 1, ans = -1;

        // Quick check: is ANY spanning tree possible?
        // (check at mid=1 with full optional set)
        auto split = [&](int mid, vector<array<int, 4>>& free,
                         vector<array<int, 4>>& upgrade) {
            free.clear();
            upgrade.clear();
            for (auto& e : optional_) {
                if (e[2] >= mid)
                    free.push_back(e);
                else if (2 * e[2] >= mid)
                    upgrade.push_back(e);
            }
        };

        vector<array<int, 4>> free, upgrade;

        while (lo <= hi) {
            int mid_idx = lo + (hi - lo) / 2;
            int mid = candidates[mid_idx];

            split(mid, free, upgrade);
            if (canAchieve(mid, n, must, free, upgrade, k)) {
                ans = mid;
                lo = mid_idx + 1;
            } else {
                hi = mid_idx - 1;
            }
        }

        return ans;
    }
};