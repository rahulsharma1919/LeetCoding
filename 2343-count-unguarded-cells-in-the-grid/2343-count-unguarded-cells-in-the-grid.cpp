class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards,
                       vector<vector<int>>& walls) {
        unordered_set<long long> wallSet, guardSet, seen;
        auto encode = [&](int r, int c) -> long long {
            return (long long)r * n + c;
        };

        for (auto& w : walls)
            wallSet.insert(encode(w[0], w[1]));
        for (auto& g : guards)
            guardSet.insert(encode(g[0], g[1]));

        vector<vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto& g : guards) {
            for (auto& d : dirs) {
                int r = g[0] + d[0], c = g[1] + d[1];
                while (r >= 0 && c >= 0 && r < m && c < n &&
                       !wallSet.count(encode(r, c)) &&
                       !guardSet.count(encode(r, c))) {
                    seen.insert(encode(r, c));
                    r += d[0];
                    c += d[1];
                }
            }
        }

        int total = m * n;
        int occupied = walls.size() + guards.size();
        int unguarded = total - occupied - seen.size();
        return unguarded;
    }
};
