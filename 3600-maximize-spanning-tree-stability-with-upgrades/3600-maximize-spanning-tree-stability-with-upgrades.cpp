class Solution {
private:
    struct DSU {
        vector<int> p, r;
        int comp;
        DSU(int n) : p(n), r(n, 0), comp(n) { iota(p.begin(), p.end(), 0); }
        int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
        bool unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b)
                return false;
            if (r[a] < r[b])
                swap(a, b);
            p[b] = a;
            if (r[a] == r[b])
                r[a]++;
            comp--;
            return true;
        }
    };

    bool check(int mid, int n, vector<vector<int>>& edges, int k) {
        DSU dsu(n);
        // Track optional edges added to spanning tree (for upgrade counting)
        int optionalInTree = 0;
        int upgradesNeeded = 0;

        // Step 1: Validate and add MUST edges
        for (auto& e : edges) {
            if (!e[3])
                continue;
            if (e[2] < mid)
                return false; // must edge too weak, impossible
            if (!dsu.unite(e[0], e[1]))
                return false; // cycle in must edges
        }

        // Step 2: Add optional edges >= mid (free, no upgrade)
        // Sort done outside; here we iterate sorted order
        for (auto& e : edges) {
            if (e[3] || e[2] < mid)
                continue;
            dsu.unite(e[0], e[1]);
        }

        // Step 3: Add optional edges needing upgrade (mid/2 <= s < mid)
        for (auto& e : edges) {
            if (e[3] || e[2] >= mid || 2 * e[2] < mid)
                continue;
            if (dsu.unite(e[0], e[1]))
                upgradesNeeded++;
        }

        return dsu.comp == 1 && upgradesNeeded <= k;
    }

public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        // Collect all candidate answer values: s and 2*s for optional edges
        vector<int> candidates;
        for (auto& e : edges) {
            candidates.push_back(e[2]);
            if (!e[3])
                candidates.push_back(e[2] * 2);
        }
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()),
                         candidates.end());

        // Check feasibility at all
        if (!check(1, n, edges, k))
            return -1;

        // Binary search over candidate values
        int lo = 0, hi = (int)candidates.size() - 1, ans = -1;
        while (lo <= hi) {
            int mi = lo + (hi - lo) / 2;
            if (check(candidates[mi], n, edges, k)) {
                ans = candidates[mi];
                lo = mi + 1;
            } else {
                hi = mi - 1;
            }
        }
        return ans;
    }
};