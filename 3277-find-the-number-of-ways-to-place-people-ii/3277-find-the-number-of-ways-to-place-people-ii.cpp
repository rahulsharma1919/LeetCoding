class Solution {
    // Fenwick / BIT (1-based)
    struct Fenwick {
        int n;
        vector<int> bit;
        Fenwick(int n=0): n(n), bit(n+1, 0) {}
        void add(int idx, int val) {
            for (; idx <= n; idx += idx & -idx) bit[idx] += val;
        }
        int sumPrefix(int idx) {
            int s = 0;
            for (; idx > 0; idx -= idx & -idx) s += bit[idx];
            return s;
        }
        int rangeSum(int l, int r) {
            if (l > r) return 0;
            return sumPrefix(r) - sumPrefix(l - 1);
        }
    };

public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size();
        if (n < 2) return 0;

        // Sort by x asc, and for equal x sort by y desc
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b){
            if (a[0] != b[0]) return a[0] < b[0];
            return a[1] > b[1]; // important: y descending on tie
        });

        // Coordinate compress y
        vector<long long> ys;
        ys.reserve(n);
        for (auto &p : points) ys.push_back(p[1]);
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        int m = ys.size();
        vector<int> yidx(n);
        for (int i = 0; i < n; ++i) {
            yidx[i] = int(lower_bound(ys.begin(), ys.end(), points[i][1]) - ys.begin());
            // we'll use 1-based indices for Fenwick -> add +1 when calling
        }

        long long ans = 0;
        // For each i, sweep j >= i, maintain a Fenwick that holds counts for points in [i..j]
        for (int i = 0; i < n; ++i) {
            Fenwick fw(m);
            for (int j = i; j < n; ++j) {
                // add point j
                fw.add(yidx[j] + 1, 1);

                if (j == i) continue;
                // Check A = i is upper-left of B = j
                if (points[i][1] >= points[j][1]) {
                    int l = yidx[j] + 1; // yB
                    int r = yidx[i] + 1; // yA
                    if (fw.rangeSum(l, r) == 2) {
                        ans++;
                    }
                }
            }
        }

        return (int)ans;
    }
};
