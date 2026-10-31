class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1000000007;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        auto land = [&](int i, int j, int dir, int& ri, int& rj) {
            while (i < m && j < n && grid[i][j]) {
                if (dir == 0) {
                    i++;
                    dir = 1;
                } // mirror entered moving right -> go down
                else {
                    j++;
                    dir = 0;
                } // mirror entered moving down  -> go right
            }
            if (i >= m || j >= n)
                return false;
            ri = i;
            rj = j;
            return true;
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] || !dp[i][j])
                    continue;
                int ri, rj;
                if (land(i, j + 1, 0, ri, rj))
                    dp[ri][rj] = (dp[ri][rj] + dp[i][j]) % MOD;
                if (land(i + 1, j, 1, ri, rj))
                    dp[ri][rj] = (dp[ri][rj] + dp[i][j]) % MOD;
            }
        }
        return dp[m - 1][n - 1];
    }
};