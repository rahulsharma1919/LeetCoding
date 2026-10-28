class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<bitset<1024>> dp(n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bitset<1024> cur;
                if (i == 0 && j == 0) {
                    cur[0] = 1;
                } else {
                    if (i > 0)
                        cur |= dp[j];
                    if (j > 0)
                        cur |= dp[j - 1];
                }
                bitset<1024> nxt;
                int g = grid[i][j];
                for (int v = cur._Find_first(); v < 1024; v = cur._Find_next(v))
                    nxt[v ^ g] = 1;
                dp[j] = nxt;
            }
        }

        return dp[n - 1]._Find_first();
    }
};